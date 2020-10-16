#include <stdio.h>
#include "pid.h"


int readData();//传感器读数据
int	Init_All();//初始化	

// Out=(Kp*Ek)*(Kp*(T/Ti)*sum(Ek))+(Kp*(TD/T)(Ek-Ek-1))+out0

int main()
{
	printf("位置式PID");
	PID_Init();
	Init_All();	

	while(1)
	{
		pid.Pv=readData();//读取当前温度
		PID_Calc();//计算pid
		PID_out();
	}	
		
	return 0;
}
