#version 460 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform vec3 objColor;
uniform vec3 lightColor;

void main() {
    vec3 norm = normalize(Normal); // 法向量
    vec3 lightDir = normalize(LightPos - FragPos); // 光照方向

    float diff = max(dot(norm, lightDir), 0.0); // 漫反射

    // 镜面反射
    float specularStrength = 0.5; // 高光强度
    // 32 --- 高光的反光度
    float spec = pow(max(dot(normalize(-FragPos), reflect(-lightDir, norm)), 0.0), 32);

    float ambientStrength = 0.1; // 环境光强度

    vec3 result = (ambientStrength + diff + spec * specularStrength) * lightColor * objColor;

    FragColor = vec4(result, 1.0);
}