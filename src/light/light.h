#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <glm\ext\vector_float3.hpp>
#include "../shader/shader.h"

static enum class LIGHT_TYPE { DIR, POINT, SPOT };

class BaseLight {
public:
	glm::vec3 ambient = glm::vec3(0.0f, 0.0f, 0.0f); // 环境光
	glm::vec3 diffuse = glm::vec3(0.0f, 0.0f, 0.0f); // 漫反射
	glm::vec3 specular = glm::vec3(0.0f, 0.0f, 0.0f); // 镜面光

	virtual void use(Shader* shader, const unsigned int index) = 0;
	void copyFrom(BaseLight* light);

protected:
	const std::string _use(Shader* shader, const unsigned int index, const LIGHT_TYPE type);
};

// 平行光
class DirLight : public BaseLight {
public:
	glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f); // 方向(从光源出发)

	virtual void use(Shader* shader, const unsigned int index);
	void copyFrom(DirLight* light);
};

// 点光源
class PointLight: public BaseLight {
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f); // 位置

	// 用于计算光强度
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	virtual void use(Shader* shader, const unsigned int index);
	void copyFrom(PointLight* light);

protected:
	const std::string _use(Shader* shader, const unsigned int index, const LIGHT_TYPE type);
};

// 聚光
class Spotlight : public PointLight {
public:
	glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f); // 方向(从光源出发)

	float innerCutOff = 0.0f; // 内圆锥角度值
	float outerCutOff = 0.0f; // 外圆锥角度值

	virtual void use(Shader* shader, const unsigned int index);
	void copyFrom(Spotlight* light);
};

#endif