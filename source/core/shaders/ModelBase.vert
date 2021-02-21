#version 330 core

/**
 * This shader is used to render all models loaded by the UrsineEngine.
 *
 * This is the vertex shader, which takes information about a single vertex
 * in a model and calculates where to place it in the scene.
 */

layout (location = 0) in vec3 aPosition;   // The vertex's position in 3D space
layout (location = 1) in vec3 aNormal;     // The vertex's normal vector
layout (location = 2) in vec2 aTexCoords;  // The vertex's corresponding texture coordinates

// Output variables
out vec3 position;   // Outputs the position vector to the fragment shader
out vec3 normal;     // Outputs the normal vector to the fragment shader
out vec2 texCoords;  // Outputs the texture coordinates to the fragment shader

// Uniform variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // Output variables to the fragment shader.
  position = vec3(model * vec4(aPosition, 1.0));
  normal = aNormal;
  texCoords = aTexCoords;

  // Set the position of this vertex in world space.
  gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
