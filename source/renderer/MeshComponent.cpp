#include "MeshComponent.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Environment.hpp"
#include "GameObject.hpp"

using UrsineRenderer::MeshComponent;

MeshComponent::MeshComponent()
  : mMode(RenderMode::eTRIANGLES)
  , mVAO(0)
  , mVBO(0)
  , mEBO(0)
{
  // Generate IDs for the vertex array, vertex buffer and element buffer.
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);
}

void MeshComponent::Render() const
{
  // Render this object for each Camera in the current scene.
  for(const auto& cam : env.GetCurrentScene()->GetObjectsOfType<Camera>())
  {
    if(GetCurrentShader() != nullptr)
    {
      // Activate the current shader.
      GetCurrentShader()->Activate();

      // Bind all textures on this mesh.
      for(unsigned int i = 0; i < mTextures.size(); ++i)
      {
        glActiveTexture(GL_TEXTURE0 + i);
        mTextures.at(i).Activate();
      }

      // Set the model matrix.
      if(GetCurrentShader()->IsUniformDefined("modelMatrix"))
      {
        GetCurrentShader()->SetMat4("modelMatrix", GetParent()->GetTransform());
      }

      // Set the view matrix for this Camera.
      if(GetCurrentShader()->IsUniformDefined("viewMatrix"))
      {
        GetCurrentShader()->SetMat4("viewMatrix", cam->GetViewMatrix());
      }

      // Create a perspective projection matrix and set it.
      // TODO: create a settings class for stuff like this
      if(GetCurrentShader()->IsUniformDefined("projectionMatrix"))
      {
        int w, h;
        glfwGetWindowSize(env.GetWindow(), &w, &h);

        // arguments:
        // field of view
        // aspect ratio
        // near plane
        // far plane
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.1f, 100.0f);
        GetCurrentShader()->SetMat4("projectionMatrix", proj);
      }

      // Draw the mesh.
      glBindVertexArray(mVAO);
      glDrawElements(mMode, mIndices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  }
}

void MeshComponent::AddVertex(const MeshVertex& aVertex)
{
  mVertices.emplace_back(aVertex);

  // Bind the vertex array.
  glBindVertexArray(mVAO);

  // Copy the vertex data into the buffer.
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER,
               mVertices.size() * sizeof(MeshVertex),
               &mVertices[0],
               GL_STATIC_DRAW);

  // Configure the vertex position attributes.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(0));

  // Configure the vertex color attributes.
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mColor)));

  // Configure the vertex texture coordinates.
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mTexCoords)));

  // Unbind the vertex array.
  glBindVertexArray(0);
}

void MeshComponent::AddIndex(unsigned int aIndex)
{
  mIndices.emplace_back(aIndex);

  // Bind the vertex array.
  glBindVertexArray(mVAO);

  // Copy the index data into the buffer.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mIndices.size() * sizeof(unsigned int),
               &mIndices[0],
               GL_STATIC_DRAW);

  // Unbind the vertex array.
  glBindVertexArray(0);
}

void MeshComponent::AddTexture(const Texture& aTexture)
{
  if(mTextures.size() >= 16)
  {
    std::cout << "Meshes can only support up to 16 textures!" << std::endl;
  }
  else
  {
    mTextures.emplace_back(aTexture);
  }
}
