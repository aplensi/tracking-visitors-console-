#include "tracking-visitors.h"

int main()
{
	actionsWithVisitors act;
	ifstream stream("file.txt");
	string str;
	getline(stream, str);
	if (!act.isPlace(str))
	{
		cout << "line of places is skipped";
		return 0;
	}
	act.setPlaces(atoi(str.c_str()));
	getline(stream, str);
	if (!act.isOpenTime(str))
	{
		cout << "line of time is skipped";
		return 0;
	}
	getline(stream, str);
	if (atoi(str.c_str()) < 0)
	{
		cout << "line of price is skipped";
		return 0;
	}
	else
	{
		act.price = atoi(str.c_str());
	}

	while (getline(stream, str))
	{
		//cout << str << endl;
		act.event(str);
	}
	for (const auto& i : act.vecVisitors)
	{
		cout << i.name << endl;
	}

	return 0;
}

void actionsWithVisitors::event(string s)
{
	cout << s << endl;
	stringstream ss(s);
	int time, status, idPlace;
	string name, sTime, sStatus, sIdPlace;
	int countW = countWords(s);
	if (countW == 3)
	{
		ss >> sTime >> sStatus >> name;
	}
	else {
		ss >> sTime >> sStatus >> name >> sIdPlace;
	}
	time = hoursToMinuts(sTime);
	status = atoi(sStatus.c_str());
	idPlace = atoi(sIdPlace.c_str());

	if (time < hoursToMinuts(openTime))
	{
		cout << sTime << " 13 NotOpenYet " << endl;
		return;
	}
	if (status == 1)
	{
		visitors visitor;
		visitor.timeOfEntry = sTime;
		visitor.name = name;
		visitor.status = status;
		vecVisitors.push_back(visitor);
	}
	else if (status == 2)
	{
		if (vecTables[idPlace - 1].status == true)
		{
			cout << sTime << " 13 PlaceIsBusy " << endl;
		}
		else {
			vecTables[idPlace - 1].status = true;
			for (auto& vis : vecVisitors)
			{
				if (vis.name == name)
				{
					vis.startTime = sTime;
					vis.status = status;
				}
			}
		}
	}
	else if (status == 3)
	{
	}
}

bool actionsWithVisitors::isPlace(string s)
{
	if (!isNumber(s))
	{
		return 0;
	}
	if (atoi(s.c_str()) < 0)
	{
		return 0;
	}
	countOfPlaces = atoi(s.c_str());
	return 1;
}

bool actionsWithVisitors::isOpenTime(string s)
{
	if (isTime(0, s) == "" || isTime(6, s) == "")
	{
		return false;
	}
	openTime = s.substr(0, 5);
	closeTime = s.substr(6, 5);
	return true;
}

string actionsWithVisitors::isTime(int startOfTime, string s)
{
	string h = s.substr(0 + startOfTime, 2);
	string m = s.substr(3 + startOfTime, 2);
	if (!isNumber(h) || atoi(h.c_str()) < 0 || atoi(h.c_str()) > 24)
	{
		return "";
	}
	if (!isNumber(m) || atoi(m.c_str()) < 0 || atoi(m.c_str()) > 60)
	{
		return "";
	}
	string time = s.substr(0 + startOfTime, 5);
	return time;
}

int actionsWithVisitors::hoursToMinuts(string s) {
	int hours, minutes;
	char colon;

	std::stringstream ss(s);

	if (ss >> hours >> colon >> minutes && colon == ':') {
		return hours * 60 + minutes;
	}
	else {
		std::cerr << "Ошибка: некорректный формат времени." << std::endl;
		return -1;
	}
}

void actionsWithVisitors::setPlaces(int count)
{
	for (int i = 0; i < count; i++) {
		vecTables.push_back({ 0, false });
	}
	countOfPlaces = count;
}

string actionsWithVisitors::minutesToHours(int totalMinutes)
{
	int hours = totalMinutes / 60;
	int minutes = totalMinutes % 60;

	char buffer[6];
	snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);

	return std::string(buffer);
}

bool actionsWithVisitors::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int actionsWithVisitors::countWords(string str)
{
	istringstream iss(str);
	string word;
	int count = 0;
	while (iss >> word) {
		count++;
	}

	return count;
}
