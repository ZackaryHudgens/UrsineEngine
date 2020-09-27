#include "GraphicalComponentWrapper.hpp"

using py::GraphicalComponentWrapper;

GraphicalComponentWrapper::GraphicalComponentWrapper()
  : GraphicalComponent()
{
}

void GraphicalComponentWrapper::SetShader_(Shader& aShader)
{
  SetShader(&aShader);
}

void GraphicalComponentWrapper::DisableShader_()
{
  SetShader(nullptr);
}
