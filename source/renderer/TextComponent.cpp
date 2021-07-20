#include "TextComponent.hpp"

#include <algorithm>
#include <iostream>

#include "Environment.hpp"

using UrsineRenderer::TextComponent;

/*****************************************************************************/
TextComponent::TextComponent()
{
  ShaderAdded.Connect(*this, [this](GraphicalComponent* aComponent,
                                    const Shader& aShader,
                                    const std::string& aName)
  {
    this->HandleShaderAdded(aComponent, aShader, aName);
  });

  ShaderRemoved.Connect(*this, [this](GraphicalComponent* aComponent,
                                      const std::string& aName)
  {
    this->HandleShaderRemoved(aComponent, aName);
  });

  ShaderChanged.Connect(*this, [this](GraphicalComponent* aComponent,
                                      const std::string& aName)
  {
    this->HandleShaderChanged(aComponent, aName);
  });
}

/*****************************************************************************/
void TextComponent::Render() const
{
  // First, enable blending.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Render each character in the string.
  for(const auto& textChar : mText)
  {
    // Find the mesh that corresponds to this character.
    auto findChar = [&](std::pair<Character, MeshComponent>& aData)
    {
      return aData.first.mChar == textChar;
    };

    auto foundChar = std::find_if(mCharacterMeshMap.begin(), mCharacterMeshMap.end(), findChar);
    if(foundChar != mCharacterMeshMap.end())
    {
      // First, clear all current vertices in this mesh.
      foundChar->second.GetVertices();
      // TODO: calculate vertices and set them whenever new text is assigned
      // and/or when loading a new font
    }
    else
    {
      std::cout << "Can't render character: " << textChar << std::endl;
    }
  }

  // Disable blending.
  glDisable(GL_BLEND);
}

/*****************************************************************************/
bool TextComponent::SetFont(const std::string& aFontPath)
{
  // First, unload whatever font is currently loaded.
  FT_Done_Face(mCurrentFont);

  bool success = true;

  if(FT_New_Face(*env.GetFontLibrary(), aFontPath.c_str(), 0, &mCurrentFont))
  {
    success = false;

    std::cout << "Error loading font: " << aFontPath << std::endl;
  }
  else
  {
    // By default, set the font to size 12.
    SetSize(12);
  }

  return success;
}

/*****************************************************************************/
bool TextComponent::SetSize(unsigned int aSize)
{
  bool success = true;

  // This function takes the face, the width, and the height as parameters.
  // By setting the width to 0, Freetype will automatically calculate the
  // width of the character glyphs according to the height.
  if(FT_Set_Pixel_Sizes(mCurrentFont, 0, aSize))
  {
    success = false;

    std::cout << "Couldn't set font size; no font specified " <<
                 "or font loaded improperly!" << std::endl;
  }
  else
  {
    LoadCharacters();
  }

  return success;
}

/*****************************************************************************/
void TextComponent::LoadCharacters()
{
  // Clear out the current character meshes.
  mCharacterMeshMap.clear();

  // Before loading any data, we need to tell OpenGL to unpack
  // pixel data in a certain way to correctly load the font file.
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Create a texture for each of the first 128 ASCII characters.
  // TODO: how do I support Unicode?
  for(unsigned int i = 0; i < 128; ++i)
  {
    if(FT_Load_Char(mCurrentFont, (char)i, FT_LOAD_RENDER))
    {
      // We failed to load this specific character, but should keep
      // trying to load the rest of them.
      std::cout << "Error loading character: " << (char)i << std::endl;
      continue;
    }

    // Create a texture for this character.
    Texture charTexture;
    unsigned char* charData = mCurrentFont->glyph->bitmap.buffer;
    unsigned int charWidth = mCurrentFont->glyph->bitmap.width;
    unsigned int charHeight = mCurrentFont->glyph->bitmap.rows;
    unsigned int charXBearing = mCurrentFont->glyph->bitmap_left;
    unsigned int charYBearing = mCurrentFont->glyph->bitmap_top;
    unsigned int charAdvance = mCurrentFont->glyph->advance.x;

    // Each color in the character image is represented by a single byte;
    // for this reason, we load each byte of the image as a single
    // color value (instead of the default 4 values: RGBA).
    charTexture.SetLoadFormat(GL_RED);
    charTexture.CreateTextureFromData(charData, charWidth, charHeight);

    // Create a Character struct with this data.
    Character newChar;
    newChar.mChar = (char)i;
    newChar.mWidth = charWidth;
    newChar.mHeight = charHeight;
    newChar.mXBearing = charXBearing;
    newChar.mYBearing = charYBearing;
    newChar.mAdvance = charAdvance;

    // Create a new mesh for this character.
    MeshComponent charMesh;
    charMesh.AddTexture(charTexture);

    for(const auto& shader : mShaderMap)
    {
      charMesh.AddShader(shader.first, shader.second);
      if(&(shader.second) == mCurrentShader)
      {
        charMesh.SetCurrentShader(shader.first);
      }
    }

    // Though the vertices may change, the indexes will not, since each
    // character is rendered to a simple quad.
    charMesh.AddIndex(0);
    charMesh.AddIndex(1);
    charMesh.AddIndex(3);
    charMesh.AddIndex(1);
    charMesh.AddIndex(2);
    charMesh.AddIndex(3);

    mCharacterMeshMap.emplace(newChar, charMesh);
  }

  // Go back to loading pixel data normally.
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

/*****************************************************************************/
void TextComponent::HandleShaderAdded(GraphicalComponent* aComponent,
                                      const Shader& aShader,
                                      const std::string& aName)
{
  if(aComponent == this)
  {
    for(auto& mesh : mCharacterMeshMap)
    {
      mesh.second.AddShader(aName, aShader);
    }
  }
}

/*****************************************************************************/
void TextComponent::HandleShaderRemoved(GraphicalComponent* aComponent,
                                        const std::string& aName)
{
  if(aComponent == this)
  {
    for(auto& mesh : mCharacterMeshMap)
    {
      mesh.second.RemoveShader(aName);
    }
  }
}

/*****************************************************************************/
void TextComponent::HandleShaderChanged(GraphicalComponent* aComponent,
                                        const std::string& aName)
{
  if(aComponent == this)
  {
    for(auto& mesh : mCharacterMeshMap)
    {
      mesh.second.SetCurrentShader(aName);
    }
  }
}
