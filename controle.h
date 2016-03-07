#include "pose.h"
#include "util.h"
#ifndef CONTROLE_H
#define CONTROLE_H
#define P_ANGULO -0.96
#define P_LINEAR 3.9
#define I_LINEAR 0.75
#define I_ANG -0.105

struct Acionamento{
    int vel;
    int per_giro;
};

//float cos(float ang){ return (Cos(ang)/100.0);}
//float sin(float ang){ return (Sin(ang)/100.0);}

float controle_som_erro_theta = 0;
float controle_som_err_linear = 0;
float controle_som_err_angular = 0;

float controle_linear(Pose refer, Pose atual, Acionamento &a){

    float x = atual.x;
    float y = atual.y;
    float theta = atual.theta;

    float x_referencia = refer.x; //cm
    float y_referencia = refer.y;
    float theta_referencia = refer.theta;


    float erro_theta = 0;

    int percent_giro = 0;
    float P = -0.1;
    float I = -0.0000000075;


    float erro_x = 0;
    float erro_y = 0;

    float erro_linear = 0;
    int velocidade_linear = 0;

    erro_theta = atan2(theta_referencia - theta);
    controle_som_erro_theta = atan2(controle_som_erro_theta + erro_theta);
     //   erro_angular = erro_theta;

    percent_giro = P * erro_theta;
    percent_giro = percent_giro + (I * controle_som_erro_theta);

    if(percent_giro > 60)
        percent_giro = 60;
    if(percent_giro  < -60)
        percent_giro = -60;

    erro_x = x_referencia - x;
    erro_y = y_referencia - y;
    erro_linear = erro_x * cos(theta) + erro_y * sin(theta);

    controle_som_err_linear += erro_linear;

    velocidade_linear = P_LINEAR * erro_linear + I_LINEAR * erro_linear;

    if(velocidade_linear > 35){
        velocidade_linear = 35;
    }
    if(velocidade_linear < -35){
        velocidade_linear = -35;
    }

    a.vel = velocidade_linear;
    a.per_giro = percent_giro;

    return erro_linear;
}

float controle_angular(Pose refer, Pose atual, Acionamento &a){
    float erro_theta=0;
    float velocidade_angular=0;
    int sinal=1;

    erro_theta = atan2(refer.theta - atual.theta);    
	controle_som_err_angular = atan2(erro_theta + controle_som_err_angular);
	
	velocidade_angular = (P_ANGULO * erro_theta) + (I_ANG * controle_som_err_angular);
    sinal = velocidade_angular/abs(velocidade_angular);
	
	if(velocidade_angular > 35){
		velocidade_angular = 35;
	}

    a.per_giro = sinal*100;
    a.vel = velocidade_angular;
	
    return erro_theta;
}

#endif
