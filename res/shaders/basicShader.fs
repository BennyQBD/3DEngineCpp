#version 120

varying vec2 texCoord0;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoords);
}
