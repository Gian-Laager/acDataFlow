#vertex shader
#version 410

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;

out vec4 pixColor;

void main() {
    gl_Position = pos;
}

#fragment shader
#version 410

out vec4 colorOut;
in vec4 pixColor;

void main() {
    colorOut = pixColor;
}