#ifndef PID_H
#define PID_H

typedef struct
{
	float Sv;
	float Pv;

	float Kp;
	float T;	//PID(计算)采样周期
	float Ti;
	float Td;

	float Ek;	//本次偏差
	float Ek_1;	//上次偏差
	float SEK;	//偏差之和

	float OUT0;
	float OUT;

	int C10ms;//
	int pwmcycle;//pwm周期
}PID;

extern	PID  pid;
void PID_Init();
void PID_Calc();
void PID_out();
#endif
