// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <set>
#include <optional>
#include <cmath>
#include <algorithm>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment14 {
public:
	void run() {
		initWindow();
		initVulkan();
		initApp();
		mainLoop();
		cleanup();
	}

private:
	GLFWwindow* window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDevice device;
	VkPhysicalDevice selectedPhysicalDevice;
	VkCommandPool commandPool;
	VkSwapchainKHR swapChain;
	std::vector<VkImageView> swapChainImageViews;

	void cleanup() {
		for (size_t i = 0; i < swapChainImageViews.size(); i++) {
			vkDestroyImageView(device, swapChainImageViews[i], nullptr);
		}
		vkDestroySwapchainKHR(device, swapChain, nullptr);
		vkDestroyCommandPool(device, commandPool, nullptr);
		vkDestroyDevice(device, nullptr);
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 14", nullptr, nullptr);
	}

	void GetPhysicalDevice(std::vector<VkPhysicalDevice> devices, uint32_t &selectedQueueWithGraphicsCapability, uint32_t &selectedQueueWithPresentationCapability) {
		for (const auto& physicalDevice : devices)
		{
			uint32_t queueFamCount = -1;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamCount, nullptr);
			std::cout << "\nQueue Families found: " << queueFamCount << "\n";
			std::vector<VkQueueFamilyProperties> queues(queueFamCount);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamCount, queues.data());

			std::optional<uint32_t> aQueueWithGraphicsCapability;
			std::optional<uint32_t> aQueueWithPresentationCapability;

			for (unsigned int i = 0; i < queueFamCount; i++)
			{
				std::cout << "\nQueueCount = " << i << "; ";

				if ((queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
					std::cout << " Graphics";
					aQueueWithGraphicsCapability = i;
				}

				if ((queues[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) std::cout << " Compute";
				if ((queues[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) std::cout << " Transfer";

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

				if (presentSupport) {
					std::cout << " Presentation";
					aQueueWithPresentationCapability = i;
				}

				if (aQueueWithGraphicsCapability.has_value() && aQueueWithPresentationCapability.has_value()) {
					std::cout << "\n\nGraphic queue family selected: " << aQueueWithGraphicsCapability.value() << "\n";
					std::cout << "Presentation queue family selected: " << aQueueWithPresentationCapability.value() << "\n";

					selectedPhysicalDevice = physicalDevice;
					selectedQueueWithGraphicsCapability = aQueueWithGraphicsCapability.value();
					selectedQueueWithPresentationCapability = aQueueWithPresentationCapability.value();
					return;
				}
			}
		}
	}

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) {
		SwapChainSupportDetails details;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};
			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
			return actualExtent;
		}
	}

	void initVulkan() {
		createInstance();

		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}

		// Enumerate devices
		uint32_t deviceCount = 0;
		if (vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS || deviceCount <= 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan Support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		if (vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS) {
			throw std::runtime_error("Could not enumerate devices");
		}

		uint32_t selectedQueueWithGraphicsCapability;
		uint32_t selectedQueueWithPresentationCapability;

		// Physical Device selection
		GetPhysicalDevice(devices, selectedQueueWithGraphicsCapability, selectedQueueWithPresentationCapability);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { selectedQueueWithGraphicsCapability, selectedQueueWithPresentationCapability };
		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority; queueCreateInfos.push_back(queueCreateInfo);
		}

		// Logical Device creation
		const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		VkPhysicalDeviceFeatures deviceFeatures{};
		VkDeviceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();
		createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(selectedPhysicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}
		std::cout << "\nLogic Device Created";

		// Command Pool creation
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = selectedQueueWithGraphicsCapability;
		poolInfo.flags = 0;

		if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create command pool!");
		}
		std::cout << "\nCommand Pool Created";

		// Command Buffer creation
		VkCommandBuffer commandBuffer;
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO; allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffer!");
		}

		// Swap chain creation

		//Swap chain capabilities (that include the size of the framebuffer,
		//and the minimum and maximum number of buffers supported)
		VkSurfaceCapabilitiesKHR SCcapabilities;

		//I query the capabilities
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(selectedPhysicalDevice, surface, &SCcapabilities);

		//Swap chain formats (characterized by the number of bits and components (defined in an enumeration),
		//and the corresponding color profile
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(selectedPhysicalDevice, surface, &formatCount, nullptr);
		std::vector<VkSurfaceFormatKHR> SCformats;

		if (formatCount != 0) {
			SCformats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(selectedPhysicalDevice, surface, &formatCount, SCformats.data());
			std::cout << "\t Supported Formats: " << formatCount << "\n";

			for (int i = 0; i < formatCount; i++) {
				std::cout << "\t\tFormat: " << SCformats[i].format << ", Color Space:" << SCformats[i].colorSpace << "\n";
			}
		}

		//Selection of format parameters
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(selectedPhysicalDevice);
		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		//Structure to create swap chain (contains the number of images in the buffers, their format,
		//the color space, the extent, and the presentation mode
		VkSwapchainCreateInfoKHR SCcreateInfo{};
		SCcreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		SCcreateInfo.surface = surface;
		SCcreateInfo.minImageCount = imageCount;
		SCcreateInfo.imageFormat = surfaceFormat.format;
		SCcreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		SCcreateInfo.imageExtent = extent;
		SCcreateInfo.imageArrayLayers = 1;
		SCcreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		//Structure to provide the swap chain pointers to graphic and presentation queues
		uint32_t queueFamilyIndices[] = { selectedQueueWithGraphicsCapability, selectedQueueWithPresentationCapability };
		if (selectedQueueWithGraphicsCapability != selectedQueueWithPresentationCapability) {
			SCcreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			SCcreateInfo.queueFamilyIndexCount = 2;
			SCcreateInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			SCcreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			SCcreateInfo.queueFamilyIndexCount = 0;
			SCcreateInfo.pQueueFamilyIndices = nullptr;
		}

		SCcreateInfo.preTransform = SCcapabilities.currentTransform;
		SCcreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		SCcreateInfo.presentMode = presentMode;
		SCcreateInfo.clipped = VK_TRUE;
		SCcreateInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(device, &SCcreateInfo, nullptr, &swapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		//Image view creation (Each buffer of the swap chain, is considered by Vulkan as a generic image
		//which must be retrieved after creation
		//Image Views, are the way in which Vulkan associate to each image, the description on how it can be used and accessed,
		//and they are necessary to support them.
		std::vector<VkImage> swapChainImages;
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

		swapChainImageViews.resize(swapChainImages.size());
		for (size_t i = 0; i < swapChainImages.size(); i++) {
			VkImageViewCreateInfo viewInfo{};
			viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewInfo.image = swapChainImages[i];
			viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewInfo.format = surfaceFormat.format;
			viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			viewInfo.subresourceRange.baseMipLevel = 0;
			viewInfo.subresourceRange.levelCount = 1;
			viewInfo.subresourceRange.baseArrayLayer = 0;
			viewInfo.subresourceRange.layerCount = 1;
			VkImageView imageView;
			VkResult result = vkCreateImageView(device, &viewInfo, nullptr, &imageView);
			if (result != VK_SUCCESS) {
				throw std::runtime_error("failed to create image view!");
			}
			swapChainImageViews[i] = imageView;
		}

		std::cout << "\nAll done!";
	}

	void createInstance() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Assignment 14";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;
		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}
	}

	void initApp() {
		// This will not be needed in this assignment!
	}
};

int main() {
	Assignment14 app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}