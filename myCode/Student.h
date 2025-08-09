/*
 * Student.h
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>
#include <vector>
#include "Enrollment.h"
#include "Address.h"
#include "Poco/Data/Date.h"
class Student
{
private:
	/**
	 * @brief The student's unique Matrikel number (ID).
	 */
	unsigned int m_Matrikelnumber;

	/**
	 * @brief The student's first name.
	 */
	std::string m_firstName;

	/**
	 * @brief The student's last name.
	 */
	std::string m_lastName;

	/**
	 * @brief A list of the student's enrollments in courses.
	 */
	std::vector<Enrollment> m_enrollments;

	/**
	 * @brief The student's date of birth.
	 */
	Poco::Data::Date m_dateOfBirth;

	/**
	 * @brief The student's address details.
	 */
	Address m_studentAddress;
public:
	static unsigned int m_nextMatrikelNumber;

	/**
	 * @brief Default constructor for the Student class.
	 *
	 * Initializes a student object with a matrikel number of 0, the next
	 * matrikel number as 0,
	 * and a default date of birth set to January 1st, 2000.
	 */
	Student();

	/**
	 * @brief Constructor for the Student class.
	 *
	 * Initializes a student object with the provided details including
	 * the student's first and last name, address information, postal code,
	 * city name, additional info, and date of birth. The matrikel number is
	 * automatically assigned, and the next matrikel number is incremented.
	 *
	 * @param firstName The student's first name.
	 * @param lastName The student's last name.
	 * @param Addressname The student's address.
	 * @param postalCode The postal code of the student's address.
	 * @param cityName The city of the student's address.
	 * @param additionalInfo Additional information about the student's address.
	 * @param birthday The student's date of birth.
	 */
	Student(std::string firstName, std::string lastName,std::string Addressname,
	unsigned short postalCode,std::string cityName,std::string additionalInfo,
												     Poco::Data::Date birthday);


	/**
	 * @brief Copy constructor for the Student class.
	 *
	 * Creates a new Student object as a copy of the provided original student
	 * object. This includes copying the matrikel number, enrollments, name,
	 * address, and date of birth.
	 *
	 * @param orig The original Student object to copy from.
	 */
	Student(const Student& orig);
	virtual ~Student();


	unsigned int getMatrikelNumber() const;

	/**
	 * @brief Sets an enrollment for the student in a given course.
	 *
	 * Checks if the student is already enrolled in the specified course.
	 * If not, the new enrollment is added to the list.
	 * If the student is already enrolled in the course, no new enrollment
	 * is added.
	 *
	 * @param semester The semester in which the student is enrolled.
	 * @param course The course that the student is enrolling in.
	 * @param grade The grade achieved by the student in the course.
	 * @return True if the enrollment was successfully added; false if the
	 * student is already enrolled in the course.
	 */
	bool setEnrollment(std::string semester,Course const& course,
															   float grade = 0);
	std::string getFirstName();
	std::string getLastName();
	Address const& getAddress() const;

	/**
	 * @brief Removes an enrollment from the student's list of enrollments
	 * based on the course ID.
	 *
	 * Iterates through the student's enrollments and removes the enrollment
	 * if the course with the specified courseID is found.
	 * If the course is found and removed, the function returns true.
	 * Otherwise, it returns false.
	 *
	 * @param courseID The ID of the course to be removed.
	 * @return True if the enrollment was successfully removed; false if the
	 * course was not found.
	 */
	bool removeEnrollment(unsigned int courseID);
	std::vector<Enrollment> getEnrollments();
	void setMFirstName(const std::string &mFirstName);
	void setMLastName(const std::string &mLastName);
	void setAddress(Address address);
	Poco::Data::Date const& getDateOfBirth() const;
	void setDateOfBirth(const Poco::Data::Date mDateOfBirth);

	/**
	 * @brief Writes the student's data to the
	 * output stream in a formatted manner.
	 *
	 * The function writes the student's Matrikelnumber,
	 * last name, first name, date of birth, and address
	 * to the provided output stream. The data is separated
	 * by semicolons and the date is formatted as day.month.year.
	 * The student's address is written using the Address class's
	 * write function.
	 *
	 * @param out The output stream to write the student's data to
	 */
	virtual void write(std::ostream& out);

	/**
	 * @brief Reads student data from the input stream and populates the
	 *  student's attributes.
	 *
	 * The function reads the student's Matrikelnumber,
	 * last name, first name, date of birth (in day.month.year format),
	 * and address from the provided input stream. The date of birth is
	 * parsed and converted into a `Poco::Data::Date` object.
	 * After reading the basic student information, the student's
	 * address is read using the `Address::read` function.
	 *
	 * @param in The input stream from which to read the student's
	 * data
	 */
	virtual void read(std::istream& in);

	/**
	 * @brief Updates an existing enrollment in the student's enrollment list.
	 *
	 * This function iterates through the student's enrollments and searches
	 * for the course with the specified `courseKey`.
	 * Once the course is found, the corresponding enrollment
	 * is updated with the provided new `Enrollment` object.
	 *
	 * @param courseKey The unique identifier of the course whose
	 * enrollment is to be updated.
	 * @param newEnrollment The new enrollment details
	 * to replace the existing enrollment for the course.
	 */
	void updateEnrollment(unsigned int courseKey,Enrollment newEnrollment);
};

#endif /* STUDENT_H_ */
