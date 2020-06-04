#pragma once

#ifndef LOADER_H
#define LOADER_H

#include <map>
#include <vector>
#include <assimp/postprocess.h>

using namespace std;

static constexpr int CACHE_MAX_SIZE = 5000; // 最大缓存数
// =========================================图片
struct ImageData
{
	int count; // 使用次数
	int width;
	int height;
	unsigned int format;
	unsigned char* data;
};
// 加载图片数据。如果已存在直接返回缓存数据
ImageData* loadImage(const char* filename);
// 根据键名删除图片缓存数据
bool deleteImageCache(const char* filename);
// 清空图片缓存数据
void clearImageCahe();

// =========================================模型
class Mesh;

struct ModelData {
	vector<Mesh*>* data;
	int count; // 使用次数
};

// 加载模型
ModelData* loadModel(const string path, unsigned int pFlags = aiProcess_Triangulate);
// 移出模型缓存
bool deleteModelCache(const string path);
// 清空缓存
void clearModelCache();

#endif
