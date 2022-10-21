#version 300 es
precision mediump float;
uniform vec3 ourColor;
in vec4 glPos;
out vec4 fragColor;
void main()
{
//    fragColor = vec4(ourColor, 1.0);
    fragColor = glPos;
}
