// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
#include <cmath>
const int N_STRIPS = 32;

void makeSpringCylinder(int iteration, float X, float Y, float Z, float YRotation) {

	const float RADIUS = 0.2f;
	//const int N_STRIPS = 32;
	const double pi = 3.14159265358979323846;

	int verticesOffset = iteration * (3 + N_STRIPS * 3);
	int previousVerticesOffset = (iteration - 1) * (3 + N_STRIPS * 3);
	int indicesOffset = (iteration - 1) * (N_STRIPS * 6);

	M4_vertices[verticesOffset + 0] = X;
	M4_vertices[verticesOffset + 1] = Y;
	M4_vertices[verticesOffset + 2] = Z;

	// I create a circle with N_STRIPS vertices
	for (int i = 0; i < N_STRIPS; i++)
	{
		float newX = RADIUS * cos((float)i / N_STRIPS * 2.0 * pi);
		float newY = Y + RADIUS * sin((float)i / N_STRIPS * 2.0 * pi);
		float newZ = 0.0;

		M4_vertices[verticesOffset + 3 * i + 3] = (newX * cos(YRotation) + newZ * sin(YRotation)) + X;
		M4_vertices[verticesOffset + 3 * i + 4] = newY;
		M4_vertices[verticesOffset + 3 * i + 5] = (newZ * cos(YRotation) - newX * sin(YRotation)) + Z;
	}

	// If this is not the first circle created, I connected it with the previous created one
	if (iteration > 0)
	{
		for (int i = 0; i < N_STRIPS; i++)
		{
			M4_indices[indicesOffset + (6 * i + 0)] = verticesOffset / 3 + i + 1;
			M4_indices[indicesOffset + (6 * i + 1)] = verticesOffset / 3 + (i + 1) % N_STRIPS + 1;
			M4_indices[indicesOffset + (6 * i + 2)] = previousVerticesOffset / 3 + i + 1;

			M4_indices[indicesOffset + (6 * i + 3)] = verticesOffset / 3 + (i + 1) % N_STRIPS + 1;
			M4_indices[indicesOffset + (6 * i + 4)] = previousVerticesOffset / 3 + i + 1;
			M4_indices[indicesOffset + (6 * i + 5)] = previousVerticesOffset / 3 + (i + 1) % N_STRIPS + 1;
		}
	}
}

void makeModels() {
	//// M1 : Cube
	// Replace the code below, that creates a simple square, with the one to create a cube.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)
	M1_vertices.resize(3 * 8);

	// first vertex of M1
	M1_vertices[0] = -1.0;
	M1_vertices[1] = -1.0;
	M1_vertices[2] = -1.0;

	// second vertex of M1
	M1_vertices[3] = -1.0;
	M1_vertices[4] = -1.0;
	M1_vertices[5] = 1.0;

	// third vertex of M1
	M1_vertices[6] = -1.0;
	M1_vertices[7] = 1.0;
	M1_vertices[8] = 1.0;

	// fourth vertex of M1
	M1_vertices[9] = -1.0;
	M1_vertices[10] = 1.0;
	M1_vertices[11] = -1.0;

	// fifth vertex of M1
	M1_vertices[12] = 1.0;
	M1_vertices[13] = -1.0;
	M1_vertices[14] = -1.0;

	// sixth vertex of M1
	M1_vertices[15] = 1.0;
	M1_vertices[16] = -1.0;
	M1_vertices[17] = 1.0;

	// seventh vertex of M1
	M1_vertices[18] = 1.0;
	M1_vertices[19] = 1.0;
	M1_vertices[20] = 1.0;

	// eighth vertex of M1
	M1_vertices[21] = 1.0;
	M1_vertices[22] = 1.0;
	M1_vertices[23] = -1.0;


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M1_indices.resize(3 * 12);

	// first triangle
	M1_indices[0] = 0;
	M1_indices[1] = 1;
	M1_indices[2] = 2;

	// second triangle
	M1_indices[3] = 2;
	M1_indices[4] = 3;
	M1_indices[5] = 0;

	// third triangle
	M1_indices[6] = 0;
	M1_indices[7] = 3;
	M1_indices[8] = 4;

	// fourth triangle
	M1_indices[9] = 4;
	M1_indices[10] = 3;
	M1_indices[11] = 7;

	// fifth triangle
	M1_indices[12] = 5;
	M1_indices[13] = 6;
	M1_indices[14] = 7;

	// sixth triangle
	M1_indices[15] = 7;
	M1_indices[16] = 4;
	M1_indices[17] = 5;

	// 7th triangle
	M1_indices[18] = 1;
	M1_indices[19] = 6;
	M1_indices[20] = 5;

	// 8th triangle
	M1_indices[21] = 1;
	M1_indices[22] = 2;
	M1_indices[23] = 6;

	// 9th triangle
	M1_indices[24] = 7;
	M1_indices[25] = 6;
	M1_indices[26] = 2;

	// 10th triangle
	M1_indices[27] = 3;
	M1_indices[28] = 2;
	M1_indices[29] = 7;

	// 11th triangle
	M1_indices[30] = 4;
	M1_indices[31] = 5;
	M1_indices[32] = 0;

	// 12th triangle
	M1_indices[33] = 1;
	M1_indices[34] = 0;
	M1_indices[35] = 5;





	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)

	const int n = 64;
	float radius = 1.0;
	float height = 1.0;
	float cx = 0, cy = 0, cz = -2.0;
	const double pi = 3.14159265358979323846;

	M2_vertices.resize((n + 1) * 2 * 3);

	// Vertices definitions
	//centro faccia sopra (vertice 0)
	M2_vertices[0] = cx;
	M2_vertices[1] = cy + height;
	M2_vertices[2] = cz;

	//vertici faccia sopra
	for (int i = 0; i < n; i++)
	{
		M2_vertices[(i + 1) * 3] = cx + radius * cos((float)i / n * pi*2.0);//x
		M2_vertices[(i + 1) * 3 + 1] = cy + height; //y
		M2_vertices[(i + 1) * 3 + 2] = cz + radius * sin((float)i / n * pi*2.0);//z
	}

	//centro faccia sotto (vertice n+1esimo)
	M2_vertices[(n + 1) * 3] = cx;
	M2_vertices[(n + 1) * 3 + 1] = cy - height;
	M2_vertices[(n + 1) * 3 + 2] = cz;

	//vertici faccia sotto
	for (int i = 0; i < n; i++)
	{
		M2_vertices[(n + 1) * 3 + (i + 1) * 3] = cx + radius * cos((float)i / n * pi*2.0);//x
		M2_vertices[(n + 1) * 3 + (i + 1) * 3 + 1] = cy - height; //y
		M2_vertices[(n + 1) * 3 + (i + 1) * 3 + 2] = cz + radius * sin((float)i / n * pi*2.0);//z
	}


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(3 * n * 4);

	// indices definitions
	//faccia sopra | indici vanno da 0 a n*3-1
	for (int i = 0; i < n; i++)
	{
		M2_indices[i * 3 + 0] = 0;
		M2_indices[i * 3 + 1] = i + 1;
		M2_indices[i * 3 + 2] = ((i + 1) % n) + 1;
	}

	//faccia sotto | indici vanno da n*3 a n*6-1
	for (int i = 0; i < n; i++)
	{
		M2_indices[n * 3 + i * 3 + 0] = n + 1;
		M2_indices[n * 3 + i * 3 + 1] = n + 1 + i + 1;
		M2_indices[n * 3 + i * 3 + 2] = n + 1 + ((i + 1) % n) + 1;
	}

	//facce laterali | indici vanno da n*6 a n*12-1
	for (int i = 0; i < n; i++)
	{
		M2_indices[n * 6 + i * 3 + 0] = i + 1;
		M2_indices[n * 6 + i * 3 + 1] = n + 1 + i + 1;
		M2_indices[n * 6 + i * 3 + 2] = ((i + 1) % n) + 1;
		/*M2_indices[n * 6 + i * 3 + 3] = ((i+1) % n) + 1;
		M2_indices[n * 6 + i * 3 + 4] = n+1 + i + 1;
		M2_indices[n * 6 + i * 3 + 5] = n+1 + ((i + 1) % n) + 1;*/

	}

	for (int i = 0; i < n; i++)
	{
		M2_indices[n * 9 + i * 3 + 0] = ((i + 1) % n) + 1;
		M2_indices[n * 9 + i * 3 + 1] = n + 1 + i + 1;
		M2_indices[n * 9 + i * 3 + 2] = n + 1 + ((i + 1) % n) + 1;
	}






	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	float verticiSopra = (float)3 * n * (n / 2) + 3;
	float indiciSopra = (float)3 * n * (n - 1);
	float triangoliSopra = verticiSopra / 3;
	const int f = 8;

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices components (3 * number of vertices)

	M3_vertices.resize((n * (n - 1) + 2) * 3);

	//vertici emisfero sopra

	for (int j = 0; j < n / 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			float angle = ((float)j / (n / 2)) * (pi / 2.0f);

			M3_vertices[(3 * n * j) + 3 * i + 0] =
				radius * cos(angle) * sin((float)i / n * 2.0 * pi);

			M3_vertices[(3 * n * j) + 3 * i + 1] =
				radius * sin(angle);

			M3_vertices[(3 * n * j) + 3 * i + 2] =
				radius * cos(angle) * cos((float)i / n * 2.0 * pi);
		}
	}

	//cima di sopra
	M3_vertices[3 * n * (n / 2) + 0] = 0.0;
	M3_vertices[3 * n * (n / 2) + 1] = radius;
	M3_vertices[3 * n * (n / 2) + 2] = 0.0;


	//vertici emisfero sotto

	for (int j = 1; j < n / 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			float angle = ((float)j / (n / 2)) * (pi / 2.0f);

			M3_vertices[verticiSopra + (3 * n * (j - 1)) + 3 * i + 0] =
				radius * cos(angle) * sin((float)i / n * 2.0 * pi);

			M3_vertices[verticiSopra + (3 * n * (j - 1)) + 3 * i + 1] =
				-radius * sin(angle);

			M3_vertices[verticiSopra + (3 * n * (j - 1)) + 3 * i + 2] =
				radius * cos(angle) * cos((float)i / n * 2.0 * pi);
		}
	}

	//cima sotto
	M3_vertices[verticiSopra + 3 * n * (n / 2 - 1) + 0] = 0.0;
	M3_vertices[verticiSopra + 3 * n * (n / 2 - 1) + 1] = -radius;
	M3_vertices[verticiSopra + 3 * n * (n / 2 - 1) + 2] = 0.0;


	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize((n * 2) * (n - 1) * 3);

	//traingoli emisfero sopra
	for (int j = 0; j < n / 2 - 1; j++)
	{
		for (int i = 0; i < n; i++)
		{
			M3_indices[6 * n * j + 6 * i + 0] = n * j + i;
			M3_indices[6 * n * j + 6 * i + 1] = n * j + (i + 1) % n;
			M3_indices[6 * n * j + 6 * i + 2] = n * j + n + i;

			M3_indices[6 * n * j + 6 * i + 3] = n * j + (i + 1) % n;
			M3_indices[6 * n * j + 6 * i + 4] = n * j + n + i;
			M3_indices[6 * n * j + 6 * i + 5] = n * j + n + ((i + 1) % n);
		}
	}

	//tringoli polo nord
	for (int i = 0; i < n; i++)
	{
		M3_indices[6 * n * (n / 2 - 1) + 3 * i + 0] =
			n * (n / 2 - 1) + i;

		M3_indices[6 * n * (n / 2 - 1) + 3 * i + 1] =
			n * (n / 2 - 1) + (i + 1) % n;

		M3_indices[6 * n * (n / 2 - 1) + 3 * i + 2] =
			n * (n / 2);
	}


	//triangoli emisfero sotto
	for (int i = 0; i < n; i++)
	{
		M3_indices[indiciSopra + 6 * i + 0] = i;
		M3_indices[indiciSopra + 6 * i + 1] = (i + 1) % n;
		M3_indices[indiciSopra + 6 * i + 2] = triangoliSopra + i;

		M3_indices[indiciSopra + 6 * i + 3] = (i + 1) % n;
		M3_indices[indiciSopra + 6 * i + 4] = triangoliSopra + i;
		M3_indices[indiciSopra + 6 * i + 5] = triangoliSopra + (i + 1) % n;
	}

	indiciSopra += n * 6;

	for (int j = 0; j < n / 2 - 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			M3_indices[indiciSopra + 6 * n * j + 6 * i + 0] =
				triangoliSopra + n * j + i;

			M3_indices[indiciSopra + 6 * n * j + 6 * i + 1] =
				triangoliSopra + n * j + (i + 1) % n;

			M3_indices[indiciSopra + 6 * n * j + 6 * i + 2] =
				triangoliSopra + n * j + n + i;

			M3_indices[indiciSopra + 6 * n * j + 6 * i + 3] =
				triangoliSopra + n * j + (i + 1) % n;

			M3_indices[indiciSopra + 6 * n * j + 6 * i + 4] =
				triangoliSopra + n * j + n + i;

			M3_indices[indiciSopra + 6 * n * j + 6 * i + 5] =
				triangoliSopra + n * j + n + ((i + 1) % n);
		}
	}

	//triangoli polo sud
	for (int i = 0; i < n; i++)
	{
		M3_indices[indiciSopra + 6 * n * (n / 2 - 2) + 3 * i + 0] =
			((n * (n - 1) + 1) - n) + i;

		M3_indices[indiciSopra + 6 * n * (n / 2 - 2) + 3 * i + 1] =
			((n * (n - 1) + 1) - n) + (i + 1) % n;

		M3_indices[indiciSopra + 6 * n * (n / 2 - 2) + 3 * i + 2] =
			(n * (n - 1) + 1);
	}







	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.
	const float SPRING_RADIUS = 3.0f;
	const int CYLINDERS_N = 300;
	const float ANGLES_BETWEEN_CYLINDERS = glm::radians(5.0f);
	const float SPRING_CENTER_X = 0.0f;
	const float SPRING_CENTER_Y = 0.0f;
	const float SPRING_CENTER_Z = 0.0f;
	const float Y_OFFSET = 0.02f;
	//const int N_STRIPS = 32;

	// I multiply 2 with the number of cylinder strips with the number  of cylinders.
	// I ignore top and bottom half faces of the cylinders because they are not present
	M4_vertices.resize(2 * N_STRIPS * 3 * CYLINDERS_N);

	// Faces number is the same of vertices number
	M4_indices.resize(2 * N_STRIPS * 3 * CYLINDERS_N);

	float currentAngle = 0.0f;
	float currentY = 0.0f;

	for (int i = 0; i < CYLINDERS_N; i++)
	{
		makeSpringCylinder(i, SPRING_CENTER_X - SPRING_RADIUS * cos(currentAngle), SPRING_CENTER_Y - currentY, SPRING_CENTER_Z + SPRING_RADIUS * sin(currentAngle), currentAngle);

		// I increase the angle between the cylinders in order to make the spring rotate
		currentAngle += ANGLES_BETWEEN_CYLINDERS;

		// I increase the y by an offset in order to make the spring growing
		currentY += Y_OFFSET;
	}
}


