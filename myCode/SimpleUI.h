/*
 * SimpleUI.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_
#include "StudentDB.h"
//class StudentDB;
class SimpleUI
{
private:
	/**
	 * @brief Pointer to the student database.
	 *
	 * This member variable manages all student-related data, including adding,
	 * searching, updating, and removing student records. It provides functions
	 * to interact with stored student objects and their associated information,
	 * such as enrollments and addresses.
	 */
	StudentDB *m_studentDatabase;

public:
	SimpleUI(StudentDB &db);
	virtual ~SimpleUI();
	void run();

	/**
	 * @brief Adds a new course to the student database.
	 *
	 * Prompts the user for course details, including key, credit points, title,
	 * and type (weekly or block).
	 * Depending on the type, additional information is collected for either
	 * BlockCourse or WeeklyCourse,
	 * which is then added to the database.
	 *
	 * @return void
	 */
	void addCourse();

	/**
	 * @brief Lists all courses in the student database and prints their details
	 *
	 * This function iterates through the list of courses in the database
	 * and displays their relevant attributes, such as title, key,
	 * major, credit points, and schedule. It differentiates between weekly
	 * and block courses and formats the output accordingly.
	 */
	void listCourses();

	/**
	 * @brief Adds a new student to the student database.
	 *
	 * This function prompts the user to enter the student's personal details,
	 * including address, name, and date of birth. It then creates a Student
	 * object with the provided data and adds it to the database.
	 *
	 * @param addressObj Reference to a Poco::Data::Date
	 * object to store the student's birthdate.
	 * This object is stored as global data in run
	 */
	void addStudent(Poco::Data::Date &poco);

	/**
	 * @brief Enrolls a student in a course.
	 *
	 * This function prompts the user to enter a students matriculation number,
	 * a course ID, and the current semester. It then retrieves the correspondin
	 * student and course from the database and attempts to enroll the student.
	 *
	 * If the student or course is not found, or if enrollment fails, an error
	 * message is displayed.
	 */
	void addEnrollment();

	/**
	 * @brief Searches for a student by name in the database.
	 *
	 * This function prompts the user to enter a student's full name,
	 * then extracts the first and last name.
	 * It searches the student database for matches based
	 * on either the first or last name and prints the corresponding
	 * matriculation numbers.
	 *
	 * If no matching students are found, no output is displayed.
	 */
	void searchStudent();

	/**
	 * @brief Prints detailed information about a student.
	 *
	 * This function prompts the user to enter a student's matriculation number
	 * and retrieves the student's information from the database. +
	 * It then displays the student's personal details, address, date of birth, and enrolled courses.
	 *
	 * If the student is not found or has no enrollments, appropriate messages
	 * are displayed.
	 */
	void printStudent();

	/**
	 * @brief Updates student information in the database.
	 *
	 * This function allows the user to modify a student's details, including
	 * their name, address, and enrollment records. The user selects which
	 * property to update and provides new values accordingly.
	 *
	 * If the student is not found or an invalid input is provided, appropriate
	 * error messages are displayed.
	 */
	void updateStudent();

	/**
	 * @brief Writes student database information to a file.
	 *
	 * This function prompts the user for a filename and writes the contents
	 * of the student database to the specified file. If the file opens
	 * successfully, the data is written; otherwise, no action is taken.
	 *
	 * The function ensures the file is properly closed after writing.
	 */
	void writeToFile();

	/**
	 * @brief Reads student database content from a file.
	 *
	 * This function prompts the user for a filename and attempts to read
	 * student database information from the specified file. Before reading,
	 * it asks the user for confirmation, as the current database content
	 * will be erased. If the user confirms, the existing database is cleared,
	 * and new data is loaded from the file.
	 *
	 * The function ensures that the file is properly opened before reading
	 * and closed afterward.
	 */
	void readFromFile();

	/**
	 * @brief Connects to the HDA server and adds students to the database.
	 *
	 * This function establishes a connection to the server at
	 * "www.hhs.users.h-da.cloud" on port "4242" to fetch student data in
	 * JSON format. It prompts the user for the number of students to add,
	 * then repeatedly sends a "generate" command to the server to retrieve
	 *  student information.
	 * The extracted data is then used to create Student objects, which are adde
	 * to the student database. If an error occurs while adding a student,
	 * an error message is displayed.
	 */
	void connectWithServer();
};

#endif /* SIMPLEUI_H_ */
