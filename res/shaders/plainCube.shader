#shader vertex
#version 330 core

layout (location = 0) in vec3 v_pos;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(v_pos, 1.0);
}

#shader fragment
#version 330 core

out vec4 v_color;

void main()
{
    v_color = vec4(1.0, 1.0, 1.0, 1.0);
}