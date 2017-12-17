#include <stdio.h>
#define INPUT 349

void initBuffer(unsigned long *buffer, unsigned long n)
{
	for (unsigned long i=0; i<n; i++)
	{
		buffer[i] = 0;
	}
}

void printBuffer(unsigned long *buffer, unsigned long n)
{
	printf("[");
	for (unsigned long i=0; i<n; i++)
	{
		printf("%d ", buffer[i]);
	}
	printf("]\n");
}

/* Inster a number at index i, move all other values to the right */
void insertNumber(unsigned long *buffer, unsigned long val, unsigned long pos, unsigned long n)
{
	for (unsigned long j = n-1; j>pos;j--)
	{
		buffer[j] = buffer[j-1];
	}
	buffer[pos] = val;
}

int main (void)
{
	unsigned long buffer[2018];
	initBuffer(buffer, 2018);
	unsigned long position = 0;
	//int current_length = 1;
	for (unsigned long i=1; i<2018; i++)
	{
		position = (position + INPUT) % i;
		//printf("%d, %d\n", i, position);
		insertNumber(buffer, i, ++position, (i+1));
	}
	printf("Task 1: value afer %d, %d\n", buffer[position], buffer[position+1]);
	int myval = 0;
	for (unsigned long i=1; i<50000001; i++)
	{
		position = (position + INPUT) % i;
		if (++position == 1)
		{
			myval = i;
			printf("%d, ", myval);
		}
	}
	printf("Task 2: value afer %d, %d\n", buffer[0], myval);
	return 0;
}