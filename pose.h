#include "util.h"
#ifndef POSE_H
#define POSE_H
#define MOTOR_DIREITO OUT_A
#define MOTOR_ESQUERDO OUT_B
#define RAIO_RODA 1.51  //2.7
#define RAIO_ROBO 7.0  //6.275
#define CONSTANTE_RODAS (PI * RAIO_RODA)/180


struct Pose{
    float x;
    float y;
    float theta;
};

struct Angulo{
    int atual;
    int anterior;
};
float distancia_ant;
float pose_dist = 0;
float alpha_dir = 0; //ÂNGULO DA RODA DIREITA
float alpha_esq = 0; //ÂNGULO DA RODA ESQUERDA
float giro_dir = 0;  //RODA DIREITA
float giro_esq = 0;  //RODA ESQUERDA
float inc_angular;   //INCREMENTO ANGULAR
float s = 0;         //SENO
float c = 0;         //COSSENO
Angulo ang_dir,ang_esq;
Pose dist_perc;

int contador_dir(){
    ang_dir.anterior = ang_dir.atual;
    ang_dir.atual = MotorRotationCount(MOTOR_DIREITO);
    //ResetTachoCount(MOTOR_DIREITO);
    //ResetRotationCount(MOTOR_DIREITO);
    return(ang_dir.atual - ang_dir.anterior);
}

int contador_esq(){
    ang_esq.anterior = ang_esq.atual;
    ang_esq.atual = MotorRotationCount(MOTOR_ESQUERDO);
    return(ang_esq.atual - ang_esq.anterior);
}

void atualiza_pose(float &x, float &y, float &theta ){
    float inc_linear;
    alpha_dir = contador_dir();
    alpha_esq = contador_esq();
    giro_dir = alpha_dir * CONSTANTE_RODAS;
    giro_esq = alpha_esq * CONSTANTE_RODAS;
    inc_linear = (giro_dir + giro_esq)/2;
    inc_angular = (giro_dir - giro_esq)/2;
	pose_dist = inc_linear;	
	
    s = Sin(theta);
    c = Cos(theta);
    y = y + inc_linear *  s / 100.00;
    x = x + inc_linear * c / 100.00;
    theta = atan2(theta + ((inc_angular * 180.0)/(PI*RAIO_ROBO)));
	NumOut(20,LCD_LINE1,theta);
}
void atualiza_pose2(Pose &a){
    atualiza_pose(a.x, a.y, a.theta);
}
float calc_dist(Pose atual,Pose ant){
	float distancia;
	distancia = sqrt(pow(atual.x - ant.x) + pow(atual.y - ant.y));
	return distancia;
}
float robo_ang(float hip,float Co){
	float angulo_rob;
	angulo_rob = Co/hip;
		return Asin(angulo_rob);
}
#endif
