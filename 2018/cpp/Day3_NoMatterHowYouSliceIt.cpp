#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

#define N 1000

using namespace std;

struct claim_t
{
	int id;
	int left;
	int top;
	int width;
	int height;
	bool overlap;
};

vector<claim_t> read_input()
{
	vector<claim_t> in;
	string line;
	string delim1="@";
	string delim2=",";
	string delim3=":";
	string delim4="x";
	int temp_id,temp_l,temp_t,temp_w,temp_h;
	int pos1, pos2, pos3, pos4;
	ifstream infile ("../inputs/day03.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			pos1=line.find(delim1);
			pos2=line.find(delim2);
			pos3=line.find(delim3);
			pos4=line.find(delim4);
			temp_id=stoi(line.substr(1,pos1-1));
			temp_l=stoi(line.substr(pos1+1,pos2-1));
			temp_t=stoi(line.substr(pos2+1,pos3-1));
			temp_w=stoi(line.substr(pos3+1,pos4-1));
			temp_h=stoi(line.substr(pos4+1,line.length()));
			in.push_back({temp_id,temp_l,temp_t,temp_w,temp_h,false});
		}
	}
	return in;
}



void part_one_and_two(vector<claim_t> in)
{
	int fabric[N][N],i,j;
	int overlap=0;
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			fabric[i][j]=0;
		}
	}
	for (auto it=in.begin(); it != in.end(); ++it)
	{
		for (i=it->left; i<it->left+it->width; i++)
		{
			for (j=it->top; j<it->top+it->height; j++)
			{
				fabric[i][j]++;
			}
		}
	}
	for (auto it=in.begin(); it != in.end(); ++it)
	{
		for (i=it->left; i<it->left+it->width; i++)
		{
			for (j=it->top; j<it->top+it->height; j++)
			{
				if (fabric[i][j]>1)
				{
					overlap++;
					it->overlap=true;
				}
			}
		}
	}
	cout << "Part 1: " << overlap << " sq.inches overlap" << endl;
	for (auto it=in.begin(); it != in.end(); ++it)
	{
		if (!it->overlap)
			cout << "Part 1: " << it->id << endl;
	}
	return;
}

int main(int, char**)
{
	vector<claim_t> in = read_input();
	part_one_and_two(in);
	return 0;
}