/*
 * BlockCourse.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "BlockCourse.h"

BlockCourse::BlockCourse()
{
}

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		float creditPoints, std::string Majorname, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course(CT_BLOCK, courseKey, title, creditPoints, Majorname), m_startDate(
				startDate), m_endDate(endDate), m_startTime(startTime), m_endTime(
				endTime)
{
	// TODO Auto-generated constructor stub

}

Poco::Data::Time BlockCourse::getMEndTime() const
{
	return m_endTime;
}

Poco::Data::Time BlockCourse::getMStartTime() const
{
	return m_startTime;
}

Poco::Data::Date BlockCourse::getMEndDate() const
{
	return m_endDate;
}

Poco::Data::Date BlockCourse::getMStartDate() const
{
	return m_startDate;
}

BlockCourse::~BlockCourse()
{
	// TODO Auto-generated destructor stub
}

void BlockCourse::write(ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << ";" << m_startDate.day() << "." << m_startDate.month() << "."
			<< m_startDate.year() << ";" << m_endDate.day() << "."
			<< m_endDate.month() << "." << m_endDate.year() << ";"
			<< m_startTime.hour() << ":" << m_startTime.minute() << ";"
			<< m_endTime.hour() << ":" << m_endTime.minute();
	return;
}

void BlockCourse::read(istream &in)
{

	Course::read(in);
	string parseBlockElements;
	//StartDate
	getline(in, parseBlockElements, ';');
	size_t dotPosition = parseBlockElements.find('.');
	int year, month, day;

	if (dotPosition != std::string::npos)
	{
		day = std::stoi(parseBlockElements.substr(0, dotPosition)); // Extract day
		size_t dotPosition2 = parseBlockElements.find('.', dotPosition + 1);

		if (dotPosition2 != std::string::npos)
		{
			month = std::stoi(
					parseBlockElements.substr(dotPosition + 1,
							dotPosition2 - dotPosition - 1)); // Extract month
			year = std::stoi(parseBlockElements.substr(dotPosition2 + 1)); // Extract year
		}
	}

	m_startDate = Poco::Data::Date
	{ year, month, day };

	// End Date
	getline(in, parseBlockElements, ';');
	dotPosition = parseBlockElements.find('.');

	if (dotPosition != std::string::npos)
	{
		day = std::stoi(parseBlockElements.substr(0, dotPosition));
		size_t dotPosition2 = parseBlockElements.find('.', dotPosition + 1);

		if (dotPosition2 != std::string::npos)
		{
			month = std::stoi(
					parseBlockElements.substr(dotPosition + 1,
							dotPosition2 - dotPosition - 1));
			year = std::stoi(parseBlockElements.substr(dotPosition2 + 1));
		}
	}

	m_endDate = Poco::Data::Date
	{ year, month, day };
	//StartTime
	getline(in, parseBlockElements, ';');
	size_t colonPosition = parseBlockElements.find(':');
	int hours = std::stoi(parseBlockElements.substr(0, colonPosition));
	int minutes = std::stoi(parseBlockElements.substr(colonPosition + 1));
	m_startTime = Poco::Data::Time
	{ hours, minutes, 0 };
	//EndTime
	getline(in, parseBlockElements, ';');
	colonPosition = parseBlockElements.find(':');
	hours = std::stoi(parseBlockElements.substr(0, colonPosition));
	minutes = std::stoi(parseBlockElements.substr(colonPosition + 1));
	m_endTime = Poco::Data::Time
	{ hours, minutes, 0 };

	return;
}
