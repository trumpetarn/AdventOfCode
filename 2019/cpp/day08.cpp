#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <unistd.h>
#include <iterator>
#include <list>
#include <math.h>

using namespace std;
namespace day08{
vector<string> read_input(string loc)
{
	vector<string> in;
	string line;
	ifstream infile (loc);
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

struct Image{
	int width;
	int height;
	vector<vector<int>> pixels;
};

Image get_image(vector<string> in, int width, int height){
	int size = width*height;
	int i = 0;
	Image image;
	image.width = width;
	image.height = height;
	vector<int> temp;
	for (char& c : in[0]){
		temp.push_back(c-'0');
		if (++i>= size){
			i=0;
			image.pixels.push_back(temp);
			temp.clear();
		}
	}
	return image;
}

void task1(Image image){
	int min = image.width*image.height;
	int n,res =-1;
	int i = 0;
	for (auto v : image.pixels){
		n = count(v.begin(),v.end(),0);
		if (n<min){
			min = n;
			res = count(v.begin(),v.end(),1)*count(v.begin(),v.end(),2);
		}
		i++;
	}
	cout << "Star 1: " << res << endl;
	return; 
}

/* 0 = black, 1 = white, 2 = transparent;
*/
void print_image(Image i){
	int j=0;
	for (int h=0; h < i.height; h++){
		for (int w=0; w < i.width; w++){
			switch (i.pixels[0][j]){
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "\u2589";
					break;
				default:
					break;
			}
			j++;
		}
		cout << endl;
	}
}

void task2(Image image){
	Image flat;
	flat.width = image.width;
	flat.height = image.height;
	flat.pixels.push_back(image.pixels[0]);
	for (auto v : image.pixels){
		for (int i=0; i<image.width*image.height; i++){
			if (flat.pixels[0][i]==2){
				flat.pixels[0][i] = v[i];
			}
		}
	}
	cout << "Star 2:" << endl;
	print_image(flat);
}

int main()
{
	string path = "../inputs/day08.txt";
	vector<string> input = read_input(path);
	Image i = get_image(input, 25, 6);
	task1(i);
	task2(i);
	return 0;
}
}//namespace day08