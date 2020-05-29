#version 460 core

#define DIR_LIGHT_MAX_COUNT 3
#define POINT_LIGHT_MAX_COUNT 30
#define SPOT_LIGHT_MAX_COUNT 30

// 平行光
struct DirLight  {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);

// 点光源
struct PointLight {
    vec3 position;

    // 用于计算光强度
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir);

// 聚光
struct Spotlight {
    vec3 position;
    vec3 direction;

    float innerCutOff; // 内光切
    float outerCutOff; // 外光切

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
vec3 calcSpotLight(Spotlight light, vec3 normal, vec3 viewDir);

struct Material {
    sampler2D diffuse; // 漫反射
    sampler2D specular; // 镜面反射
    float shininess; // 反光度
};

in vec3 Normal; // 法向量
in vec3 FragPos; // 片段坐标
in vec2 TexCoords; // 纹理坐标

uniform vec3 viewPos; // 观察者位置
uniform Material material; // 材质

uniform DirLight dirLights[DIR_LIGHT_MAX_COUNT];
uniform PointLight pointLights[POINT_LIGHT_MAX_COUNT];
uniform Spotlight spotLights[SPOT_LIGHT_MAX_COUNT];
uniform int lightCount[3]; // 光源数量。 [DirLight, PointLight, Spotlight]

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    result += calcSpotLight(spotLights[0], norm, viewDir);
    for(int i = 0; i < min(lightCount[0], DIR_LIGHT_MAX_COUNT); i++)
        result += calcDirLight(dirLights[i], norm, viewDir);
    for(int i = 0; i < min(lightCount[1], POINT_LIGHT_MAX_COUNT); i++)
        result += calcPointLight(pointLights[i], norm, viewDir);
    for(int i = 0; i < min(lightCount[2], SPOT_LIGHT_MAX_COUNT); i++)
        result += calcSpotLight(spotLights[i], norm, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 光强
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(Spotlight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 光强
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
