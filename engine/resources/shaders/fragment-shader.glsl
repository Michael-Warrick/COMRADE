#version 410 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D crateTexture;
uniform sampler2D decalTexture;

uniform float mixAmount;

void main()
{
   FragColor = mix(texture(crateTexture, texCoord), texture(decalTexture, texCoord), mixAmount);
}