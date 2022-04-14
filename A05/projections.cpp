using namespace glm;

const float n = 0.1f;
const float f = 9.9f;

glm::mat4 generate_projection(float fovy, float a) {

	mat4 to_return = perspective(fovy, a, n, f);

	to_return[1][1] *= -1;
	return to_return;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a) {
	const float fovy = radians(90.0f);
	glm::mat4 out = glm::mat4(1.0);

	out = generate_projection(fovy, a);
	/*
	out = perspective(fovy, a, n, f);
	out[1][1] *= -1;
	*/
	return out;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a) {
	const float fovy = radians(120.0f);

	glm::mat4 out = glm::mat4(1.0);

	out = generate_projection(fovy, a);

	/*
	out = perspective(120.0f, a, n, f);
	out[1][1] *= -1;
	*/
	return out;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a) {
	const float fovy = radians(30.0f);
	glm::mat4 out = glm::mat4(1.0);

	out = generate_projection(fovy, a);
	return out;
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {


	float l = -a * n * tan(radians(90.0f/2));
	float r = 0.0f;
	float t = n*tan(radians(90.0f / 2));
	float b = -n * tan(radians(90.0f / 2));
	
	glm::mat4 out = glm::mat4(1.0);
	out = scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * frustum(l, r, b, t, n, f);
	return out;
}

