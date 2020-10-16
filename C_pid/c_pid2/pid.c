#include "pid.h"
	
PID pid;	
// Out=(Kp*Ek-Ek-1)*(Kp*(T/Ti)*Ek)+(Kp*(TD/T)(Ek-2Ek-1+Ek-2)

void PID_Init()
{
	pid.set=100;		//用户设定温度
	pid.currpwm=0;		//当前pwm值	
	
	//ms	
	pid.pwm_cycle=100;	//pwmh周期	
	pid.calc_cycle=100;	//计算周期	
	pid.Tsam=1000;		//采样周期
	
	//ms
	pid.Ti=4000;		//积分时间
	pid.Td=2000;		//微分时间
	pid.Kp=5;
	
}

void PID_Calc()
{
	float dk1;
	float dk2;
	float t1,t2,t3;
	
	//判断运算周期是否到采样周期
	if(pidcalcms<pid.Tsam)	
		return;
	
	pid.En=pid.set-pid.curr;			//当前偏差
	
	dk1=pid.En-pid.En_1;				//Ek-Ek-1 上一次偏差
	t1=pid.Kp*dk1;						//Kp*Ek-Ek-1

	t2=pid.Kp*(pid.Tsam/pid.Ti)*pid.En;	//Kp*(T/Ti)*Ek

	dk2=pid.En-2*pid.En_1+pid.En_2;		//Ek-2Ek-1+Ek-2
	t3=pid.Kp*(pid.Td/pid.Tsam)*dk2;	//Kp*(TD/T)(Ek-2Ek-1+Ek-2)

	pid.Dout=t1+t2+t3;					//PID增量
	pid.currpwm+=pid.Dout;				//输出值
	
	//边界值判断	
	if(pid.currpwm>pid.pwm_cycle)
		pid.currpwm=pid.pwm_cycle;
	
	if(pid.currpwm<0)
		pid.currpwm=0;

	//更新误差	
	pid.En_2=pid.En_1;
	pid.En_1=pid.En;
	
	pidcalcms=0;
}
