/*
 * Student.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "Student.h"
#include <iostream>
using namespace std;
unsigned int Student::m_nextMatrikelNumber = 100000;
Student::Student()
{
	m_Matrikelnumber = 0;
	m_nextMatrikelNumber = 0;
	m_dateOfBirth = Poco::Data::Date
	{ 2000, 1, 1 };
}
Student::Student(std::string firstName, std::string lastName,
		std::string Addressname, unsigned short postalCode,
		std::string cityName, std::string additionalInfo,
		Poco::Data::Date birthday)
{
	m_firstName = firstName;
	m_lastName = lastName;
	m_Matrikelnumber = m_nextMatrikelNumber;
	m_nextMatrikelNumber++;
	m_studentAddress = Address
	{ additionalInfo, postalCode, cityName, additionalInfo };
	this->setDateOfBirth(birthday);
}

Student::Student(const Student &orig)
{
	m_Matrikelnumber = orig.m_Matrikelnumber;
	m_enrollments = orig.m_enrollments;
	m_firstName = orig.m_firstName;
	m_lastName = orig.m_lastName;
	m_nextMatrikelNumber = orig.m_nextMatrikelNumber;
	m_studentAddress = orig.m_studentAddress;
	m_dateOfBirth = orig.m_dateOfBirth;
}

Student::~Student()
{
	// TODO Auto-generated destructor stub
}

unsigned int Student::getMatrikelNumber() const
{
	return m_Matrikelnumber;
}

bool Student::setEnrollment(string semester, Course const &course, float grade)
{
	bool enrollmentNew = true;

	if (m_enrollments.empty())
	{
		m_enrollments.push_back(Enrollment
		{ grade, semester, course });
	}
	else
	{
		for (auto &enrollments : m_enrollments)
		{
			if (enrollments.getCourse()->getCourseKey()
					== course.getCourseKey())
			{
				//if course already exists, set false
				enrollmentNew = false;
			}
			else
			{
				//Add Enrollment
				m_enrollments.push_back(Enrollment
				{ grade, semester, course });
			}
		}
	}
	return enrollmentNew;
}

string Student::getFirstName()
{
	return m_firstName;
}

string Student::getLastName()
{
	return m_lastName;
}

Address const& Student::getAddress() const
{
	return m_studentAddress;
}

std::vector<Enrollment> Student::getEnrollments()
{
	return m_enrollments;
}

void Student::setMFirstName(const std::string &mFirstName)
{
	m_firstName = mFirstName;
}

void Student::setMLastName(const std::string &mLastName)
{
	m_lastName = mLastName;
}

void Student::setAddress(Address address)
{
	m_studentAddress = address;
}

bool Student::removeEnrollment(unsigned int courseID)
{
	//iterates through enrollments until coursekey is found
	for (auto it_enr = m_enrollments.begin(); it_enr != m_enrollments.end();)
	{
		if (courseID == it_enr->getCourse()->getCourseKey())
		{
			// Erase returns the next valid iterator
			it_enr = m_enrollments.erase(it_enr);
			return true;
		}
		else
		{
			//Only increment if no erase happened
			++it_enr;
		}
	}
	return false;
}

void Student::setDateOfBirth(const Poco::Data::Date mDateOfBirth)
{
	m_dateOfBirth = mDateOfBirth;
}

Poco::Data::Date const& Student::getDateOfBirth() const
{
	return m_dateOfBirth;
}

void Student::write(ostream &out)
{
	out << m_Matrikelnumber << ";" << m_lastName << ";" << m_firstName << ";"
			<< m_dateOfBirth.day() << "." << m_dateOfBirth.month() << "."
			<< m_dateOfBirth.year() << ";";
	m_studentAddress.write(out);
	return;
}

void Student::read(std::istream &in)
{
	//read out matrikelnumber
	string matrklnbr;
	getline(in, matrklnbr, ';');
	unsigned int matrikelnmmer = stoul(matrklnbr);
	m_Matrikelnumber = matrikelnmmer;
	m_nextMatrikelNumber = m_Matrikelnumber + 1;
	//Last name next expected value
	getline(in, m_lastName, ';');
	//First Name next expected value
	getline(in, m_firstName, ';');
	//Birthday next expected value
	string birthday;
	getline(in, birthday, ';');
	size_t dotPosition1 = birthday.find('.');
	size_t dotPosition2 = birthday.find('.', dotPosition1 + 1);
	// Extract day
	int day = std::stoi(birthday.substr(0, dotPosition1));
	// Extract month
	int month = std::stoi(
			birthday.substr(dotPosition1 + 1, dotPosition2 - dotPosition1 - 1));
	// Extract year
	int year = std::stoi(birthday.substr(dotPosition2 + 1));
	m_dateOfBirth = Poco::Data::Date
	{ year, month, day };
	//Read Address from file
	m_studentAddress.read(in);
	return;
}

void Student::updateEnrollment(unsigned int courseKey, Enrollment newEnrollment)
{
	//iterate through enrollments until course key fits
	//used in StudentDB, to add enrollment to student
	for (auto &enr : m_enrollments)
	{
		if (enr.getCourse()->getCourseKey() == courseKey)
		{
			//add Enrollment
			enr = newEnrollment;
		}
	}
	return;
}
