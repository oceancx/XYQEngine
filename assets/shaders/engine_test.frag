#version 330 core
in vec2 textureCoordinate;
in vec4 color;
uniform sampler2D textureSampler;

void main()
{
	vec4 sampledColor = texture2D(textureSampler, vec2(textureCoordinate.x,1-textureCoordinate.y));
	gl_FragColor = sampledColor * color;
	//gl_FragColor = texture2D(textureSampler, vec2(textureCoordinate.x,1-textureCoordinate.y));

}
