attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 tangent;

varying vec2 texCoord0;
varying vec3 worldPos0;
varying mat3 tbnMatrix;

uniform mat4 T_model;
uniform mat4 T_MVP;

void main()
{
    gl_Position = T_MVP * vec4(position, 1.0);
    texCoord0 = texCoord; 
    worldPos0 = (T_model * vec4(position, 1.0)).xyz;
    
    vec3 n = normalize((T_model * vec4(normal, 0.0)).xyz);
    vec3 t = normalize((T_model * vec4(tangent, 0.0)).xyz);
    t = normalize(t - dot(t, n) * n);
    
    vec3 biTangent = cross(t, n);
    tbnMatrix = mat3(t, biTangent, n);
}
