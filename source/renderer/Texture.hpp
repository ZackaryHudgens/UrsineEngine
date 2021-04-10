#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace UrsineRenderer
{
  class Texture
  {
    public:
      Texture();

      void LoadImageFromFile(const std::string& aFilePath);
      void Activate() const;

      unsigned int GetHeight() const { return mHeight; }
      unsigned int GetWidth() const  { return mWidth; }

    private:
      unsigned int mID;
      unsigned int mWidth;
      unsigned int mHeight;
  };
}

#endif
