/*
 * Course.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "Course.h"
using namespace std;
std::map<unsigned int, std::string> Course::m_majorById =
{
{ 'A', "Automation" },
{ 'C', "Communication" },
{ 'E', "Embedded" },
{ 'P', "Power" } };

Course::Course()
{
	m_courseKey = 0;
	m_creditPoints = 0.0;
	m_major = 'E';
	m_type = Course::CT_NONE;
}

Course::Course(courseType_t type, unsigned int courseKey, std::string title,
		float creditPoints, std::string Majorname)
{
	m_courseKey = courseKey;
	m_creditPoints = creditPoints;
	m_title = title;
	m_type = type;

	for (auto major : m_majorById)
	{
		if (major.second == Majorname)
		{
			m_major = major.first;
		}
	}
}

Course::Course(const Course &course)
{
	m_courseKey = course.getCourseKey();
	m_creditPoints = course.getCPs();
	m_title = course.getTitle();
	m_type = course.m_type;
	for (auto pair : m_majorById)
	{
		string major = course.getMajor();
		if (pair.second == major)
		{
			m_major = pair.first;
		}
	}
}

Course::~Course()
{
	// TODO Auto-generated destructor stub
}

std::string Course::getMajor() const
{
	return m_majorById.at(m_major);
}

unsigned int Course::getCourseKey() const
{
	return m_courseKey;
}

float Course::getCPs() const
{
	return m_creditPoints;
}

string Course::getTitle() const
{
	return m_title;
}

Course::courseType_t Course::getCourseType() const
{
	return m_type;
}

Poco::Data::Date Course::getMStartDate() const
{
	return Poco::Data::Date(0, 0, 0);
}

Poco::Data::Date Course::getMEndDate() const
{
	return Poco::Data::Date(0, 0, 0);
}

Poco::DateTime::DaysOfWeek Course::getDaysOfWeek() const
{
	return Poco::DateTime::DaysOfWeek::MONDAY;
}

Poco::Data::Time Course::getMEndTime() const
{
	return Poco::Data::Time(0, 0, 0);
}

Poco::Data::Time Course::getMStartTime() const
{
	return Poco::Data::Time(0, 0, 0);
}

void Course::write(std::ostream &out) const
{
	out << m_courseKey << ";" << m_title << ";" << m_major << ";"
			<< m_creditPoints;
	return;
}

void Course::setCourse(Course course)
{
	m_courseKey = course.getCourseKey();
	m_creditPoints = course.getCPs();
	m_major = course.getMajor()[0];
	m_title = course.getTitle();
	m_type = course.getCourseType();
	return;
}

void Course::read(std::istream &in)
{
	string courses;
	string tmp;
	getline(in, tmp, ';');
	//conversion to unsigned short
	m_courseKey = stoul(tmp);
	getline(in, tmp, ';');
	m_title = tmp;
	getline(in, tmp, ';');
	m_major = tmp[0];
	getline(in, tmp, ';');
	m_creditPoints = stof(tmp);
	return;
}
