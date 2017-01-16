#version 330 core
layout (location = 0) in vec2 position;
uniform mat4 MVP;
void main()
{
	vec4 NewPosition = vec4(position, 0.0, 1.0);
	NewPosition = MVP * NewPosition;
	gl_Position = NewPosition;
}