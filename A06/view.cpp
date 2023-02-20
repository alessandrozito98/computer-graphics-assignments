using namespace glm;

// Create a look in direction matrix
 // Pos    -> Position of the camera
 // Angs.x -> direction (alpha)
 // Angs.y -> elevation (beta)
 // Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs) {

	mat4 out = glm::mat4(1.0);

	out = glm::rotate(glm::mat4(1.0), -Angs.z, glm::vec3(0, 0, 1)) * glm::rotate(out, -Angs.y, glm::vec3(1, 0, 0)) * 
		glm::rotate(glm::mat4(1.0), -Angs.x, glm::vec3(0, 1, 0)) * translate(glm::mat4(1.0), -Pos);
	return out;
}

 // Create a look at matrix
 // Pos    -> Position of the camera (c)
 // aim    -> Posizion of the target (a)
 // Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll) {
	glm::mat4 out = glm::mat4(1.0);

	out = lookAt(Pos,aim, glm::vec3(0, 1, 0)) * rotate(out, -Roll, vec3(0, 0, 1));
	return out;
}



