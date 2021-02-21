#version 330 core

/**
 * This shader is used to render all models loaded by the UrsineEngine.
 *
 * This is the fragment shader, which takes in some information about a
 * vertex and uses that to determine the color of each pixel between it
 * and other vertices.
 */

#define DIR_LIGHTS   0
#define POINT_LIGHTS 0
#define SPOT_LIGHTS  0

/**
 * A struct defining an object's behavior under light.
 */
struct Material
{
  sampler2D mDiffuseColor;   // Samples the object's texture at the given coordinates
  sampler2D mSpecularColor;  // Samples the object's specular map at the given coordinates
  float mShininess;          // The degree to which light scatters on the object
};

/**
* A struct representing a global, directional light source.
*/
struct DirectionalLight
{
  vec3 mDirection;
  vec3 mColor;

  vec3 mAmbientIntensity;
  vec3 mDiffuseIntensity;
  vec3 mSpecularIntensity;
};

/**
* A struct representing a light source that casts light in all directions.
*/
struct PointLight
{
  vec3 mPosition;
  vec3 mColor;

  vec3 mAmbientIntensity;
  vec3 mDiffuseIntensity;
  vec3 mSpecularIntensity;

  float mConstant;
  float mLinear;
  float mQuadratic;
};

/**
* A struct representing a light with a set position that only casts in one direction.
*/
struct SpotLight
{
  vec3 mPosition;
  vec3 mDirection;
  vec3 mColor;

  vec3 mAmbientIntensity;
  vec3 mDiffuseIntensity;
  vec3 mSpecularIntensity;

  float mHardCutoffAngle;
  float mGradientCutoffAngle;
};

// Input variables
in vec3 position;    // The position vector for this vertex
in vec3 normal;      // The normal vector for this vertex
in vec2 texCoords;   // The texture coordinates for this vertex

// Output variables
out vec4 fragColor;  // The final output color.

// Uniform variables
uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight dirLights[DIR_LIGHTS];
uniform PointLight pointLights[POINT_LIGHTS];
uniform SpotLight spotLights[SPOT_LIGHTS];

/**
 * Calculates the effect of a directional light on this fragment and returns the
 * resulting color.
 *
 * @param aLight The DirectionalLight to use.
 * @param aNormal The normal vector for this fragment.
 * @param aViewPos The position in world space of the viewer.
 */
vec3 CalcDirectionalLight(DirectionalLight aLight, vec3 aNormal, vec3 aViewPos)
{
  vec3 lightDir = normalize(-aLight.mDirection);
  float diffuseStrength = max(dot(aNormal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, aNormal);
  float specularStrength = pow(max(dot(aViewPos, reflectDir), 0.0), material.mShininess);

  vec3 ambient = aLight.mAmbientIntensity * aLight.mColor * vec3(texture(material.mDiffuseColor, texCoords));
  vec3 diffuse = aLight.mDiffuseIntensity * aLight.mColor * diffuseStrength * vec3(texture(material.mDiffuseColor, texCoords));
  vec3 specular = aLight.mSpecularIntensity * aLight.mColor * specularStrength * vec3(texture(material.mSpecularColor, texCoords));

  return (ambient + diffuse + specular);
}

/**
 * Calculates the effect of a point light on this fragment and returns the
 * resulting color.
 *
 * @param aLight The PointLight to use.
 * @param aNormal The normal vector for this fragment.
 * @param aFragPos The position in world space for this fragment.
 * @param aViewPos The position in world space of the viewer.
 */
vec3 CalcPointLight(PointLight aLight, vec3 aNormal, vec3 aFragPos, vec3 aViewPos)
{
  vec3 lightDir = normalize(aLight.mPosition - aFragPos);
  float diffuseStrength = max(dot(aNormal, lightDir) 0.0);

  vec3 reflectDir = reflect(-lightDir, aNormal);
  float specularStrength = pow(max(dot(aViewPos, reflectDir), 0.0), material.mShininess);

  float distanceToLight = length(aLight.mPosition - aFragPos);
  float attenuation = 1.0 / (aLight.mConstant + aLight.mLinear * distanceToLight + aLight.mQuadratic * (distanceToLight * distanceToLight));

  vec3 ambient = aLight.mAmbientIntensity * aLight.mColor * vec3(texture(material.mDiffuseColor, texCoords));
  vec3 diffuse = aLight.mDiffuseIntensity * aLight.mColor * diffuseStrength * vec3(texture(material.mDiffuseColor, texCoords));
  vec3 specular = aLight.mSpecularIntensity * aLight.mColor * specularStrength * vec3(texture(material.mSpecularColor, texCoords));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

/**
 * Calculates the effect of a spotlight on this fragment and returns the
 * resulting color.
 *
 * @param aLight The SpotLight to use.
 * @param aNormal The normal vector for this fragment.
 * @param aFragPos The position in world space for this fragment.
 * @param aViewPos The position in world space of the viewer.
 */
vec3 CalcSpotLight(SpotLight aLight, vec3 aNormal, vec3 aFragPos, vec3 aViewPos)
{
  vec3 lightDir = normalize(aLight.mPosition - aFragPos);  // The vector from this fragment to the light's position
  float theta = dot(lightDir, normalize(-aLight.mDirection));

  if(theta > aLight.mGradientCutoffAngle)  // Only apply this light if the fragment is within its radius
  {
    float diffuseStrength = max(dot(aNormal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, aNormal);
    float specularStrength = pow(max(dot(aViewPos, reflectDir), 0.0), material.mShininess);

    vec3 ambient = aLight.mAmbientIntensity * aLight.mColor * vec3(texture(material.mDiffuseColor, texCoords));
    vec3 diffuse = aLight.mDiffuseIntensity * aLight.mColor * diffuseStrength * vec3(texture(material.mDiffuseColor, texCoords));
    vec3 specular = aLight.mSpecularIntensity * aLight.mColor * specularStrength * vec3(texture(material.mSpecularColor, texCoords));

    float epsilon = aLight.mHardCutoffAngle - aLight.mGradientCutoffAngle;
    float gradient = clamp((theta - aLight.mGradientCutoffAngle) / epsilon, 0.0, 1.0);

    ambient *= gradient;
    diffuse *= gradient;
    specular *= gradient;

    return (ambient + diffuse + specular);
  }
  else
  {
    return vec3(0.0);
  }
}

void main()
{
  vec3 color = vec3(0.0);

  for(int i = 0; i < DIR_LIGHTS; i++)
  {
    color += CalcDirectionalLight(dirLights[i], normal, viewPosition);
  }
  for(int i = 0; i < POINT_LIGHTS; i++)
  {
    color += CalcPointLight(pointLights[i], normal, position, viewPosition);
  }
  for(int i = 0; i < SPOT_LIGHTS; i++)
  {
    color += CalcSpotLight(spotLights[i], normal, position, viewPosition);
  }

  fragColor = vec4(color, 1.0);
}
