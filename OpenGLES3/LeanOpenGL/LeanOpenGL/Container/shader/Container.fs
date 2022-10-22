#version 300 es
precision mediump float;
in vec3 ourColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//    fragColor = texture(texture1, texCoord) * vec4(ourColor, 1.0);
//    fragColor = texture(texture2, texCoord);
    fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord).bgra, 0.5);
}
