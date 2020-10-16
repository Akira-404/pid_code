#include "pid.h"
	
PID pid;	
// Out=(Kp*Ek)*(Kp*(T/Ti)*Sum(Ek))+(Kp*(TD/T)(Ek-Ek-1))+out0

void PID_Init()
{
	pid.Sv=100;//用户设定温度
	
	//可调
	pid.Kp=20;
	
	//ms
	pid.Ti=5000;//积分时间
	pid.Td=1200;//微分时间
	pid.T=1000;//采样周期 1000ms做一次计算
	pid.pwmcycle=1000;//pwm时间;一个周期
	
	pid.OUT0=1;
}

void PID_Calc()
{
	float DelEk;//Ek-Ek-1
	
	float ti;//T/Ti
	float ki;//Kp*(T/Ti)
	
	float td;//TD/T
	float kd;//Kp*(TD/T)

	//PID Out
	float Pout;
	float Iout;
	float Dout;
	
	float out;
	//PID_Calc每1000ms算一次，但是要保证每次必须先执行完毕结果才能计算
	//C10ms在定时器中断里面，每10ms中断一次,C10ms++

	if(pid.C10ms<(pid.T)/10)
		return ;	

	//Pout 比例输出 
	//Kp*Ek	
	pid.Ek=pid.Sv-pid.Pv;	//当前偏差 Ek
	Pout=pid.Kp*pid.Ek;		//Kp*Ek

	//Iout 积分输出 
	//Kp*(T/Ti)*Sum(Ek)
	pid.SEK+=pid.Ek;		//Sum(Ek) 历史偏差总和
	ti=pid.T/pid.Ti;		//T/Ti
	ki=pid.Kp*ti;			//Kp*(T/Ti)
	Iout=ki*pid.SEK;		//Kp*(T/Ti)*Sum(Ek)

	//Dout 微分输出	
	//Kp*(TD/T)(Ek-Ek-1)
	td=pid.Td/pid.T;		//TD/T
	kd=pid.Kp*td;			//Kp*(TD/T)
	DelEk=pid.Ek-pid.Ek_1;	//Ek-Ek-1 最近两次偏差之差
	Dout=kd*DelEk;			//Kp*(TD/T)(Ek-Ek-1)

	out=Pout+Iout+Dout+pid.OUT0;
	
	if(out>pid.pwmcycle)
		pid.OUT=pid.pwmcycle;//最大值
	if(out<0)
		pid.OUT=0;			 //最小值
	
	pid.OUT=out;
	
	pid.Ek_1=pid.Ek;//把本次的偏差变成上一次的偏差
	pid.C10ms=0;
}
//定时器中断函数调用,每一毫秒调用一次
void PID_out()
{
	static int pw;
	pw++;
	if(pw>=pid.pwmcycle)
		pw=0;
	//
	if(pw<pid.OUT)
		;//增加
	else
		;//减少

}
