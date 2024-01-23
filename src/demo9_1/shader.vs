#version 330

layout (location=0) in vec3 position;
layout (location=1) in vec2 coordTex;

out vec2 io_coordTex;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform sampler2D samp;

void main(void) {
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	io_coordTex = coordTex;
}