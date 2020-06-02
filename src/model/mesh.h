#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glm\ext\vector_float3.hpp>
#include <glm\ext\vector_float2.hpp>

#include "../texture/texture.h"
#include "../shader/shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    /*  网格数据  */
    vector<unsigned int> indices;
    vector<Texture*> textures;
    vector<Vertex> vertices;

    Mesh(vector<Vertex> vertices, vector<Texture*> textures, vector<unsigned int> indices);
    ~Mesh();

    void paint(Shader* shader);

private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO; // 顶点数组对象、顶点缓冲对象、索引缓冲对象

    void setupMesh();
};

#endif