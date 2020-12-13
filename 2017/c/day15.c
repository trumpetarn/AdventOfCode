#include<stdio.h>
#include<stdbool.h>

#define DIVISOR 2147483647

bool compare_last_bits(unsigned long m, unsigned long n) {
	int mbit = 0;
	int nbit = 0;
  for (int i=0; i<16; i++)
  {
  	mbit = m % 2;
  	nbit = n % 2;
  	if (mbit != nbit)
		{
  		return false;
		}
  	m = m / 2;
  	n = n / 2;
  }
  return true;
}

unsigned long next_value(unsigned long prev, unsigned long factor, long div)
{
	unsigned long ret = (prev * factor) % DIVISOR;
	while (!(ret%div==0))
	{
		ret = (ret * factor) % DIVISOR;
	}
	return ret;
}

int main(void)
{
	// Defined Data
	unsigned long genA = 16807;
	unsigned long genB = 48271;
	/* Input Data
	Generator A starts with 512
	Generator B starts with 191

	Generator A starts with 699
	Generator B starts with 124

	*/
	unsigned long prevGenA = 699;
	unsigned long prevGenB = 124;
	int matches = 0;
	for (int i=0;i<40000000;i++)
	{
		prevGenA = next_value(prevGenA, genA, 1);
		prevGenB = next_value(prevGenB, genB, 1);
		if (compare_last_bits(prevGenA, prevGenB))
		{
			matches++;
		}
	}
	printf("Task 1: %d\n", matches);

	matches = 0;
	prevGenA = 699;
	prevGenB = 124;
	for (int i=0;i<5000000;i++)
	{
		prevGenA = next_value(prevGenA, genA, 4);
		prevGenB = next_value(prevGenB, genB, 8);
		if (compare_last_bits(prevGenA, prevGenB))
		{
			matches++;
		}
	}
	printf("Task 2: %d\n", matches);
	return 0;
}