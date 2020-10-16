#include <stdio.h>
#include "pid.h"


int readData();//传感器读数据
int	Init_All();//初始化	

// Out=(Kp*Ek-Ek-1)*(Kp*(T/Ti)*Ek)+(Kp*(TD/T)(Ek-2Ek-1+Ek-2)

int main()
{
	printf("增量式PID");
	PID_Init();
	Init_All();	

	while(1)
	{
		pid.curr=readData();//读取当前温度
		PID_Calc();//计算pid
	}	
		
	return 0;
}
