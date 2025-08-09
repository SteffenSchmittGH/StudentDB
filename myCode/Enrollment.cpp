/*
 * Enrollment.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "Enrollment.h"
using namespace std;

Enrollment::Enrollment()
{
	m_grade = 0;
	m_course = nullptr;
}

Enrollment::Enrollment(float grade, std::string semester, Course const &course) :
		m_grade(grade), m_semester(semester), m_course(&course)
{
}
Enrollment::Enrollment(const Enrollment &orig)
{
	m_grade = orig.m_grade;
	m_semester = orig.m_semester;
	m_course = orig.m_course;
}

Enrollment::~Enrollment()
{
}

Course const* Enrollment::getCourse() const
{
	return m_course;
}

std::string Enrollment::getSemester()
{
	return m_semester;
}

void Enrollment::setGrade(float grade)
{
	m_grade = grade;
	return;
}

void Enrollment::write(ostream &out)
{
	out << this->getCourse()->getCourseKey() << ";" << m_semester << ";"
			<< m_grade;
	return;
}

float Enrollment::getGrade()
{
	return m_grade;
}

Enrollment Enrollment::read(std::istream &in)
{
	//Next expected element is semseter
	string semester;
	getline(in, semester, ';');
	m_semester = semester;
	//Next expected element is Grade
	string grade_str;
	getline(in, grade_str);
	m_grade = stof(grade_str);
	return *this;
}
