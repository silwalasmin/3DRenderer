#shader vertex
#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_TexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(v_pos, 1.0);
    TexCoord = v_TexCoord;
}

#shader fragment
#version 330 core

out vec4 v_color;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    v_color = texture(texture1, TexCoord);
}