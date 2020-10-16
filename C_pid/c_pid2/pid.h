#ifndef PID_H
#define PID_H

typedef struct
{
	float set;			//设定值
	float curr;			//当前值
	
	float Kp;
	float Ti;
	float Td;

	float En;			//本次偏差
	float En_1;			//上次偏差
	float En_2;			//上次偏差
	
	float currpwm;		//当前pwm值
	
	//ms	
	float Tsam;			//采样周期
	float calc_cycle;	//计算周期
	
	float pwm_cycle;	//pwm周期
	
	float Dout;			//PID增量
	
}PID;

extern	PID  pid;
extern	int pidcalcms;	//pid 运算周期 ms

void PID_Init();
void PID_Calc();
#endif
