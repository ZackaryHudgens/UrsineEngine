#version 330 core

// Output variables
out vec4 fragColor;

// Uniform variables
uniform vec3 defaultColor;

void main()
{
  fragColor = vec4(defaultColor, 1.0);
}
