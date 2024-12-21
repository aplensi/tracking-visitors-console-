#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

struct visitors
{
	string startTime;
	string name;
	int status;
	int idComputer;
};

struct tables
{
	int workTime = 0;
	int earned = 0;
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
	void kickEveryoneOut();
	void revenue();
	string minutesToHours(int);
	int price;
	vector<visitors> vecVisitors;
	string openTime, closeTime;
private:
	string isTime(int startOfTime, string);
	bool isNumber(const std::string&);
	int countWords(string);
	int countOfPlaces;
	vector<tables> vecTables;
};