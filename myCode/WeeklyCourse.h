/*
 * WeeklyCourse.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_
#include "Course.h"
#include <string>
#include <iostream>
class WeeklyCourse : public Course
{
private:
	/**
	 * @brief Stores the start time of the event/course.
	 *
	 * The start time is represented using the Poco::Data::Time class,
	 * which holds the time of day.
	 */
	Poco::Data::Time m_startTime;

	/**
	 * @brief Stores the end time of the event/course.
	 *
	 * The end time is represented using the Poco::Data::Time class,
	 *  which holds the time of day.
	 */
	Poco::Data::Time m_endTime;

	/**
	 * @brief Stores the day of the week for the event/course.
	 *
	 * The day of the week is represented as an enum value from
	 * Poco::DateTime::DaysOfWeek, where each value corresponds to a specific
	 * day
	 */
	Poco::DateTime::DaysOfWeek m_dayOfWeek;
public:
	WeeklyCourse();
	WeeklyCourse(unsigned int key,std::string title, float CPs,
			std::string majorName,Poco::Data::Time start,Poco::Data::Time end ,
											   Poco::DateTime::DaysOfWeek days);
	virtual ~WeeklyCourse();
	Poco::DateTime::DaysOfWeek getDaysOfWeek() const;
	Poco::Data::Time getMEndTime() const;
	Poco::Data::Time getMStartTime() const;

	/**
	 * @brief Writes the data of a weekly course to the output stream.
	 *
	 * This method overrides the write method of the Course class
	 * to include the specific details of the weekly course
	 * such as the day of the week, start time, and end time.
	 * It formats the information and writes it to the provided output stream.
	 *
	 * @param out The output stream where the course data is written.
	 */
	void write(std::ostream& out) const;

	/**
	 * @brief Reads the data of a weekly course from the input stream.
	 *
	 * This method overrides the `read` method of the Course class to include
	 * the specific details of the weekly course such as the day of
	 * the week and the start and end times.
	 * It reads the information from the input stream and updates the
	 * relevant member variables accordingly.
	 *
	 * @param in The input stream from which the course data is read.
	 */
	void read(std::istream& in);
};

#endif /* WEEKLYCOURSE_H_ */
