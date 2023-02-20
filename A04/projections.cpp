using namespace glm;

// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	glm::mat4 out = glm::mat4(1.0);
	mat4 s = scale(out, vec3(1, -1, 1));
	mat4 rx = rotate(out, radians(35.26f), vec3(1, 0, 0));
	mat4 ry = rotate(out, radians(45.0f), vec3(0, 1, 0));
	mat4 ort = ortho(-2.0f, 2.0f, -2.0f / a, 2.0f / a, -4.0f, 12.0f);
	out = s * ort * rx * ry;
	return out;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	glm::mat4 out = glm::mat4(1.0);
	mat4 s = scale(out, vec3(1, -1, 1));
	mat4 ry = rotate(out, radians(45.0f), vec3(0, 1, 0));
	mat4 rx = rotate(out, radians(45.0f), vec3(1, 0, 0));
	mat4 ort = ortho(-2.0f, 2.0f, -2.0f / a, 2.0f / a, -4.0f, 12.0f);
	out = s * ort * rx * ry;
	return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	glm::mat4 out = glm::mat4(1.0);
	mat4 s = scale(out, vec3(1, -1, 1));
	mat4 ry = rotate(out, radians(60.0f), vec3(0, 1, 0));
	mat4 rx = rotate(out, radians(45.0f), vec3(1, 0, 0));
	mat4 ort = ortho(-2.0f, 2.0f, -2.0f / a, 2.0f / a, -4.0f, 12.0f);
	out = s * ort * rx * ry;
	return out;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	const float p = 0.5;
	const float alpha = 45.0f;
	glm::mat4 out = glm::mat4(1.0);
	mat4 s = scale(out, vec3(1, -1, 1));
	mat4 ort = ortho(-2.0f, 2.0f, -2.0f / a, 2.0f / a, -4.0f, 12.0f);
	
	mat4 m2 = mat4(1, 0, -p*cos(radians(alpha)), 0,
		0, 1, -p*sin(radians(alpha)), 0,
		0, 0, 1, 0,
		0, 0, 0, 1);


	mat4 shear = transpose(m2);

	out = s * ort * shear;
	return out;
}

