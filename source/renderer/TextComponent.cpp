#include "TextComponent.hpp"

#include <iostream>

#include "Environment.hpp"

using UrsineRenderer::TextComponent;

/**
 * A static cache of font data; used to prevent reloading
 * the same fonts over and over again.
 */
std::map<std::string, FT_Face> gLoadedFontsMap;

/*****************************************************************************/
TextComponent::TextComponent()
{
}

/*****************************************************************************/
void TextComponent::Render() const
{
  mMesh.Render();
}

/*****************************************************************************/
bool TextComponent::SetFont(const std::string& aFontPath)
{
  bool success = true;

  // If this font has already been loaded, don't load it again.
  auto foundFont = gLoadedFontsMap.find(aFontPath);
  if(foundFont != gLoadedFontsMap.end())
  {
    mCurrentFont = aFontPath;
  }
  else
  {
    FT_Face newFace;

    if(!FT_New_Face(*env.GetFontLibrary(), aFontPath.c_str(), 0, &newFace))
    {
      success = false;

      std::cout << "Error loading font: " << aFontPath << std::endl;
    }
    else
    {
      gLoadedFontsMap.emplace(aFontPath, newFace);
      mCurrentFont = aFontPath;

      // By default, set the font to size 12.
      SetSize(12);
    }
  }

  return success;
}

/*****************************************************************************/
bool TextComponent::SetSize(unsigned int aSize)
{
  bool success = true;

  if(!mCurrentFont.empty())
  {
    FT_Set_Pixel_Sizes(gLoadedFontsMap.at(mCurrentFont), 0, aSize);
    GenerateTextureAtlas();
  }
  else
  {
    success = false;

    std::cout << "Couldn't set font size; no font specified!" << std::endl;
  }

  return success;
}

/*****************************************************************************/
void TextComponent::GenerateTextureAtlas()
{
  // First, determine the minimum width and height necessary to
  // place all glyphs into a texture.
  int atlasWidth = 0;
  int atlasHeight = 0;

  // Load a glyph for each ASCII character from 32 to 127; the first 31
  // ASCII characters are control codes and unnecessary.
  // TODO: how do I handle non-English text? Or emojis?
  for(int i = 32; i < 128; ++i)
  {
    if(FT_Load_Char(gLoadedFontsMap.at(mCurrentFont), i, FT_LOAD_RENDER))
    {
      std::cout << "Faild to load character: " << (char)i << std::endl;
      continue;  // If one character failed to load, keep trying to load the rest.
    }

    atlasWidth += gLoadedFontsMap.at(mCurrentFont)->glyph->bitmap.width;

    int numRows = gLoadedFontsMap.at(mCurrentFont)->glyph->bitmap.rows;
    atlasHeight = std::max(atlasHeight, numRows);
  }
}
