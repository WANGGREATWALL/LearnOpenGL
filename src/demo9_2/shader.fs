#version 330

in vec4 varyingColor;
// in vec2 tc;
out vec4 fragColor;

uniform sampler2D samp;

void main(void)
{
	// fragColor = texture(samp, tc);
	fragColor = varyingColor;
}