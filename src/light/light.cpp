#include "light.h"

constexpr const char* LightTypeName[] = { "dirLights[", "pointLights[", "spotLights[" };

void BaseLight::copyFrom(BaseLight* light) {
	ambient = light->ambient;
	diffuse = light->diffuse;
	specular = light->specular;
}

const std::string BaseLight::_use(
	Shader* shader,
	const unsigned int index,
	const LIGHT_TYPE type
) {
	const std::string name = LightTypeName[(unsigned int)type] + std::to_string(index) + "].";

	shader
		->setUniform(name + "ambient", ambient)
		->setUniform(name + "diffuse", diffuse)
		->setUniform(name + "specular", specular);

	return name;
}
// ============================================================================
void DirLight::use(Shader* shader, const unsigned int index) {
	shader->setUniform(_use(shader, index, LIGHT_TYPE::DIR) + "direction", direction);
}
void DirLight::copyFrom(DirLight* light) {
	BaseLight::copyFrom(light);
	direction = light->direction;
}

// ========================================================================
void PointLight::use(Shader* shader, const unsigned int index) {
	_use(shader, index, LIGHT_TYPE::POINT);
}
void PointLight::copyFrom(PointLight* light) {
	BaseLight::copyFrom(light);
	position = light->position;
	constant = light->constant;
	linear = light->linear;
	quadratic = light->quadratic;
}

const std::string PointLight::_use(Shader* shader, const unsigned int index, const LIGHT_TYPE type) {
	const std::string name = BaseLight::_use(shader, index, type);

	shader
		->setUniform(name + "position", position)
		->setUniform(name + "constant", constant)
		->setUniform(name + "linear", linear)
		->setUniform(name + "quadratic", quadratic);

	return name;
}

// ====================================================================
void Spotlight::use(Shader* shader, const unsigned int index) {
	const std::string name = _use(shader, index, LIGHT_TYPE::SPOT);

	shader
		->setUniform(name + "direction", direction)
		->setUniform(name + "innerCutOff", innerCutOff)
		->setUniform(name + "outerCutOff", outerCutOff);
}
void Spotlight::copyFrom(Spotlight* light) {
	PointLight::copyFrom(light);
	direction = light->direction;
	innerCutOff = light->innerCutOff;
	outerCutOff = light->outerCutOff;
}
