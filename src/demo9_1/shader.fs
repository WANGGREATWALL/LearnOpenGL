#version 330

in vec2 io_coordTex;

out vec4 io_colorOut;

uniform sampler2D samp;

void main(void) {
    io_colorOut = texture(samp, io_coordTex);
}