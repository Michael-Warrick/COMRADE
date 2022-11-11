#version 410 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambientIntensity;
    vec3 diffuseIntensity;
    vec3 specularIntensity;
};

struct PointLight {
    vec3 position;

    vec3 ambientIntensity;
    vec3 diffuseIntensity;
    vec3 specularIntensity;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambientIntensity;
    vec3 diffuseIntensity;
    vec3 specularIntensity;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};

uniform vec3 viewPosition;
uniform Material material;

// Light types
uniform DirectionalLight directionalLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform bool enableSpotLight;
uniform SpotLight spotLight;

// Function prototypes
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

void main() 
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - FragPos);

    // Step 1 - Directional Light
    vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDir);

    // Step 2 - Point Lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++) 
    {
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // Step 3 - Spot Light
    if (enableSpotLight) 
    {
        result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) 
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // Combined result
    vec3 ambient = light.ambientIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specularIntensity * spec * vec3(texture(material.specular, TexCoords));

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection) 
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combined result
    vec3 ambient = light.ambientIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specularIntensity * spec * vec3(texture(material.specular, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDirection) 
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Spotlight radius calculation and smoothing
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Combined result
    vec3 ambient = light.ambientIntensity * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specularIntensity * spec * vec3(texture(material.specular, TexCoords));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}