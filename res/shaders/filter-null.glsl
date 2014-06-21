#include "common.glh"

varying vec2 texCoord0;

#if defined(VS_BUILD)
attribute vec3 position;
attribute vec2 texCoord;

uniform mat4 T_MVP;

void main()
{
    gl_Position = T_MVP * vec4(position, 1.0);
    texCoord0 = texCoord; 
}
#elif defined(FS_BUILD)
uniform sampler2D R_filterTexture;

DeclareFragOutput(0, vec4);
void main()
{
	SetFragOutput(0, texture2D(R_filterTexture, texCoord0));
}
#endif
