#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

struct visitors
{
	string timeOfEntry;
	string exitTime;
	string startTime;
	string name;
	int timeUsed, status;
};

struct tables
{
	int workTime = 0;
	bool status;
};

class actionsWithVisitors
{
public:
	void event(string);
	bool isPlace(string);
	bool isOpenTime(string);
	int hoursToMinuts(string);
	void setPlaces(int);
	string minutesToHours(int);
	int price;
	vector<visitors> vecVisitors;
private:
	string openTime, closeTime;
	string isTime(int startOfTime, string);
	bool isNumber(const std::string&);
	int countWords(string);
	int countOfPlaces;
	vector<tables> vecTables;
};