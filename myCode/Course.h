/*
 * Course.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef COURSE_H_
#define COURSE_H_
#include <map>
#include <string>
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"
#include <iostream>
class Course
{
public:
	enum courseType_t {CT_WEEKLY,CT_BLOCK,CT_NONE};
private:
	/**
	 * @brief Type of the course (e.g., lecture, seminar, etc.).
	 *
	 * Represents the category or classification of the course.
	 */
	courseType_t m_type;

	/**
	 * @brief Static map that associates course major IDs with their
	 * respective names.
	 *
	 * Used to store the mapping between the ID of a major and its
	 * corresponding name.
	 */
	static std::map<unsigned int, std::string> m_majorById;

	/**
	 * @brief Unique identifier for each course.
	 *
	 * The course key is used to uniquely identify each course in the database.
	 */
	unsigned int m_courseKey;

	/**
	 * @brief The title or name of the course.
	 *
	 * Holds the name of the course, such as "Introduction to Programming".
	 */
	std::string m_title;

	/**
	 * @brief The major associated with the course.
	 *
	 * Stores the ID of the major associated with the course, typically
	 * represented as a single character for simplicity
	 */
	unsigned char m_major;

	/**
	 * @brief The number of credit points awarded
	 * upon successful completion of the course.
	 *
	 * Represents the value or weight of the course in
	 * terms of academic credit points.
	 */
	float m_creditPoints;
public:
	Course();

	/**
	 * @brief Constructor for the Course class.
	 *
	 * Initializes a new instance of the `Course` class with the given parameter
	 * It sets the course type, key, title, credit points, and major name.
	 * The constructor also assigns the course's major based on the provided
	 * major name.
	 *
	 * @param type The type of the course (e.g., lecture, seminar, etc.).
	 * @param courseKey The unique identifier for the course.
	 * @param title The title of the course.
	 * @param creditPoints The number of credit points for the course.
	 * @param Majorname The name of the major associated with the course,
	 * which will be mapped to a major ID.
	 */
	Course(courseType_t type, unsigned int courseKey, std::string title,
								     float creditPoints, std::string Majorname);

	/**
	 * @brief Copy constructor for the Course class.
	 *
	 * Initializes a new `Course` object by copying data from another `Course` object.
	 *
	 * @param course The `Course` object to copy.
	 */
	Course(const Course& course);
	virtual ~Course();

	/**
	 * @brief Sets the course information from another `Course` object.
	 *
	 * Updates the current `Course` with values from the provided `course` object.
	 *
	 * @param course The `Course` object to copy values from.
	 */
	void setCourse(Course course);
	std::string getMajor() const;
	unsigned int getCourseKey() const;
	float getCPs() const;
	std::string getTitle() const;
	courseType_t getCourseType() const;
	virtual Poco::Data::Date getMStartDate() const;
	virtual Poco::Data::Date getMEndDate() const;
	virtual Poco::DateTime::DaysOfWeek getDaysOfWeek() const;
	virtual Poco::Data::Time getMEndTime() const;
	virtual Poco::Data::Time getMStartTime() const;

	/**
	 * @brief Writes the course information to an output stream.
	 *
	 * Outputs the course key, title, major, and credit points to the provided stream.
	 *
	 * @param out The output stream to write the course data to.
	 */
	virtual void write(std::ostream& out) const;

	/**
	 * @brief Reads course information from an input stream.
	 *
	 * Extracts the course key, title, major, and credit points from the provided input stream and stores them.
	 *
	 * @param in The input stream to read the course data from.
	 */
	void read(std::istream& in);
};

#endif /* COURSE_H_ */
