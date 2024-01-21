#version 330

in vec2 tCoord;
out vec4 color;

uniform sampler2D samp;

void main(void) {
    color = texture(samp, tCoord);
}