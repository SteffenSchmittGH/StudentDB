/*
 * Enrollment.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_
#include "Course.h"
#include <string>
#include <iostream>
class Enrollment
{
private:
	/**
	 * @brief Stores the grade of the enrollment.
	 *
	 * The grade is a floating-point value representing the performance score
	 * in the course.
	 */
	float m_grade;

	/**
	 * @brief Stores the semester in which the course was taken.
	 *
	 * The semester is represented as a string
	 */
	std::string m_semester;

	/**
	 * @brief Pointer to the course associated with this enrollment.
	 *
	 * This pointer points to a constant Course object inside of the database
	 */
	Course const* m_course;
public:
	Enrollment();
	Enrollment(float grade, std::string semester,Course const& course);
	Enrollment(Enrollment const& orig);
	virtual ~Enrollment();
	Course const* getCourse() const;
	std::string getSemester();
	void setGrade(float grade);
	float getGrade();

	/**
	 * @brief This method writes the enrollment data (course key, semester, and grade)
	 * into the provided output stream.
	 *
	 * @param out The output stream where the enrollment data is written.
	 */
	void write(std::ostream& out);

	/**
	 * @brief This method reads out an istream for enrolment datad
	 * @param in fstream file
	 *
	 * @return Enrollment for chained enrollment calls
	 */
	Enrollment read(std::istream& in);
};

#endif /* ENROLLMENT_H_ */
