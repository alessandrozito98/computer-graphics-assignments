// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static glm::vec3 pos = glm::vec3(-3,0,2);	// variable to store robot position
												// here glm::vec3(-3,0,2) represents a
												// meaningful initial position for the robot
												//
												// this variable is here just as an example!
												// it should replaced or combined with
												//  the ones you think necessary for the task
	glm::mat4 out;
	
	static float MOVE_SPEED = 0.20;

	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0f;

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	float deltaT = time - lastTime;

	lastTime = time;


	static float yaw = 0.0;

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		pos -=  MOVE_SPEED * glm::vec3(1, 0, 0) * deltaT;
		yaw = 180.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		pos += MOVE_SPEED * glm::vec3(1, 0, 0) * deltaT;
		yaw = 0.0;
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		pos -= MOVE_SPEED * glm::vec3(0, 0, 1) * deltaT;
		yaw = 90.0;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		pos += MOVE_SPEED * glm::vec3(0, 0, 1) * deltaT;
		yaw = -90.0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += float(sqrt(2)) * MOVE_SPEED * glm::vec3(-1, 0, -1) * deltaT;
		yaw = 135.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += float(sqrt(2)) * MOVE_SPEED * glm::vec3(1, 0, -1) * deltaT;
		yaw = 45.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += float(sqrt(2)) * MOVE_SPEED * glm::vec3(1, 0, 1) * deltaT;
		yaw = -45.0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += float(sqrt(2)) * MOVE_SPEED * glm::vec3(-1, 0, 1) * deltaT;
		yaw = -135.0;
	}



	out = glm::translate(glm::mat4(1), pos) * glm::rotate(glm::mat4(1), glm::radians(yaw), glm::vec3(0, 1, 0));	// this line has to be changed!
												// it is here just to allow the program to
												// be compiled and run
	return out;
}

