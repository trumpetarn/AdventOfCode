#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#define NUM_OF_INSTRUCTIONS 10300
#define DATA_LEN 16

typedef enum {SPIN, EXCHANGE, PARTNER} dance_move;

typedef struct instruction {
	dance_move type;
	int A;
	int B;
	char a;
	char b;
}instruction;

instruction instructions[NUM_OF_INSTRUCTIONS];

void print_data(char* data)
{
	for (int i=0; i<DATA_LEN; i++)
	{
		printf("%c", data[i]);
	}
	printf("\n");
}

int return_number(char a, char b)
{
	if (isdigit(b))
	{
		return 10+(b-'0');
	}
	return a-'0';
}

int read_instructions()
{
	FILE *fp = fopen("/repo/AdventOfCode/2017/inputs/input_day16.txt", "r");
	char c,d,e;
	int a,b;
	int i = 0;
	while ((c = getc(fp)) != EOF)
	{
		switch (c) {
			case 's':
				d = getc(fp);
				e = getc(fp);
				a = return_number(d,e);
				instructions[i].type = SPIN;
				instructions[i].A = a;
				instructions[i].B = -1;
				instructions[i].a = '-';
				instructions[i].b = '-';
				i++;
				break;
			case 'x':
				d = getc(fp);
				e = getc(fp);
				a = return_number(d,e);
				if (e!='/')
					getc(fp);
				d = getc(fp);
				e = getc(fp);
				b = return_number(d,e);
				instructions[i].type = EXCHANGE;
				instructions[i].A = a;
				instructions[i].B = b;
				instructions[i].a = '-';
				instructions[i].b = '-';
				i++;
				break;
			case 'p':
				d = getc(fp);
				getc(fp);
				e = getc(fp);
				instructions[i].type = PARTNER;
				instructions[i].A = -1;
				instructions[i].B = -1;
				instructions[i].a = d;
				instructions[i].b = e;
				i++;
				break;
			default:
				break;
		}
	}
	fclose(fp);
	return i;
}

void spin(int x, char *data)
{
	int tmp[DATA_LEN];
	x = DATA_LEN-x;
	for (int i=0;i<DATA_LEN;i++)
	{
		tmp[i] = data[i];
		if (x<DATA_LEN)
			data[i] = data[x];
		else
			data[i] = tmp[x%DATA_LEN];
		x++;
	}
	data[0];
}

void exchange(int a, int b, char *data)
{
	char tmp = data[a];
	data[a] = data[b];
	data[b] = tmp;
}

void partner(char a, char b, char *data)
{
	int ai = 0;
	int bi = 0;
	for (int i=0;i<DATA_LEN;i++)
	{
		if (data[i] == a)
		{
			ai = i;
		}
		if (data[i] == b)
		{
			bi = i;
		}
	}
	exchange(ai,bi,data);
}

void follow_instructions(int len, char *data)
{
	for (int i=0; i<len; i++)
	{
		switch (instructions[i].type)
		{
			case SPIN:
				spin(instructions[i].A,data);
				break;
			case EXCHANGE:
				exchange(instructions[i].A,instructions[i].B,data);
				break;
			case PARTNER:
				partner(instructions[i].a,instructions[i].b,data);
				break;
		}
	}
}

bool found_cycle(char*data)
{
	char start[DATA_LEN] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};	
	for (int i=0;i<DATA_LEN;i++)
	{
		if (start[i] != data[i])
		{
			return false;
		}
	}
	return true;
}

int main(void)
{
	char data[DATA_LEN] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
	int len = read_instructions();
	follow_instructions(len, data);
	printf("Task 1:\t");
	print_data(data);
	int cycle = 0;
	for (int i=1;i<1000000000;i++)
	{
		follow_instructions(len, data);
		if (found_cycle(data))
		{
			cycle = i+1; //Remeber index 0
			printf("Cycle: %d\n", cycle);
			break;
		}
	}
	for (int j=0;j<cycle+1000000000%cycle; j++)
	{
		follow_instructions(len, data);
	}
	printf("Task 2 (%d):\t", 1000000000%cycle);
	print_data(data);
	return 0;
}