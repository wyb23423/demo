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
bool deleteModelCache(const char* path);
// 清空缓存
void clearModelCache();
// 通过meshs数据绘制
void paintModel(vector<Mesh*>& meshs);

#endif