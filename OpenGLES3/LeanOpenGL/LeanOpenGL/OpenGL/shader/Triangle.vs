#version 300 es
layout(location = 0) in vec3 aPos;
out vec4 glPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    glPos = gl_Position;
}
