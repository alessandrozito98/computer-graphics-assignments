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
	
	static float yaw = 0.0;

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		pos -=  glm::vec3(0.020, 0, 0);
		yaw = 180.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		pos += glm::vec3(0.020, 0, 0);
		yaw = 0.0;
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		pos -= glm::vec3(0, 0, 0.020);
		yaw = 90.0;
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		pos += glm::vec3(0, 0, 0.020);
		yaw = -90.0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += glm::vec3(-0.028, 0, -0.028);
		yaw = 135.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += glm::vec3(0.028, 0, -0.028);
		yaw = 45.0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += glm::vec3(0.028, 0, 0.028);
		yaw = -45.0;
	}
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += glm::vec3(-0.028, 0, 0.028);
		yaw = -135.0;
	}



	out = glm::translate(glm::mat4(1), pos) * glm::rotate(glm::mat4(1), glm::radians(yaw), glm::vec3(0, 1, 0));	// this line has to be changed!
												// it is here just to allow the program to
												// be compiled and run
	return out;
}

