#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<Texture*> textures, vector<unsigned int> indices) {
    this->vertices = vertices;
    this->textures = textures;
    this->indices = indices;

    setupMesh();
}

Mesh::Mesh(Mesh* mesh) {
    vertices = mesh->vertices;
    textures = mesh->textures;
    indices = mesh->indices;

    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    for (unsigned i = 0; i < textures.size(); i++) {
        delete textures[i];
    }
}

void Mesh::paint(Shader* shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++) {
        // 绑定相应的纹理单元
        textures[i]->bind();

        string number = "";
        string name = "";
        switch (textures[i]->type)
        {
        case aiTextureType_DIFFUSE:
            number = to_string(diffuseNr++);
            name = "texture_diffuse";
            break;
        case aiTextureType_SPECULAR:
            number = to_string(specularNr++);
            name = "texture_specular";
            break;
        default:
            cout << "Unknown type: " << i << endl;
            continue;
        }

        shader->setUniform((name + number).c_str(), (int)textures[i]->unit);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

    // always good practice to set everything back to defaults once configured.
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);

     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);

     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

     // 顶点位置
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
     // 顶点法线
     glEnableVertexAttribArray(1);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
     // 顶点纹理坐标
     glEnableVertexAttribArray(2);
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

     glBindVertexArray(0);
}
