#ifndef POINTLIGHTCOMPONENT_HPP
#define POINTLIGHTCOMPONENT_HPP

#include "LightComponent.hpp"

namespace UrsineRenderer
{
  class PointLightComponent : public LightComponent
  {
    public:
      PointLightComponent();

      double GetLinearTerm() const     { return mLinearTerm; }
      void SetLinearTerm(double aTerm) { mLinearTerm = aTerm; }

      double GetQuadraticTerm() const     { return mQuadraticTerm; }
      void SetQuadraticTerm(double aTerm) { mQuadraticTerm = aTerm; }

    private:
      double mLinearTerm;
      double mQuadraticTerm;
  };
}

#endif
