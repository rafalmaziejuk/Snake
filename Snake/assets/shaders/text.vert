#version 330 core

layout (location = 0) in vec4 vertexData;

out vec2 texCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertexData.xy, 0.0, 1.0);
    texCoords = vertexData.zw;
}  