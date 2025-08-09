/*
 * WeeklyCourse.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "WeeklyCourse.h"
using namespace std;

WeeklyCourse::WeeklyCourse()
{
	m_dayOfWeek = Poco::DateTime::DaysOfWeek::MONDAY;
	m_endTime = Poco::Data::Time{0,0,0};
	m_startTime = Poco::Data::Time{0,0,0};
}

WeeklyCourse::WeeklyCourse(unsigned int key, string title, float CPs,
		string majorName, Poco::Data::Time start, Poco::Data::Time end,
		Poco::DateTime::DaysOfWeek days) :
		Course(CT_WEEKLY, key, title, CPs, majorName), m_startTime(start),
		m_endTime(end), m_dayOfWeek(days)
{
}

WeeklyCourse::~WeeklyCourse()
{
	// TODO Auto-generated destructor stub
}

Poco::Data::Time WeeklyCourse::getMEndTime() const
{
	return m_endTime;
}

Poco::Data::Time WeeklyCourse::getMStartTime() const
{
	return m_startTime;
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDaysOfWeek() const
{
	return m_dayOfWeek;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << ";" << m_dayOfWeek << ";" << m_startTime.hour() << ":"
			<< m_startTime.minute() << ";" << m_endTime.hour() << ":"
			<< m_endTime.minute();
	return;
}

void WeeklyCourse::read(istream &in)
{
	Course::read(in);
	string parseWeeklyElements;
	getline(in, parseWeeklyElements, ';');
	switch (stoi(parseWeeklyElements))
	{
	case 0:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::SUNDAY;
		break;
	case 1:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::MONDAY;
		break;
	case 2:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::TUESDAY;
		break;
	case 3:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::WEDNESDAY;
		break;
	case 4:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::THURSDAY;
		break;
	case 5:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::FRIDAY;
		break;
	case 6:
		m_dayOfWeek = Poco::DateTime::DaysOfWeek::SATURDAY;
		break;
	}
	getline(in, parseWeeklyElements, ';');
	size_t colonPosition = parseWeeklyElements.find(':');
	int hours = std::stoi(parseWeeklyElements.substr(0, colonPosition));
	int minutes = std::stoi(parseWeeklyElements.substr(colonPosition + 1));
	m_startTime = Poco::Data::Time
	{ hours, minutes, 0 };
	getline(in, parseWeeklyElements);
	colonPosition = parseWeeklyElements.find(':');
	hours = std::stoi(parseWeeklyElements.substr(0, colonPosition));
	minutes = std::stoi(parseWeeklyElements.substr(colonPosition + 1));
	m_endTime = Poco::Data::Time
	{ hours, minutes, 0 };
	return;
}
