#version 330

in vec2 tc;
out vec4 fragColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

uniform sampler2D t;	// for texture
uniform sampler2D h;	// for height map

void main(void)
{
	fragColor = texture(t, tc);
}
