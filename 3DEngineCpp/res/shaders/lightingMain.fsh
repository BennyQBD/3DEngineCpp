void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0.xy) * 
    	CalcLightingEffect(normalize(normal0), worldPos0);
}
