#include<stdio.h>
#include<stdbool.h>

#define SCANNER_LEN 91
#define LINES 43

static int scanner[SCANNER_LEN];

bool is_caught(int step, int depth)
{
	if (depth > 0)
		return ((step % (2*(depth-1))) == 0);
	return false;
}

void init_scanner()
{	
	int a,b,c = 0;
	for (int i=0;i<SCANNER_LEN;i++)
	{
		scanner[i] = 0;
	}

	FILE *fp = fopen("/git/AdventOfCode/2017/inputs/input_day13.txt", "r");
	for (int i=0;i<LINES;i++)
	{
		fscanf(fp, "%d: %d\n", &a,&b);
		scanner[a] = b;
	}
	fclose(fp);
	return;
} 

void task1(void)
{
	init_scanner();
	int severity = 0;
	for (int i=0; i<SCANNER_LEN; i++)
	{
		if (is_caught(i, scanner[i]))
		{
			severity += i * scanner[i];
		}
	}
	printf("Task1, severity: %d\n", severity);
}

void task2(void)
{
	init_scanner();
	int delay = 0;
	bool done = false;
	while (!done)
	{
		done = true;
		for (int i=0; i<SCANNER_LEN; i++)
		{
			done = done && !is_caught(i+delay, scanner[i]);
		}
		delay++;
	}
	printf("Task2, delay: %d\n", delay-1);
}

int main(void)
{
	task1();
	task2();
	return 0;
}