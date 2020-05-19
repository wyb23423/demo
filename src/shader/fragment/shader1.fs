#version 460 core

struct Material {
    vec3 ambient; // 环境光
    vec3 diffuse; // 漫反射
    vec3 specular; // 镜面反射
    float shininess; // 反光度
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform Material material;
uniform Light light;

void main() {
    vec3 normal = normalize(Normal); // 法向量
    vec3 lightDir = normalize(LightPos - FragPos); // 光照方向

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normalize(-FragPos), reflect(-lightDir, normal)), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = diff * light.diffuse * material.diffuse;
    vec3 specular = spec * light.specular * material.specular;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
