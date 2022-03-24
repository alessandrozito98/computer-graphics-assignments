using namespace glm;

mat4 i4 = mat4(1);

// Rotate 45 degrees around an arbitrary axis passing through (1,0,-1). The x-axis can be aligned to the arbitrary axis after a rotation of 30 degrees around the z-axis, and then -60 degrees around the y-axis.

mat4 MT1_2 = translate(i4, vec3(1, 0, -1));
mat4 MT1_3 = rotate(i4, radians(45.0f), vec3(1, 0, 0));
mat4 MT1_4 = rotate(i4, radians(-60.0f), vec3(0, 1, 0));
mat4 MT1_5 = rotate(i4, radians(30.0f), vec3(0, 0, 1));
mat4 MT1 = MT1_2 * MT1_4 * MT1_5 * MT1_3 * inverse(MT1_5) * inverse(MT1_4) * inverse(MT1_2);
			   
// Half the size of an object, using as fixed point (5,0,-2)	
mat4 MT2_2 = translate(i4, vec3(5, 0, -2));
mat4 MT2_3 = scale(i4, vec3(0.5f, 0.5f, 0.5f));

mat4 MT2 = MT2_2 * MT2_3 * inverse(MT2_2);

// Mirror the starship along a plane passing through (1,1,1), and obtained rotating 15 degree around the x axis the xz plane

mat4 MT3_2 = translate(i4, vec3(1, 1, 1));
mat4 MT3_3 = scale(i4, vec3(1, -1, 1));
mat4 MT3_4 = rotate(i4, radians(15.0f), vec3(1, 0, 0));

mat4 MT3 = MT3_2 * MT3_4 * MT3_3 * inverse(MT3_4) * inverse(MT3_2);


// Apply the inverse of the following sequence of transforms: Translation of (0, 0, 5) then rotation of 30 degree around the Y axis, and finally a uniform scaling of a factor of 3.

mat4 MT4_1 = translate(i4, vec3(0, 0, 5));
mat4 MT4_2 = rotate(i4, radians(30.0f), vec3(0, 1, 0));
mat4 MT4_3 = scale(i4, vec3(3, 3, 3));



mat4 MT4 = inverse(MT4_1) * inverse(MT4_2) * inverse(MT4_3);

