#include <stdio.h>
#include "pid.h" 
#include <time.h>
#include <windows.h>

//函数入口 pid结构体 初始值 目标值 pid参数
void InitPid(pPID ppid, float setpoint, float target, float kp, float ki, float kd)
{
	ppid->setpoint = setpoint;
	ppid->target = target;
	ppid->kp = kp;
	ppid->ki = ki;
	ppid->kd = kd;
	ppid->currTime = 0;
	ppid->lastTime = 0;
	ppid->lastValue = 0;
	ppid->lastError = 0;
	ppid->dt = 0.1;
	ppid->Pout = 0;
	ppid->Iout = 0;
	ppid->Dout = 0;
	printf("init success\n");
	printf("setpoint:%f \n", ppid->setpoint);
	printf("target:%f \n", ppid->target);
}

//函数入口 pid结构体 当前值
float CalcPid(pPID ppid, float curr)
{
	printf("=====calc=====\n");
	printf("curr:\t%f\n", curr);
	printf("last value:\t%f\n",ppid->lastValue);
	
	float error = ppid->target - curr;			//目标值和当前值之间的误差

	ppid->Pout = ppid->kp * error;

	ppid->Iout += ppid->ki * error * ppid->dt;
	
#ifdef DERROR_ON
	ppid->Dout = (ppid->kd * (error-ppid->lastError)) / ppid->dt;//这次和前一次误差的斜率
#else
	ppid->Dout = (ppid->kd * (curr-ppid->lastValue)) / ppid->dt;//这次和前一次误差的斜率
#endif 

	float Out = ppid->Pout + ppid->Iout + ppid->Dout;

	ppid->lastValue = Out;
	ppid->lastError = error;
	
	printf("error:\t%f\n", error);

	printf("pout:\t%f\n", ppid->Pout);
	printf("Iout:\t%f\n", ppid->Iout);
	printf("Dout:\t%f\n", ppid->Dout);

	printf("OUT:\t%f\n",Out);

	printf("=====calc=====\n");

	return Out;
}

//随机噪声
float Noise()
{
	srand(NULL);
	printf("noise:\t%f\n", (rand() % 11)*0.1);
	return (rand() % 11)*0.1;
}

