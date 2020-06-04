#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
 
// 加载模型
vector<Mesh*>* loadModel(const string path, unsigned int pFlags = aiProcess_Triangulate);
// 移出模型缓存
bool deleteModelCache(const string path);
// 清空缓存
void clearModelCache();
// 通过meshs数据绘制
void paintModel(const vector<Mesh*>* meshs, Shader* shader);
void paintModel(const string path, Shader* shader);

#endif