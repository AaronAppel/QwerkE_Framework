#pragma once

// #NOTE This data should mirror ShaderVariableDoc.txt.
// #NOTE Do not include prefixes. They are auto-added at runtime and exist in GraphicsHelpers.h/cpp

/* Attributes */
#define vertexPosition "Position"
#define vertexColour "Color"
#define vertexUV "UV"
#define vertexNormal "Normal"
#define vertexTangent "Tangent"
#define vertexBitangent "Bitangent"

/* Uniforms */
// Transforms
#define worldMatrix "WorldMat"
#define viewMatrix "ViewMat"
#define projectionMatrix "ProjMat"
#define transform2D "Transform2D"

// Materials
#define TexturePrefix "Texture"
#define AmbientName "AmbientTexture"
#define DiffuseName "DiffuseTexture"
#define SpecularName "SpecularTexture"
#define EmissiveName "EmissiveTexture"
#define HeightName "HeightTexture"
#define NormalsName "NormalsTexture"
#define ShininessName "ShininessTexture"
#define OpacityName "OpacityTexture"
#define DisplacementName "DisplacementTexture"
#define LightMapName "LightMapTexture"
#define ReflectionName "ReflectionTexture"
#define AlbedoName "AlbedoTexture"
#define MetallicName "MetallicTexture"
#define AmbientOcclusionName "AmbientOcclusionTexture"
#define RougnessName "RougnessTexture"

// Camera
#define cameraPosition "CamPos"

// Lighting
#define lightColor "LightColor"
#define lightPosition "LightPos"

// Other
#define objectColor "ObjectColor"

// #TODO How to handle transfer variables
/* Transfers */
