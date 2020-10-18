#include "MeshComponent.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.hpp"

using core::MeshComponent;

MeshComponent::MeshComponent(const std::vector<MeshVertex>& aVertices,
                             const std::vector<unsigned int> aIndices,
                             const std::vector<MeshTexture> aTextures)
  : mVAO(0)
  , mVBO(0)
  , mEBO(0)
  , mVertices(aVertices)
  , mIndices(aIndices)
  , mTextures(aTextures)
{
  Initialize();
}

void MeshComponent::Render() const
{
  // Temporary? Used to count the number of diffuse/specular
  // textures provided with this mesh.
  if(GetShader() != nullptr)
  {
    GetShader()->Activate();

    // Transform this mesh based on the GameObject's transform matrix.
    glm::mat4 model = GetParent()->GetTransform();
    glm::vec3 axis(0.5f, 1.0f, 0.0f);
    GetShader()->SetMat4("transform", glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), axis));
    //GetShader()->SetMat4("transform", GetParent()->GetTransform());

    //TODO: temporary; this should go somewhere else
    GetShader()->SetMat4("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)));
    GetShader()->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

    unsigned int diffuse = 1, specular = 1;
    for(unsigned int i = 0; i < mTextures.size(); ++i)
    {
      glActiveTexture(GL_TEXTURE0 + i);

      std::string number;
      std::string name = mTextures[i].mType;
      if(name == "texture_diffuse")
      {
        number = std::to_string(diffuse++);
      }
      else if(name == "texture_specular")
      {
        number = std::to_string(specular++);
      }

      GetShader()->SetInt(name + number, i);
      glBindTexture(GL_TEXTURE_2D, mTextures[i].mId);
    }
  }

  glActiveTexture(GL_TEXTURE0);

  // Draw the mesh.
  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void MeshComponent::Initialize()
{
  // Generate IDs for the vertex array, vertex buffer and element buffer.
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);

  // Bind the vertex array.
  glBindVertexArray(mVAO);

  // Load the vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER,
               mVertices.size() * sizeof(MeshVertex),
               &mVertices[0],
               GL_STATIC_DRAW);

  // Load the element data.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mIndices.size() * sizeof(unsigned int),
               &mIndices[0],
               GL_STATIC_DRAW);

  // Set the vertex position attributes.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(0));

  // Set the vertex normal attributes.
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mNormal)));

  // Set the texture coordinate attributes.
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
