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
	day.day++;
	if (day.day>length)
	{
		day.day = 1;
		day.month++;
		if (day.month>12)
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
	map<int, entry_t> guard_info2;
	map<int, int> sleep_time;
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
		}
		else if ((*it).compare(19,5,"falls")==0)
		{
			entry.asleep.push_back(temp);
		}
		else if ((*it).compare(19,5,"wakes")==0)
		{
			entry.awake.push_back(temp);
		}
		else
		{
			cout << "WTF!" << endl;
		}
		guard_info[temp_date] = entry;
		//cout << guard_info[temp_date].asleep.size() << ',';
	}

	for (auto iter = guard_info.begin(); iter!=guard_info.end(); iter++)
	{
		if (iter->second.id != 0)
		{
			sort(iter->second.awake.begin(),iter->second.awake.end());
			sort(iter->second.asleep.begin(),iter->second.asleep.end());
			for (int j=0; j< (int)iter->second.asleep.size(); j++)
			{
				if (sleep_time.find(iter->second.id) == sleep_time.end())
				{
					sleep_time[iter->second.id] = 0;	
				}
				sleep_time[iter->second.id] += minutes_asleep(iter->second.asleep[j], iter->second.awake[j]);
				guard_info2[iter->second.id].asleep.push_back(iter->second.asleep[j]);
				guard_info2[iter->second.id].awake.push_back(iter->second.awake[j]);
			}
		} else {
			cout << "x\n";
		}
	}
	int max_time = 0;
	int max_id = 0;
	for (auto it2 = sleep_time.begin(); it2 != sleep_time.end(); it2++)
	{
		if (it2->second > max_time)
		{
			max_time = it2->second;
			max_id = it2->first;
		}
	}
	cout << max_id << ':' << guard_info2[max_id].asleep.size() << endl;
}

int main (int, char**)
{
	vector<string> in = read_input();
	part_one(in);
	return 0;
}