#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "../mesh/mesh.h"

static map<const string, ModelData*> MODEL_CACHE;

static vector<Texture*> loadMaterialTextures(
	const aiMaterial* mat,
	const aiTextureType type,
	const string directory,
	const unsigned int start = 0
) {
	vector<Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture* texture = new Texture((directory + '/' + str.C_Str()).c_str());
		texture->unit = i + start;
		texture->type = type;
		texture->use();
		textures.push_back(texture);
	}

	return textures;
}

static Mesh* processMesh(aiMesh* mesh, const aiScene* scene, const string directory) {
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture*> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// 处理顶点位置、法线和纹理坐标
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertex.texCoords = glm::vec2(0.0f, 0.0f);
		if (mesh->mTextureCoords[0]) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	// 处理索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// 处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, directory);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, directory, textures.size());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return new Mesh(vertices, textures, indices);
}

static void processNode(
	aiNode* node,
	const aiScene* scene,
	vector<Mesh*>* const meshes,
	const string directory
) {
	unsigned int i;
	// 处理节点所有的网格（如果有的话）
	for (i = 0; i < node->mNumMeshes; i++) {
		meshes->push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene, directory));
	}
	// 接下来对它的子节点重复这一过程
	for (i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, meshes, directory);
	}
}

// ====================================================
ModelData* loadModel(const string path, unsigned int pFlags) {
	if (MODEL_CACHE.count(path)) {
		return MODEL_CACHE.at(path);
	}

	// 超过设置的最大缓存量, 先清空数据
	if (MODEL_CACHE.size() >= CACHE_MAX_SIZE) {
		clearModelCache();
	}

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, pFlags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return NULL;
	}

	vector<Mesh*>* meshes = new vector<Mesh*>();
	processNode(scene->mRootNode, scene, meshes, path.substr(0, path.find_last_of('/')));

	ModelData* modelData = (ModelData*)malloc(sizeof(modelData));
	modelData->data = meshes;
	modelData->count = 0;
	MODEL_CACHE[path] = modelData;

	return modelData;
}

bool deleteModelCache(const string path) {
	if (!MODEL_CACHE.count(path)) {
		return false;
	}

	ModelData* modelData = MODEL_CACHE.at(path);
	if (--modelData->count <= 0) {
		for (unsigned i = 0; i < modelData->data->size(); i++) {
			delete modelData->data->at(i);
		}
		delete modelData->data;

		MODEL_CACHE.erase(path);
	}

	return true;
}

void clearModelCache() {
	if (MODEL_CACHE.size() < 1) {
		return;
	}

	map<const string, ModelData*>::iterator iter;
	for (iter = MODEL_CACHE.begin(); iter != MODEL_CACHE.end(); iter++) {
		ModelData* modelData = iter->second;
		for (unsigned i = 0; i < modelData->data->size(); i++) {
			delete modelData->data->at(i);
		}
		delete modelData->data;
	}

	MODEL_CACHE.clear();
}

