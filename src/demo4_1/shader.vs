#version 330

layout (location=0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varingColor;

void main(void) {
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
    varingColor = vec4(position, 1.0f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 0.5f);
}