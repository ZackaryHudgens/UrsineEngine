#include "Texture.hpp"

#include <GL/glew.h>

#include <il.h>
#include <ilu.h>

#include <iostream>

using UrsineRenderer::Texture;

Texture::Texture()
  : mID(0)
{
}

void Texture::LoadImageFromFile(const std::string& aFilePath)
{
  ILuint imageID;

  ilGenImages(1, &imageID);
  ilBindImage(imageID);

  // Attempt to load the image.
  ILboolean success = ilLoadImage(aFilePath.c_str());
  if(success == IL_TRUE)
  {
    // Attempt to convert the image to RGBA.
    success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if(success == IL_TRUE)
    {
      unsigned char* data = ilGetData();
      if(data != nullptr)
      {
        int w = ilGetInteger(IL_IMAGE_WIDTH);
        int h = ilGetInteger(IL_IMAGE_HEIGHT);

        // Generate an OpenGL texture.
        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        // Set texture wrapping and filtering options.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Copy the image data into the currently bound texture.
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     w,
                     h,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);

        ilDeleteImages(1, &imageID);
      }
      else
      {
        std::cout << "Error retrieving image data! " << ilGetError() << std::endl;
        ilDeleteImages(1, &imageID);
      }
    }
    else
    {
      std::cout << "Error converting image! " << ilGetError() << std::endl;
      ilDeleteImages(1, &imageID);
    }
  }
  else
  {
    std::cout << "Error loading image! " << ilGetError() << std::endl;
  }
}

void Texture::Activate() const
{
  glBindTexture(GL_TEXTURE_2D, mID);
}
