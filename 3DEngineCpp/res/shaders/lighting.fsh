varying vec2 texCoord0;
varying vec3 worldPos0;
varying vec4 shadowMapCoords0;
varying mat3 tbnMatrix;

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;

uniform sampler2D R_shadowMap;
uniform float R_shadowBias;
uniform vec3 R_shadowTexelSize;

#include "lighting.glh"
