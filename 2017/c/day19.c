#include <stdio.h>
#include <stdbool.h>
#define SIZE 256

typedef struct Coords {
	int x;
	int y;
} coords;

typedef enum {UP, DOWN, LEFT, RIGHT, NONE} direction;

coords generate_map(char map[SIZE][SIZE])
{
	char c;
	coords start= {0,0};
	int i=0;
	int j=0;
	FILE *fp = fopen("/repo/AdventOfCode/2017/new_inputs/input_day19.txt", "r");
	while ((c = getc(fp)) != EOF)
	{
		if (i==0 && c=='|')
			start.x = j;
		if (c != '\n')
		{
			map[i][j] = c;
			j++;
		}else{
			while (j<SIZE)
			{
				map[i][j]=' ';
				j++;
			}
			j=0;
			i++;
		}
	}
	return start;
}

coords next(coords current, direction dir)
{
	coords ret = current;
	switch (dir)
	{
		case UP:
			ret.y--;
			break;
		case DOWN:
			ret.y++;
			break;
		case LEFT:
			ret.x--;
			break;
		case RIGHT:
			ret.x++;
			break;
	}
	if (ret.x >= SIZE || ret.x < 0)
		ret.x = current.x;
	if (ret.y >= SIZE || ret.y < 0)
		ret.y = current.y;
	return ret;
}

direction turn(coords current, direction dir, char map[SIZE][SIZE])
{
	char dirs[] = {'|','|','-','-'};
	direction dir1, dir2;
	if (dir == UP || dir == DOWN)
	{// Go left or right
		dir1 = LEFT;
		dir2 = RIGHT;
	}else{ // Go up or down
		dir1 = UP;
		dir2 = DOWN;
	}
	coords next1 = next(current, dir1);
	coords next2 = next(current, dir2);

	if (map[next1.y][next1.x] == dirs[dir1]){
		return dir1;
	} else if (map[next2.y][next2.x] == dirs[dir2]){
		return dir2;
	} else if (map[next1.y][next1.x] == '+'){
		return dir1;
	} else if (map[next2.y][next2.x] == '+'){
		return dir2;
	} 
	return NONE;
}

int main(void)
{
	char map[SIZE][SIZE], c;
	char letters[SIZE/4];
	int i = 0;
	coords current = generate_map(map);
	direction dir = DOWN;
	bool foundEnd = false;
	int steps = 0;
	while (!foundEnd)
	{
		steps++;
		current = next(current, dir);
		c = map[current.y][current.x];
		switch (c)
		{
			case '|':
			case '-':
				// Keep current direction
				break;
			case '+':
				dir = turn(current, dir, map);
				break;
			case ' ':
				foundEnd = true;
				break;
			default: //Only other char is letters to save
				letters[i] = c;
				i++;
				if (i >= SIZE/4)
				{
					printf("Too many letters (>%d)\n", SIZE/4);
					foundEnd = true;
				}
				printf("%c", c);
				break;
		}
		if (dir == NONE)
			foundEnd = true;
	}
	printf("\nNumber of steps: %d\n", steps);
	return 0;
}