#shader vertex
#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex;

out vec2 u_tex;

void main()
{
    gl_Position = vec4(v_pos, 1.0);
    u_tex = v_tex;
}

#shader fragment
#version 330 core

in vec2 u_tex;

out vec4 v_color;

uniform sampler2D splashtexture;

void main()
{
    v_color = texture(splashtexture, u_tex);
}