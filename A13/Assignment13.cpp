// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment13 {
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
	VkCommandPool commandPool;

	void cleanup() {
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

	//Creation of the window
	void initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 13", nullptr, nullptr);
	}

	void GetPhysicalDevice(std::vector<VkPhysicalDevice> devices, VkPhysicalDevice &selectedPhysicalDevice, uint32_t &selectedQueueWithGraphicsCapability, uint32_t &selectedQueueWithPresentationCapability) {
		for (const auto& physicalDevice : devices)
		{
			//Enumerate the queue families
			uint32_t queueFamCount = -1;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamCount, nullptr);
			std::cout << "\nQueue Families found: " << queueFamCount << "\n";
			std::vector<VkQueueFamilyProperties> queues(queueFamCount);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamCount, queues.data());

			std::optional<uint32_t> aQueueWithGraphicsCapability;
			std::optional<uint32_t> aQueueWithPresentationCapability;

			//I iterate throughout all the queue families selecting the first one supporting both a graphic
			//and a presentation queue
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

	void initVulkan() {
		createInstance();

		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}

		// Enumerate physical devices
		uint32_t deviceCount = 0;
		if (vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr) != VK_SUCCESS || deviceCount <= 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan Support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		if (vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()) != VK_SUCCESS) {
			throw std::runtime_error("Could not enumerate devices");
		}

		VkPhysicalDevice selectedPhysicalDevice;
		uint32_t selectedQueueWithGraphicsCapability;
		uint32_t selectedQueueWithPresentationCapability;

		// Physical device selection
		GetPhysicalDevice(devices, selectedPhysicalDevice, selectedQueueWithGraphicsCapability, selectedQueueWithPresentationCapability);

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
		VkPhysicalDeviceFeatures deviceFeatures{};
		VkDeviceCreateInfo createInfo{};

		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;
		createInfo.ppEnabledExtensionNames = nullptr;
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

		std::cout << "\nAll done!";
	}

	void createInstance() {

		//I retrieve the extensions required to allow the application working in the host O.S
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Assignment 13";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//Structure that contains the app info and the required extensions
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
	Assignment13 app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}