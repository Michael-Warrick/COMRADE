#version 410 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D crateTexture;
uniform sampler2D decalTexture;

void main()
{
   FragColor = mix(texture(crateTexture, texCoord), texture(decalTexture, texCoord), 0.5);
}