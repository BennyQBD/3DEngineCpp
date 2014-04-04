#version 120

varying vec2 texCoord0;

uniform vec3 R_ambient;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0.xy) * vec4(R_ambient, 1);
}
