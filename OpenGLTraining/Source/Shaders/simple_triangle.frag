#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 menuColor;     // color selected by the user

uniform sampler2D TexImage;

void main()
{
    //FragColor = menuColor;
    FragColor = texture(TexImage, TexCoord);
}