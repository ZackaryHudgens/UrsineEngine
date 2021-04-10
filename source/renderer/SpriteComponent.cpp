#include "SpriteComponent.hpp"

using UrsineRenderer::SpriteComponent;

SpriteComponent::SpriteComponent()
  : GraphicalComponent()
{
}

void SpriteComponent::Render() const
{
  mMesh.Render();
}

void SpriteComponent::SetTexture(const Texture& aTexture)
{
  // Remove any old textures.
  mMesh.GetTextures().clear();

  // Add the new texture.
  mMesh.AddTexture(aTexture);

  // By default, render the entire texture.
  SetRenderDimensions(0, 0, aTexture.GetWidth(), aTexture.GetHeight());
}

void SpriteComponent::SetRenderDimensions(unsigned int aX,
                                          unsigned int aY,
                                          unsigned int aWidth,
                                          unsigned int aHeight)
{
  // First, normalize the width and height.
  double magnitude = std::pow(aWidth, 2) + std::pow(aHeight, 2);
  magnitude = std::sqrt(magnitude);

  double normalizedWidth = aWidth / magnitude;
  double normalizedHeight = aHeight / magnitude;

  // Next, use the normalized width and height to create a rectangle.
  MeshVertex vertex;
  vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);  // bottom left
  vertex.mTexCoords = glm::vec2(aX, aY);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(normalizedWidth, 0.0, 0.0);  // bottom right
  vertex.mTexCoords = glm::vec2(aX + aWidth, aY);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(normalizedWidth, normalizedHeight, 0.0);  // top right
  vertex.mTexCoords = glm::vec2(aX + aWidth, aY + aHeight);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(0.0, normalizedHeight, 0.0);  // bottom right
  vertex.mTexCoords = glm::vec2(aX, aY + aHeight);
  mMesh.AddVertex(vertex);
}
