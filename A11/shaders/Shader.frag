#version 450layout(location = 0) in float real;layout(location = 1) in float img;
layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {	float m_real = 0.0f, m_img = 0.0f, temp; int i;		for(i = 0; i < 16; i++) {		if(m_real * m_real + m_img * m_img > 4.0) {			break;		}		temp = m_real * m_real - m_img * m_img + real; m_img = 2.0 * m_real * m_img + img;		m_real = temp;	} 	outColor = vec4((float(i % 5) + sin(gubo.time*6.28)) / 5.0, float(i % 10) / 10.0, float(i) / 15.0, 1.0);}