#version 450

//in vec4 v2fcolor ;
in vec4 inout_color;

out vec4 myfragcolor ;

void main ()
{
        myfragcolor = inout_color ;
}
