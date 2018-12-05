#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum entry_type {starts, asleep, awake};

struct date_t
{
	int year;
	int month;
	int day;
	bool operator <(const date_t& x) const{
		if (x.year != year)
			return x.year < year;
		if (x.month != month)
			return x.month < month;
    return x.day < day;
	}
	bool operator >(const date_t& x) const{
		if (x.year != year)
			return x.year > year;
		if (x.month != month)
			return x.month > month;
    return x.day > day;
	}
};

struct dt_t
{
	date_t date;
	int hour;
	int min;
	//TODO: Check date
	bool operator <(const dt_t& x) const{
		return  (hour*60 + min) < (x.hour*60+x.min);
	}
	bool operator >(const dt_t& x) const{
		return (hour*60 + min) > (x.hour*60+x.min);
	}
};

struct entry_t
{
	int id;
	vector<dt_t> awake;
	vector<dt_t> asleep;
};

int minutes_asleep(dt_t start, dt_t stop)
{
	return (stop.hour - start.hour)*60 + (stop.min - start.min);
}

//Todo: create Helper to read input (with dynamic file)?
vector<string> read_input()
{
	vector<string> in;
	string line;
	ifstream infile ("../inputs/day04.txt");
	if (infile.is_open())
	{
		while (getline(infile,line))
		{
			in.push_back(line);
		}
	}
	return in;
}

date_t next_day(date_t day)
{
	int length;
	switch (day.month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			length = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			length = 30;
			break;
		case 2:
			// 1518 was not a leap year
			length = 28;
			break;
		default:
			length = 0;
			cout << "WTF!" << endl;
	}
	if (day.day==length)
	{
		day.day = 1;
		day.month++;
		if (day.month==13)
		{
			day.month = 1;
			day.year++;
		}
	}
	return day;
}

void part_one(vector<string> in)
{
	map<date_t, entry_t> guard_info;
	map<int, entry_t> sleep_time;
	for (auto it=in.begin(); it!=in.end(); it++)
	{
		date_t temp_date;
		dt_t temp;
		entry_t entry;
		temp_date.year = stoi((*it).substr(1,4));
		temp_date.month = stoi((*it).substr(6,7));
		temp_date.day = stoi((*it).substr(9,10));

		temp.hour = stoi((*it).substr(12,13));
		temp.min = stoi((*it).substr(15,16));
		// Set date to next day since shift really starts at midnight
		if (temp.hour == 23)
		{
			temp_date = next_day(temp_date);
			temp.hour = 0;
			temp.min = 0;
		}

		temp.date = temp_date;
		if (guard_info.find(temp_date) != guard_info.end())
		{
			entry = guard_info[temp_date];
		} else {
			entry.id = 0;
		}
		if ((*it).compare(19,5,"Guard")==0)
		{
			entry.id = stoi((*it).substr(26,33));
			//entry.awake.push_back(temp);
			guard_info[temp_date] = entry;
		}
		else if ((*it).compare(19,5,"falls")==0)
		{
			entry.asleep.push_back(temp);
			guard_info[temp_date] = entry;
		}
		else if ((*it).compare(19,5,"wakes")==0)
		{
			entry.awake.push_back(temp);
			guard_info[temp_date] = entry;
		}
		else
		{
			cout << "WTF!" << endl;
		}
	}

	for (auto iter = guard_info.begin(); iter!=guard_info.end(); iter++)
	{
		if (iter->second.id != 0)
		{
			sleep_time[iter->second.id] = iter->second;
			//cout << minutes_asleep(iter->second.asleep[0],iter->second.awake[0]);
			sort(iter->second.awake.begin(),iter->second.awake.end());
			sort(iter->second.asleep.begin(),iter->second.asleep.end());
			for (int i=0; i< (int)iter->second.awake.size(); i++)
			{
				cout << iter->second.awake[i].hour << ':' << iter->second.awake[i].min << ',';
			}
			cout << endl;
			for (int j=0; j< (int)iter->second.asleep.size(); j++)
			{
				cout << iter->second.asleep[j].hour << ':' << iter->second.asleep[j].min << ',';
			}
			cout << endl << endl;
		}
	}
}

int main (int, char**)
{
	vector<string> in = read_input();
	part_one(in);
	return 0;
}