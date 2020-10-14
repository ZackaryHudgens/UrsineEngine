#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
  FragColor = texture(texture_diffuse1, TexCoords);
  //FragColor = vec4(0.5, 0.2, 0.6, 1.0);
}
