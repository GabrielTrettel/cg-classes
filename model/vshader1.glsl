#version 450

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 normal;

uniform mat4 model;

//out vec4 v2fcolor;
out vec4 inout_color;

void main () {
    inout_color = vec4(abs(normal), 1);

    gl_Position = model * vPosition;

    //We could infer the depth of the model
    float gray = (gl_Position.z + 1) * 0.5;
//    inout_color = vec4 (gray , gray , gray , 1);
}

