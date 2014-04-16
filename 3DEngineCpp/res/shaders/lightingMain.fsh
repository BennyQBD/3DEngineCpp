void main()
{
	vec3 normal = normalize(tbnMatrix * (255.0/128.0 * texture2D(normalMap, texCoord0.xy).xyz - 1));
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * 
    	CalcLightingEffect(normal, worldPos0);
}
