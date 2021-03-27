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

    private:
      unsigned int mID;
  };
}

#endif
