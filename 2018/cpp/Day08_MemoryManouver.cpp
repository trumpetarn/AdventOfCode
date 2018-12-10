#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unistd.h>

using namespace std;

struct node_t
{
	int num_child;
	int num_meta_entries;
	vector<node_t> childs;
	vector<int> meta;
	int size;
};

ostream& operator << (std::ostream& o, const node_t& a)
{
  o << "[" << a.num_child << "][" << a.num_meta_entries << "]";
  return o;
}	

vector<string> read_input()
{
	vector<string> in;
	string line;
	//ifstream infile ("../inputs/day08.txt");
	ifstream infile ("../inputs/day08_example.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

vector<int> input_to_int(string str)
{
	vector<int> data;
	stringstream ss;
	ss << str;
	int temp;
	while (!ss.eof())
	{
		ss >> temp;
		data.push_back(temp);
	}
	return data;
}

node_t create_node(vector<int> data, int pos)
{
	node_t node, child;
	int start = pos;
	node.num_child = data[pos];
	node.num_meta_entries = data[++pos];
	pos++;
	for (int i=0; i<node.num_child; i++)
	{
		child = create_node(data, pos);
		node.childs.push_back(child);
		pos += child.size;
		//cout << '[' << pos << ']' << endl;
	}
	//cout << node.num_child << ':' << node.num_meta_entries << '(';
	for (int i=0;i<node.num_meta_entries; i++)
	{
		node.meta.push_back(data[pos]);
		//cout << data[pos] << ',';
		pos++;
	}
	//cout << ") " << endl;
	node.size = pos - start;
	return node;
}

int calculate_meta_sum(node_t tree)
{
	int sum = 0;
	for (auto it = tree.meta.begin(); it != tree.meta.end(); ++it)
	{
		sum += *it;
	}
	for (auto it = tree.childs.begin(); it != tree.childs.end(); ++it)
	{
		sum += calculate_meta_sum(*it);
	}
	return sum;
}

int compute_value(node_t tree)
{
	int value=0;
	for (int i=0; i < tree.num_meta_entries; i++)
	{
		int val = tree.meta[i];
		if (tree.num_child > 0)
		{
			cout << tree.childs[val] << ',';
			compute_value(tree.childs[val]);
		} else {
			value += val;
		}
	}
	return value;
}

int main(int, char**)
{
	vector<string> in = read_input();
	vector<int> data = input_to_int(in[0]);
	node_t tree = create_node(data, 0);
	cout << "Task 1: " << calculate_meta_sum(tree) << endl;
	cout << "Task 2: " << compute_value(tree) << endl;
	return 0;
}