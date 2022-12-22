#version 300 es

precision mediump float;

in vec2 TexCoords;
out vec4 fColor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    vec4 color = texture(image, TexCoords);
//    if (color.a == 0.0) {
//        fColor = vec4(0.0, 0.0, 0.0, 1.0);
//    } else {
        fColor = vec4(spriteColor, 1.0) * color;
//    }
}
