#type vertex
#version 330 core

layout (location = 0) in vec4 vertexData;

out vec2 texCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertexData.xy, 0.0, 1.0);
    texCoords = vertexData.zw;
} 

#type fragment
#version 330 core

in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  