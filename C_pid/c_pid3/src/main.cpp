#include <iostream>
#include "pid.h" 
#include <time.h>
#include <windows.h>


int main()
{
	printf("pid teest\n");

	//pPID ppid = (pPID)malloc(sizeof(float) * 13);
	pPID ppid=ppid= (pPID)malloc(sizeof(pPID));

	if (ppid != NULL)
		printf("malloc success\n");

	InitPid(ppid,10,100,0.3,0,0);

	//printf("init success\n");
	float curr = 10;


	for (int i = 0; i < 44; i++)
	{
		curr += CalcPid(ppid, curr) + Noise();
		printf("now curr:\t%f\n", curr);
		Sleep(100);
	}
	return 0;
}
