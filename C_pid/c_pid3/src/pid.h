#ifndef _PID_H_ 
#define _PID_H_

#define DERROR_ON

typedef struct
{
	float setpoint;
	float target;

	float kp;
	float ki;
	float kd;

	float currTime;
	float lastTime;

	float lastValue;
	float lastError;

	float dt;

	float Pout;
	float Iout;
	float Dout;

}PID, * pPID;

void InitPid(pPID ppid, float setpoint, float target, float kp, float ki, float kd);
float CalcPid(pPID ppid, float curr);
float Noise();

#endif 
