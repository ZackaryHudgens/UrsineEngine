#include "Texture.hpp"
#include "Environment.hpp"

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>

using gCore::Texture;

Texture::Texture()
  : mTextureID(0)
  , mTextureWidth(0)
  , mTextureHeight(0)
{
}

Texture::~Texture()
{
  FreeTexture();
}

bool Texture::LoadFromFile(const std::string& aFilePath)
{
  ILuint imgID = 0;
  ilGenImages(1, &imgID);
  ilBindImage(imgID);

  ilLoadImage(aFilePath.c_str());
  ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
  LoadFromPixels((GLuint*)(ilGetData()),
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT));
  ilDeleteImages(1, &imgID);

  ILenum error = ilGetError();
  if(error != IL_NO_ERROR)
  {
    std::cout << "Error loading image! " << iluErrorString(error) << std::endl;
    return false;
  }

  return true;
}

bool Texture::LoadFromPixels(GLuint* aPixelData, int aWidth, int aHeight)
{
  FreeTexture();

  mTextureWidth = aWidth;
  mTextureHeight = aHeight;
  glGenTextures(1, &mTextureID);
  glBindTexture(GL_TEXTURE_2D, mTextureID);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               mTextureWidth,
               mTextureHeight,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               aPixelData);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    std::cout << "Error loading texture! " << gluErrorString(error) << std::endl;
    return false;
  }

  return true;
}

void Texture::Render(const Vector2D& aLocation)
{
  if(mTextureID != 0)
  {
    glLoadIdentity();
    glTranslatef(aLocation.x, aLocation.y, 0.0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex2f(0.0, 0.0);

      glTexCoord2f(1.0, 0.0);
      glVertex2f(mTextureWidth, 0.0);

      glTexCoord2f(1.0, 1.0);
      glVertex2f(mTextureWidth, mTextureHeight);

      glTexCoord2f(0.0, 1.0);
      glVertex2f(0.0, mTextureHeight);
    glEnd();
  }
}

void Texture::RenderPortion(const Vector2D& aLocation, const SDL_Rect& aPortion)
{
  if(mTextureID != 0)
  {
    // Texture coordinates:
    GLfloat top = float(aPortion.y) / mTextureHeight;
    GLfloat bottom = float((aPortion.y + aPortion.h)) / mTextureHeight;
    GLfloat left = float(aPortion.x) / mTextureWidth;
    GLfloat right = float((aPortion.x + aPortion.w)) / mTextureWidth;

    // Vertex coordinates:
    GLfloat width = aPortion.w;
    GLfloat height = aPortion.h;
    
    glLoadIdentity();
    glTranslatef(aLocation.x, aLocation.y, 0.0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glBegin(GL_QUADS);
      glTexCoord2f(left, top);
      glVertex2f(0.0f, 0.0f);

      glTexCoord2f(right, top);
      glVertex2f(width, 0.0);

      glTexCoord2f(right, bottom);
      glVertex2f(width, height);

      glTexCoord2f(left, bottom);
      glVertex2f(0.0, height);
    glEnd();
  }
}

void Texture::FreeTexture()
{
  if(mTextureID != 0)
  {
    glDeleteTextures(1, &mTextureID);
    mTextureID = 0;
  }

  mTextureWidth = 0;
  mTextureHeight = 0;
}
