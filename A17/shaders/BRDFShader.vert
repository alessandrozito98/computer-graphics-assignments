#version 450
#extension GL_ARB_separate_shader_objects : enable

	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

/**** Modify from here *****/

vec2 inTexCoord;
vec3 inNormal;

vec3 fragPos;
vec3 fragNorm;
vec2 fragTexCoord;

/**** To here *****/


	gl_Position = ubo.mvpMat * vec4(inPosition, 1.0);
	fragPos = (ubo.mMat * vec4(inPosition, 1.0)).xyz;
	fragNorm = mat3(ubo.nMat) * inNormal;
	fragTexCoord = inTexCoord;
}