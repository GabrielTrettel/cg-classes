#version 450
layout ( location = 0) in vec4 vPosition ;

out vec4 v2fcolor ;

void main ()
{
    // Ajusta a luminosidade do modelo de acordo com a sua coordenada
    // no plano. X e Y estão no plano da tela e Z apontado pra fora
     float gray = (vPosition.z + 1) * 0.5;
//    float gray = (vPosition.z + 1);

//    if (gray <= 1)
//        gray *= 0.6;
//    else if (gray <= 1.2)
//        gray *= 0.7;
//    else
//        gray *= 0.75;


    v2fcolor = vec4( gray , gray , gray , 1) ;
    gl_Position = vec4(vPosition.x, vPosition.y , -vPosition.z, vPosition.w);
}
