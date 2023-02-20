// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;

const double pi = 3.14159265358979323846;


void makeModels() {
	//// M1 : Cube

	//24 vertices
	M1_vertices.resize(24);

	M1_vertices[0].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[0].norm = glm::vec3(0.0, 0.0, 1.0);
	M1_vertices[0].UV = glm::vec2(0.125, 0.125);

	M1_vertices[1].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[1].norm = glm::vec3(0.0, 0.0, 1.0);
	M1_vertices[1].UV = glm::vec2(0.25, 0.125);

	M1_vertices[2].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[2].norm = glm::vec3(0.0, 0.0, 1.0);
	M1_vertices[2].UV = glm::vec2(0.125, 0.0);

	M1_vertices[3].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[3].norm = glm::vec3(0.0, 0.0, 1.0);
	M1_vertices[3].UV = glm::vec2(0.25, 0.0);

	M1_vertices[4].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[4].norm = glm::vec3(1.0, 0.0, 0.0);
	M1_vertices[4].UV = glm::vec2(0.375, 0.375);

	M1_vertices[5].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[5].norm = glm::vec3(1.0, 0.0, 0.0);
	M1_vertices[5].UV = glm::vec2(0.375, 0.25);

	M1_vertices[6].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[6].norm = glm::vec3(1.0, 0.0, 0.0);
	M1_vertices[6].UV = glm::vec2(0.25, 0.25);

	M1_vertices[7].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[7].norm = glm::vec3(1.0, 0.0, 0.0);
	M1_vertices[7].UV = glm::vec2(0.25, 0.375);

	M1_vertices[8].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[8].norm = glm::vec3(0.0, 0.0, -1.0);
	M1_vertices[8].UV = glm::vec2(0.25, 0.375);

	M1_vertices[9].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[9].norm = glm::vec3(0.0, 0.0, -1.0);
	M1_vertices[9].UV = glm::vec2(0.25, 0.25);

	M1_vertices[10].pos = glm::vec3(-1.0, -1.0, -1.0);
	M1_vertices[10].norm = glm::vec3(0.0, 0.0, -1.0);
	M1_vertices[10].UV = glm::vec2(0.125, 0.375);

	M1_vertices[11].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[11].norm = glm::vec3(0.0, 0.0, -1.0);
	M1_vertices[11].UV = glm::vec2(0.125, 0.25);

	M1_vertices[12].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[12].norm = glm::vec3(-1.0, 0.0, 0.0);
	M1_vertices[12].UV = glm::vec2(0.125, 0.25);

	M1_vertices[13].pos = glm::vec3(-1.0, -1.0, -1.0);
	M1_vertices[13].norm = glm::vec3(-1.0, 0.0, 0.0);
	M1_vertices[13].UV = glm::vec2(0.125, 0.375);

	M1_vertices[14].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[14].norm = glm::vec3(-1.0, 0.0, 0.0);
	M1_vertices[14].UV = glm::vec2(0.0, 0.25);

	M1_vertices[15].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[15].norm = glm::vec3(-1.0, 0.0, 0.0);
	M1_vertices[15].UV = glm::vec2(0.0, 0.375);

	M1_vertices[16].pos = glm::vec3(-1.0, 1.0, 1.0);
	M1_vertices[16].norm = glm::vec3(0.0, 1.0, 0.0);
	M1_vertices[16].UV = glm::vec2(0.125, 0.125);

	M1_vertices[17].pos = glm::vec3(1.0, 1.0, 1.0);
	M1_vertices[17].norm = glm::vec3(0.0, 1.0, 0.0);
	M1_vertices[17].UV = glm::vec2(0.25, 0.125);

	M1_vertices[18].pos = glm::vec3(1.0, 1.0, -1.0);
	M1_vertices[18].norm = glm::vec3(0.0, 1.0, 0.0);
	M1_vertices[18].UV = glm::vec2(0.25, 0.25);

	M1_vertices[19].pos = glm::vec3(-1.0, 1.0, -1.0);
	M1_vertices[19].norm = glm::vec3(0.0, 1.0, 0.0);
	M1_vertices[19].UV = glm::vec2(0.125, 0.25);

	M1_vertices[20].pos = glm::vec3(1.0, -1.0, -1.0);
	M1_vertices[20].norm = glm::vec3(0.0, -1.0, 0.0);
	M1_vertices[20].UV = glm::vec2(0.25, 0.375);

	M1_vertices[21].pos = glm::vec3(-1.0, -1.0, -1.0);
	M1_vertices[21].norm = glm::vec3(0.0, -1.0, 0.0);
	M1_vertices[21].UV = glm::vec2(0.125, 0.375);

	M1_vertices[22].pos = glm::vec3(1.0, -1.0, 1.0);
	M1_vertices[22].norm = glm::vec3(0.0, -1.0, 0.0);
	M1_vertices[22].UV = glm::vec2(0.25, 0.5);

	M1_vertices[23].pos = glm::vec3(-1.0, -1.0, 1.0);
	M1_vertices[23].norm = glm::vec3(0.0, -1.0, 0.0);
	M1_vertices[23].UV = glm::vec2(0.125, 0.5);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 12);

	M1_indices[0] = 0;
	M1_indices[1] = 1;
	M1_indices[2] = 2;

	M1_indices[3] = 1;
	M1_indices[4] = 2;
	M1_indices[5] = 3;

	M1_indices[6] = 4;
	M1_indices[7] = 5;
	M1_indices[8] = 6;

	M1_indices[9] = 4;
	M1_indices[10] = 6;
	M1_indices[11] = 7;

	M1_indices[12] = 8;
	M1_indices[13] = 9;
	M1_indices[14] = 10;

	M1_indices[15] = 9;
	M1_indices[16] = 10;
	M1_indices[17] = 11;

	M1_indices[18] = 12;
	M1_indices[19] = 13;
	M1_indices[20] = 14;

	M1_indices[21] = 13;
	M1_indices[22] = 14;
	M1_indices[23] = 15;

	M1_indices[24] = 16;
	M1_indices[25] = 17;
	M1_indices[26] = 18;

	M1_indices[27] = 16;
	M1_indices[28] = 18;
	M1_indices[29] = 19;

	M1_indices[30] = 20;
	M1_indices[31] = 21;
	M1_indices[32] = 22;

	M1_indices[33] = 21;
	M1_indices[34] = 22;
	M1_indices[35] = 23;

	//// M2 : Cylinder

	// Height of the cylinder
	const float HEIGHT = 3.0f;

	// Radius of the upper and lower circles
	const float RADIUS = 1.0f;

	// Number of strips (edges in the edge ring)
	const int N_STRIPS = 32;

	// Resizes the vertices array. Replace the values with the correct number of
	// vertices components (3 * number of vertices)
	// For each circle there are 2 * N_STRIPS vertices (duplication of vertices because of normals)
	// Also, vertices at the beginning and at the end of the texture should be repeated (with different UVs)
	// => total of N_STRIPS * 4 vertices + 2 for the middle of the two circles + 2 vertices repeated.
	M2_vertices.resize(4 * N_STRIPS + 6);

	// Resizes the indices array. Replace the values with the correct number of
	// indices (3 * number of triangles)
	// For each face (N_STRIPS) two triangles => N_STRIPS * 2 triangles + N_STRIPS triangles for each circle (2).
	M2_indices.resize(4 * (N_STRIPS) * 3);

	// Offset in vertices array between vertices of the lower circle and vertices of the upper circle
	const int offset1 = N_STRIPS + 2;

	// Offset in indices array between triangles of the lower circle and triangles of the upper circle
	const int offset2 = 3 * N_STRIPS;

	// Offset in indices array between triangles of the circles and triangles connecting the 2 circles
	const int offset3 = 6 * N_STRIPS;

	// Offset in vertices array between the two copies of same vertices with different normals
	const int offset4 = 2 * (N_STRIPS + 1) + 2;

	// Lower circle middle vertex
	M2_vertices[0].pos = glm::vec3(0.0, 0.0, 0.0);
	M2_vertices[0].norm = glm::vec3(0.0, -1.0, 0.0);
	M2_vertices[0].UV = glm::vec2(0.875, 0.125);

	// Upper circle middle vertex
	M2_vertices[offset1].pos = glm::vec3(0.0, HEIGHT, 0.0);
	M2_vertices[offset1].norm = glm::vec3(0.0, 1.0, 0.0);
	M2_vertices[offset1].UV = glm::vec2(0.625, 0.125);

	// I create vertices connected to the lower circle middle vertex (height = 0) and ones connected to the lower
	// circle middle vertex (height = HEIGHT)
	for (int i = 0; i < N_STRIPS + 1; i++)
	{
		M2_vertices[i + 1].pos =
			glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				0.0,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi));

		M2_vertices[i + 1].norm = glm::vec3(0.0, -1.0, 0.0);

		M2_vertices[i + 1].UV =
			glm::vec2(0.875 + 0.125 * sin((float)i / N_STRIPS * 2.0 * pi),
				0.125 + 0.125 * cos((float)i / N_STRIPS * 2.0 * pi));

		M2_vertices[offset1 + (i + 1)].pos =
			glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				HEIGHT,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi));

		M2_vertices[offset1 + (i + 1)].norm = glm::vec3(0.0, 1.0, 0.0);

		M2_vertices[offset1 + (i + 1)].UV =
			glm::vec2(0.625 + 0.125 * sin((float)i / N_STRIPS * 2.0 * pi),
				0.125 + 0.125 * cos((float)i / N_STRIPS * 2.0 * pi));
	}

	// I duplicate previous created vertices because of different normals
	for (int i = 0; i < N_STRIPS + 1; i++)
	{
		M2_vertices[offset4 + i].pos =
			glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				0.0,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi));

		M2_vertices[offset4 + i].norm =
			normalize(glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				0.0,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi)));

		M2_vertices[offset4 + i].UV = glm::vec2(0.5 + 0.5 * i / N_STRIPS, 0.5);

		M2_vertices[offset4 + N_STRIPS + 1 + i].pos =
			glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				HEIGHT,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi));

		M2_vertices[offset4 + N_STRIPS + 1 + i].norm =
			normalize(glm::vec3(RADIUS * sin((float)i / N_STRIPS * 2.0 * pi),
				0.0,
				RADIUS * cos((float)i / N_STRIPS * 2.0 * pi)));

		M2_vertices[offset4 + N_STRIPS + 1 + i].UV = glm::vec2(0.5 + 0.5 * i / N_STRIPS, 0.25);
	}

	// I connect the middle vertex of the circles to the border vertices
	for (int i = 0; i < N_STRIPS; i++)
	{
		M2_indices[3 * i + 0] = 0;
		M2_indices[3 * i + 1] = i + 1;
		M2_indices[3 * i + 2] = (i + 1) + 1;

		M2_indices[offset2 + (3 * i + 0)] = offset1;
		M2_indices[offset2 + (3 * i + 1)] = offset1 + i + 1;
		M2_indices[offset2 + (3 * i + 2)] = offset1 + ((i + 1) + 1);
	}

	// I connect the two circles
	for (int i = 0; i < N_STRIPS; i++)
	{
		M2_indices[offset3 + (6 * i + 0)] = offset4 + i;
		M2_indices[offset3 + (6 * i + 1)] = offset4 + (i + 1);
		M2_indices[offset3 + (6 * i + 2)] = offset4 + N_STRIPS + 1 + i;

		M2_indices[offset3 + (6 * i + 3)] = offset4 + (i + 1);
		M2_indices[offset3 + (6 * i + 4)] = offset4 + N_STRIPS + 1 + i;
		M2_indices[offset3 + (6 * i + 5)] = offset4 + N_STRIPS + 1 + (i + 1);
	}
}