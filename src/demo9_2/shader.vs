#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex_coord;
// out vec2 tc;

out vec4 varyingColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
	// tc = tex_coord;
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0f);
}