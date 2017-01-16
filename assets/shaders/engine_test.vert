#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 colorMultiplier;
layout (location = 3) in float isHUD;
uniform mat4 scaleMatrix;
uniform mat4 viewInverseMatrix;
uniform mat4 projectionMatrix;
out vec2 textureCoordinate;
out vec4 color;

void main()
{
	
 //   vec4 wPos = position;
//	wPos *= scaleMatrix;
//	wPos *= projectionMatrix;
	if(isHUD < 0.5)
	{
//		wPos *= viewInverseMatrix;
	}
	//gl_Position = wPos;
	gl_Position = projectionMatrix *scaleMatrix* position;
	textureCoordinate = texCoord;
	color = colorMultiplier;
}
