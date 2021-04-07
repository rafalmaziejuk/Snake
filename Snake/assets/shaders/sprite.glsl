#type vertex
#version 330 core

layout (location = 0) in vec4 vertexData;

out vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	texCoords = vertexData.zw;
	gl_Position = projection * model * vec4(vertexData.xy, 0.0, 1.0);
}

#type fragment
#version 330 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D sprite;

void main()
{
	color = texture(sprite, texCoords);
}