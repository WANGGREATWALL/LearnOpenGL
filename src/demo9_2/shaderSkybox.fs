#version 330

in vec3 tc;
out vec4 fragColor;

uniform mat4 v_matrix;
uniform mat4 p_matrix;
uniform samplerCube samp;

void main(void)
{
	fragColor = texture(samp,tc);
}