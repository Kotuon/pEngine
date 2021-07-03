#version 330 core

in vec3 position;
in vec3 scale;

void main() {
    gl_Position = vec4(position.x * scale.x, position.y * scale.y, position.z * scale.z, 1.f);
}

