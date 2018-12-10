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
#include <numeric>

using namespace std;

struct node_t
{
	int num_child;
	int num_meta_entries;
	vector<node_t> childs;
	vector<int> meta;
	int size;
	int value;
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
		//cout << pos << ':';
	}
	cout << node.num_child << ':' << node.num_meta_entries << '(';
	for (int i=0;i<node.num_meta_entries; i++)
	{
		int val = data[pos];
		node.meta.push_back(val);
		cout << val << ',';
		pos++;
	}
	node.value = 0;
	if (node.num_child==0)
	{
		node.value += accumulate(node.meta.begin(), node.meta.end(), 0);
	} else {
		for (auto it = node.meta.begin(); it != node.meta.end(); ++it)
		{
			if (*it <= node.num_child)
				node.value += node.childs[(*it)-1].value;
			//cout << '<' << node.value << '>' << endl;
		}
	}
	cout << ") ";
	cout << '[' << node.value << ']' << endl;
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

int main(int, char**)
{
	vector<string> in = read_input();
	vector<int> data = input_to_int(in[0]);
	node_t tree = create_node(data, 0);
	cout << "Task 1: " << calculate_meta_sum(tree) << endl;
	cout << "Task 2: " << tree.value << endl;
	return 0;
}