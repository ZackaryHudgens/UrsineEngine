#include "Texture.hpp"

#include <GL/glew.h>

#include <il.h>
#include <ilu.h>

#include <iostream>

using UrsineRenderer::Texture;
using UrsineRenderer::TextureData;

/**
 * A static cache of texture data; used to prevent reloading
 * the same textures over and over again.
 */
std::map<std::string, TextureData> gLoadedTextureMap;

/*****************************************************************************/
Texture::Texture()
{
  // Generate an OpenGL texture.
  glGenTextures(1, &mData.mID);
}

/*****************************************************************************/
void Texture::CreateTextureFromFile(const std::string& aFilePath)
{
  // If this image has already been loaded, don't load it again.
  auto foundTexture = gLoadedTextureMap.find(aFilePath);
  if(foundTexture != gLoadedTextureMap.end())
  {
    mData = foundTexture->second;
  }
  else
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
          mData.mWidth = ilGetInteger(IL_IMAGE_WIDTH);
          mData.mHeight = ilGetInteger(IL_IMAGE_HEIGHT);

          // Create the OpenGL texture.
          CreateTextureFromData(data, mData.mWidth, mData.mHeight);

          // Store this data in gLoadedTextureMap to avoid loading the same
          // image data.
          gLoadedTextureMap.emplace(aFilePath, mData);

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
}

/*****************************************************************************/
void Texture::CreateTextureFromData(unsigned char* aData,
                                    unsigned int aWidth,
                                    unsigned int aHeight)
{
  if(aData != nullptr)
  {
    mData.mWidth = aWidth;
    mData.mHeight = aHeight;

    // Bind the texture for use.
    glBindTexture(GL_TEXTURE_2D, mData.mID);

    // Set texture wrapping and filtering options.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Copy the image data into the currently bound texture.
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 mData.mWidth,
                 mData.mHeight,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 aData);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
}

/*****************************************************************************/
void Texture::Activate() const
{
  glBindTexture(GL_TEXTURE_2D, mData.mID);
}
