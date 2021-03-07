#include "MeshComponent.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cmrc/cmrc.hpp>

#include "Environment.hpp"
#include "GameObject.hpp"

CMRC_DECLARE(ShaderLib);

using UrsineRenderer::Camera;
using UrsineRenderer::MeshComponent;

MeshComponent::MeshComponent(const VertexList& aVertices,
                             const IndexList& aIndices,
                             const TextureList& aTextures)
  : mVAO(0)
  , mVBO(0)
  , mEBO(0)
  , mVertices(aVertices)
  , mIndices(aIndices)
  , mTextures(aTextures)
{
  // Add the base model shader.
  auto fs = cmrc::ShaderLib::get_filesystem();
  auto vertexFile = fs.open("shaders/ModelBase.vert");
  auto fragmentFile = fs.open("shaders/ModelBase.frag");
  AddShader(Shader(vertexFile.begin(), fragmentFile.begin()));

  Initialize();
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

void MeshComponent::PrivateRender() const
{
  for(const auto& shader : GetShaders())
  {
    shader.Activate();

    Camera* cam = env.GetCurrentScene()->GetCamera();

    int w, h;
    glfwGetWindowSize(env.GetWindow(), &w, &h);
    double aspectRatio = (double)w / (double)h;

    // Transform this mesh based on the GameObject's transform matrix
    // and the scene's Camera.
    //
    // TODO: handle multiple cameras?
    shader.SetMat4("model", GetParent()->GetTransform());
    shader.SetMat4("view", cam->GetViewMatrix());
    shader.SetMat4("projection", glm::perspective(glm::radians(cam->GetFOV()),
                                                  aspectRatio,
                                                  cam->GetNearPlane(),
                                                  cam->GetFarPlane()));

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

      shader.SetInt(name + number, i);
      glBindTexture(GL_TEXTURE_2D, mTextures[i].mId);

      glActiveTexture(GL_TEXTURE0);

      // Draw the mesh.
      glBindVertexArray(mVAO);
      glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  }
}
