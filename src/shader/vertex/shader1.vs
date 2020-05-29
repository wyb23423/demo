#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalModel; // 法向量矩阵

out vec3 Normal; // 法向量
out vec3 FragPos; // 片段坐标
out vec2 TexCoords; // 纹理坐

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalModel * aNormal;
    TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}