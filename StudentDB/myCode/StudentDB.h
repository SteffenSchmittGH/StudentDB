/*
 * StudentDB.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_
#include "Student.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include <memory>
#include <set>
#include <iostream>
class StudentDB
{
private:
	/**
	 * @brief A map of student IDs (Matrikelnumber)
	 * to corresponding student objects. Actual Database for students
	 */
	std::map<int,Student> m_students;


	/**
	 * @brief A map of course IDs to unique pointers of constant Course objects.
	 * Actual Database for Courses.
	 */
	std::map<int,std::unique_ptr<const Course>> m_courses;
public:
	/**
	 * @brief Standard constructor.
	 */
	StudentDB();

	/**
	 * @brief Destructor.
	 */
	virtual ~StudentDB();

	/**
	 * @brief This method adds objects of type BlockCourse to the Database.
	 * @param course Block Course to be added to the database
	 */
	void addBlockCourse(const BlockCourse& course);

	/**
	 * @brief This method adds objects of type WeeklyCourse to the Database.
	 * @param course Weekly Course to be added to the database
	 */
	void addWeeklyCourse(const WeeklyCourse& course);

	/**
	 * @brief This method lists all the courses of the database. Therefore,
	 * it needs to access the member m_courses of this class, which is a map.
	 * This map holds as second a unique pointer with constant Course elements.
	 * In order to access those elements it needs to be ensured, not to
	 * modify these courses. Hence, this method needs to be const and its return
	 * type needs to be a pointer whos value can not be modified. (to protect
	 * database content)
	 *
	 * @return returns a vector which holds pointers which cannot be modified in
	 * their value to the databases (m_courses) courses.
	 */
	std::vector<const Course*> listCourses() const;

	/**
	 * @brief This function provides the user with a course of the database.
	 * This functions has just read out purposes.
	 * @param courseKey the key to access a specific course
	 *
	 * @return Pointer which is not enabled to modify its value to the
	 * course elements of database.
	 */
	Course const* getCourse(unsigned int courseKey);

	/**
	 * @brief This method adds a new student to the database. It inserts the
	 * student into the m_students map, where the key is the student's
	 * Matrikelnumber and the value is the student object.
	 * The insertion process ensures that the student is properly stored in the
	 * database, using their Matrikelnumber as the unique key.
	 *
	 * @param student The student object to be added to the database.
	 */
	void addStudent(Student student);


	Student* getStudent(unsigned int matrikelnumber);

	std::vector<Student*> getStudentVector();

	/**
	 * @brief This method clears the entire student and course databases.
	 * It removes all entries from both the m_students and m_courses maps,
	 * effectively resetting the database to an empty state.
	 * This operation is irreversible and erases all
	 * stored student and course data.
	 */
	void clearDataBase();

	/**
	 * @brief This method reads course data from an input stream and stores
	 * it into a string. It first reads the total number of courses, then
	 * reads each courses data and appends it to the provided string.
	 * The string is updated to contain all the course information.
	 *
	 * @param in The input stream from which course data is read.
	 * @param line The string that will hold the course data after being read.
	 */
	void readCoursesIntoString(istream& in, string& line);

	/**
	 * @brief This method writes the course and student data from the database
	 * an output stream. It first writes the total number of courses and each
	 * courses details, followed by the number of students and each students
	 * details. Then, it writes enrollment information for each student,
	 * including the enrolled courses, semesters, and grades.
	 *
	 * @param out The output stream to which the course, student, and enrollment
	 * data is written.
	 */
	void write(std::ostream& out);

	/**
	 * @brief This function reads in content from a file.
	 * The file must be written in a comma seperated value manner where the
	 *  delimiter are semicolon (;).
	 * It will read in the Information from the file and store it in database.
	 */
	void read(std::istream& out);
};
#endif /* STUDENTDB_H_ */
