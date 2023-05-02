#version 410 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPosition;

uniform bool renderDepthBuffer;

float near = 0.1;
float far = 1000.0;

float LinearizeDepth(float depth) 
{
   float z = depth * 2.0 - 1.0;

   return (2.0 * near * far) / (far + near -z * (far - near));
}

struct DirectionalLight {
   vec3 direction;

   vec3 ambientIntensity;
   vec3 diffuseIntensity;
   vec3 specularIntensity;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

uniform DirectionalLight directionalLight;
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

void main()
{
   if (!renderDepthBuffer) 
   {
      vec3 norm = normalize(Normal);
      vec3 viewDir = normalize(viewPosition - FragPos);

      vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDir);
      FragColor = vec4(result, 1.0);
   }
   else 
   {
      float depth = LinearizeDepth(gl_FragCoord.z) / far;
      FragColor = vec4(vec3(depth), 1.0);
   }
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) 
{
   vec3 lightDir = normalize(-light.direction);

   // Diffuse
   float diff = max(abs(dot(normal, lightDir)), 0.0);

   // Specular
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 64.0);

   if (texture(texture_diffuse1, TexCoords).a < 0.1) 
   {
      discard;
   }

   // Combined result
   vec3 ambient = light.ambientIntensity * vec3(texture(texture_diffuse1, TexCoords));
   vec3 diffuse = light.diffuseIntensity * diff * vec3(texture(texture_diffuse1, TexCoords));
   vec3 specular = light.specularIntensity * spec * vec3(texture(texture_specular1, TexCoords));

   return (ambient + diffuse + specular);
}