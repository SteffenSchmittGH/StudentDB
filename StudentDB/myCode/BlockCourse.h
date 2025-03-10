/*
 * BlockCourse.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_
#include "Course.h"
#include <iostream>
using namespace std;

class BlockCourse: public Course
{
private:
	/**
	 * @brief The start date of the block course.
	 *
	 * This member variable stores the starting date of the block course.
	 * It is represented as a Poco::Data::Date object
	 * containing the year, month, and day of the course's start date.
	 */
	Poco::Data::Date m_startDate;

	/**
	 * @brief The end date of the block course.
	 *
	 * This member variable stores the ending date of the block course.
	 * It is represented as a Poco::Data::Date object
	 * containing the year, month, and day of the course's end date.
	 */
	Poco::Data::Date m_endDate;

	/**
	 * @brief The start time of the block course.
	 *
	 * This member variable stores the starting time of the block course.
	 * It is represented as a Poco::Data::Time object
	 * containing the hour, minute, and second of the course's start time.
	 */
	Poco::Data::Time m_startTime;

	/**
	 * @brief The end time of the block course.
	 *
	 * This member variable stores the ending time of the block course.
	 * It is represented as a Poco::Data::Time object
	 * containing the hour, minute, and second of the course's end time.
	 */
	Poco::Data::Time m_endTime;
public:
	BlockCourse();
	BlockCourse(unsigned int courseKey, std::string title, float creditPoints,
			std::string Majorname, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);
	virtual ~BlockCourse();
	Poco::Data::Time getMEndTime() const;
	Poco::Data::Time getMStartTime() const;

	Poco::Data::Date getMEndDate() const;
	Poco::Data::Date getMStartDate() const;

	/**
	 * @brief Writes the block course data to the output stream.
	 *
	 * This function writes the block course's information
	 * to the provided output stream. It writes the base course data
	 * using the `Course::write(out)` method,
	 * followed by writing the start and end dates in the "day.month.year"
	 * format, and the start and end times in the "hour:minute" format.
	 * The output is formatted to match the block course structure.
	 *
	 * @param out The output stream to write the data to.
	 */
	void write(ostream &out) const;

	/**
	 * @brief Reads the block course data from the input stream.
	 *
	 * This function reads a block course's information from the provided input
	 * stream. It first reads the base course data using the ourse::read(in)
	 * method, followed by parsing the start date, end date, start time,
	 * and end time, extracting the relevant day, month, and year components
	 * for dates and hours and minutes for times.
	 * The parsed data is then stored in the respective member variables of the
	 * BlockCourse class.
	 *
	 * @param in The input stream to read the data from.
	 */
	void read(istream &in);
};

#endif /* BLOCKCOURSE_H_ */
