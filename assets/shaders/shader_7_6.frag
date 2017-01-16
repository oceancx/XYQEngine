#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;
uniform sampler2D ourTexture;
//uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

void main()
{	
	color = texture(ourTexture, vec2(TexCoord.x , TexCoord.y));
//	color = vec4(0.0f,1.0f,1.0f,0.0f);
}
