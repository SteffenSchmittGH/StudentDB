/*
 * SimpleUI.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "SimpleUI.h"
#include <iostream>
#include <fstream>


#include <boost/asio.hpp>
#include <boost/json/src.hpp>

using namespace std;

SimpleUI::SimpleUI(StudentDB &db)
{
	m_studentDatabase = &db;
}

SimpleUI::~SimpleUI()
{
}
void SimpleUI::addCourse()
{
	//Provide information about the course (eg. key and CPs)
	unsigned int key;
	float CPs;
	string majorName, title;
	cout << "You've chosen to create a new Course in "
			"the database." << endl;
	cout << "Please specify the: " << endl;
	cout << "Key: ";
	cin >> key;
	cout << "Credit Points: ";
	cin >> CPs;
	cout << "Name of assigned major: " << endl;
	//cin.ignore() is used to clear the leftover new line in the input buffer
	cin.ignore();
	getline(cin, majorName);
	cout << "Course Title: " << endl;
	getline(cin, title);
	cout << "Should the course be an Weekly course or an Block course?" << endl;
	cout << "Press 1 for BLOCK and 2 for WEEKLY!" << endl;
	int chooseCourseType = 0;
	cin >> chooseCourseType;
	//if else statement to seperate betweeen Weekly and Block course
	if (chooseCourseType == 1)
	{
		cout << "Provide information about start and end date: " << endl;
		cout << "Set day, month and year of start date: " << endl;
		cout << "Day: " << endl;
		int dayStart = 0;
		cin >> dayStart;
		cout << "Month: " << endl;
		int monthStart = 0;
		cin >> monthStart;
		cout << "Year: " << endl;
		int yearStart = 0;
		cin >> yearStart;
		cout << "Now set information about the End Date: " << endl;
		cout << "Start with Day: " << endl;
		int dayEnd = 0;
		cin >> dayEnd;
		cout << "Now Month for End Date: " << endl;
		int monthEnd = 0;
		cin >> monthEnd;
		cout << "Year for End Date: " << endl;
		int yearEnd = 0;
		cin >> yearEnd;
		//create a Poco::Data::Date object with the input datas
		Poco::Data::Date startDate(yearStart, monthStart, dayStart);
		Poco::Data::Date endDate(yearEnd, monthEnd, dayEnd);

		cout << "Now provide information about start and End TIME! " << endl;
		cout << "Set HOUR,MINUTE for StartTime! " << endl;
		cout << "Start with Hour(Start): " << endl;
		int hourStart = 0;
		cin >> hourStart;
		cout << "Continue with Minute(Start): " << endl;
		int minuteStart = 0;
		cin >> minuteStart;
		//create a Poco::Data::Time object with the input datas
		Poco::Data::Time startTime(hourStart, minuteStart, 0);

		cout << "Set hour and minute for END Time! " << endl;
		cout << "Start with Hour(END): " << endl;
		int hourEnd = 0;
		cin >> hourEnd;
		cout << "Continue with Minute(END): " << endl;
		int minuteEnd = 0;
		cin >> minuteEnd;

		Poco::Data::Time endTime(hourEnd, minuteEnd, 0);

		//when all datas for the constructor of BlockCourse are there,
		//object is added into the database.
		m_studentDatabase->addBlockCourse(BlockCourse
		{ key, title, CPs, majorName, startDate, endDate, startTime, endTime });
	}
	else if (chooseCourseType == 2)
	{
		//read in information for WeeklyCourse Type
		//Poco::Data::Time
		cout << "Provide information about start and end Time: " << endl;
		cout << "Set hour, minute and second of start time: " << endl;
		cout << "First hour: " << endl;
		int Starthour = 0;
		cin >> Starthour;
		cout << "Minutes: " << endl;
		int Startminute = 0;
		cin >> Startminute;
		Poco::Data::Time StartTime(Starthour, Startminute, 0);
		//Information for End Time
		cout << "Set hour, minute and second of END time: " << endl;
		cout << "First hour: " << endl;
		int Endthour = 0;
		cin >> Endthour;
		cout << "Minutes: " << endl;
		int Endminute = 0;
		cin >> Endminute;
		Poco::Data::Time EndTime(Endthour, Endminute, 0);
		//Days of Week (Attribute of Weekly Course)
		//Query the user for input datas. Switch case transforms integer to enum
		Poco::DateTime::DaysOfWeek weekDay;
		cout << "When should the Weekly Course take place?" << endl;
		cout << "(0) for Sunday" << endl;
		cout << "(1) for Monday" << endl;
		cout << "(2) for Tuesday" << endl;
		cout << "(3) for Wednesday" << endl;
		cout << "(4) for Thursday" << endl;
		cout << "(5) for Friday" << endl;
		cout << "(6) for Saturday" << endl;
		int chooseDay = 0;
		cin >> chooseDay;
		//Actual transformation userinput to enum
		switch (chooseDay)
		{
		case 0:
			weekDay = Poco::DateTime::DaysOfWeek::SUNDAY;
			break;
		case 1:
			weekDay = Poco::DateTime::DaysOfWeek::MONDAY;
			break;
		case 2:
			weekDay = Poco::DateTime::DaysOfWeek::TUESDAY;
			break;
		case 3:
			weekDay = Poco::DateTime::DaysOfWeek::WEDNESDAY;
			break;
		case 4:
			weekDay = Poco::DateTime::DaysOfWeek::THURSDAY;
			break;
		case 5:
			weekDay = Poco::DateTime::DaysOfWeek::FRIDAY;
			break;
		case 6:
			weekDay = Poco::DateTime::DaysOfWeek::SATURDAY;
			break;
		}
		//all datas for Constructor of Weekly Course are collected, so
		//object can be added into student database
		m_studentDatabase->addWeeklyCourse(WeeklyCourse
		{ key, title, CPs, majorName, StartTime, EndTime, weekDay });
	}
	else
	{
		//if input from user is not valid
		cout << "Option " << chooseCourseType << " not available!" << endl;
	}
	return;
}

void SimpleUI::listCourses()
{
	int countCourses = 0;
	//iterate through courses of database, to print their information.
	//therefore an constant address is used since the values cannot be
	//modified by users. (unique_ptr<const Course>)
	for (auto const &course : m_studentDatabase->listCourses())
	{
		cout << "---------------------------------------------" << endl;
		cout << "---------------------------------------------" << endl;
		//read out and print members of course
		countCourses++;
		cout << "Course " << countCourses << " has the following Elements: "
				<< endl;
		cout << "Course Title is: " << course->getTitle() << endl;
		cout << "Course Key is: " << course->getCourseKey() << endl;
		cout << "Course Major is : " << course->getMajor() << endl;
		cout << "Course CPs are: " << course->getCPs() << endl;
		//check for variable portType in class Course if weekly or block course
		//for this purpose an enum was created in class Course
		if (course->getCourseType() == Course::CT_WEEKLY)
		{
			cout << "Start Time: " << course->getMStartTime().hour() << ":"
					<< course->getMStartTime().minute() << endl;
			cout << "End Time: " << course->getMEndTime().hour() << ":"
					<< course->getMEndTime().minute() << endl;
			cout << "Day of Week: ";
			//Transform integer to enum to print
			switch (course->getDaysOfWeek())
			{
			case 0:
				cout << "Sunday" << endl;
				break;
			case 1:
				cout << "Monday" << endl;
				break;
			case 2:
				cout << "Tuesday" << endl;
				break;
			case 3:
				cout << "Wednesday" << endl;
				break;
			case 4:
				cout << "Thursday" << endl;
				break;
			case 5:
				cout << "Friday" << endl;
				break;
			case 6:
				cout << "Saturday" << endl;
				break;
			}
		}
		//check for variable portType in class Course if weekly or block course
		//for this purpose an enum was created in class Course
		//print attributes
		else if (course->getCourseType() == Course::CT_BLOCK)
		{
			cout << "Start Time: " << course->getMStartTime().hour() << ":"
					<< course->getMStartTime().minute() << " UHR" << endl;
			cout << "End Time: " << course->getMEndTime().hour() << ":"
					<< course->getMEndTime().minute() << " UHR" << endl;
			cout << "Start Date: " << course->getMStartDate().day() << "."
					<< course->getMStartDate().month() << "."
					<< course->getMStartDate().year() << endl;
			cout << "End Date: " << course->getMEndDate().day() << "."
					<< course->getMEndDate().month() << "."
					<< course->getMEndDate().year() << endl;
		}
		else
		{
			//Error Message if user input was wrong
			cout << "CT_NONE or other Type was set into courseType" << endl;
		}
		cout << "---------------------------------------------" << endl;
		cout << "---------------------------------------------" << endl;
	}
	return;
}
void SimpleUI::addStudent(Poco::Data::Date &addressObj)
{
	//Query Address information
	std::string Addressname;
	unsigned short postalCode = 0;
	std::string cityName;
	std::string additionalInfo;

	cout << "Enter the Address Information of the Student!" << endl;
	cout << "Start with Address Name" << endl;
	cin.ignore();
	getline(cin, Addressname);
	cout << "Continue with PostalCode: " << endl;
	cin >> postalCode;
	cout << "Futhermore, enter the city Name: " << endl;
	cin.ignore();
	getline(cin, cityName);
	cout << "Some room for Additional Information: " << endl;
	getline(cin, additionalInfo);
	cout << endl;

	//Query Student information
	cout << "Student section: " << endl;
	std::string firstName;
	std::string lastName;
	std::vector<Enrollment> enrollments;
	cout << "Enter First Name here: " << endl;
	getline(cin, firstName);
	cout << "Enter Last Name here: " << endl;
	getline(cin, lastName);

	//Query date of birth information
	int year, month, day;
	cout << "Enter Birthday, starting with day: " << endl;
	cin >> day;
	cout << "Continue with Month: " << endl;
	cin >> month;
	cout << "Now enter year(e.g. 1996): " << endl;
	cin >> year;
	cout << "The Birthday you've chosen is:" << endl;
	cout << day << "." << month << "." << year << endl;
	//assign queried information to addressObject(passedByReference)
	addressObj.assign(year, month, day);

	//Create Student Object and fill it with information
	Student localStudent(firstName, lastName, Addressname, postalCode, cityName,
			additionalInfo, addressObj);
	//add student to database
	m_studentDatabase->addStudent(localStudent);
}
void SimpleUI::addEnrollment()
{
	cout << "-----------" << endl;
	cout << "You want to Enroll ? Please Provide "
			"some information: " << endl;
	cout << endl;
	//Query information to search for Student and Course
	cout << "Type in Matrikelnumber here: " << endl;
	unsigned int matrikelnumber = 0;
	cin >> matrikelnumber;
	cout << "Now provide course id here: " << endl;
	unsigned int courseID = 0;
	cin >> courseID;
	//cin.ignore();
	//Provide information for Enrollment
	cout << "Now Provide the current Semester(string): " << endl;
	cin.ignore();
	string semester;
	getline(cin, semester);
	//Search for Course with CourseID and Query information
	//of course for enrollment.
	//(major, CPs, title)
	Course const *l_course;
	l_course = m_studentDatabase->getCourse(courseID);
	if (l_course == nullptr)
	{
		cout << "l_course is null Pointer" << endl;
	}
	//create pointer to student in database
	Student *l_stud = m_studentDatabase->getStudent(matrikelnumber);
	//used for printing information about success
	bool succeeded = false;
	//Error handling in case no student is in database
	if (l_stud != nullptr)
	{
		succeeded = l_stud->setEnrollment(semester, *l_course, 0);
	}
	else
	{
		succeeded = false;
		cout << "l_student is nullptr!" << endl;
	}
	//Provide Error Messages
	if (!succeeded)
	{
		cout << "Enrollment Failed!" << endl;
	}
	return;
}

void SimpleUI::printStudent()
{
	cout << "Yout ve chosen to print a Students information!" << endl;
	cout << "Provide the Matrikelnumber: " << endl;
	unsigned int matrikelnumber = 0;
	cin >> matrikelnumber;
	cout << "The Students Matrikelnumber is: " << matrikelnumber << endl;

	//Query student infos
	Student *tmp_stdud = m_studentDatabase->getStudent(matrikelnumber);
	if (tmp_stdud == nullptr)
	{
		cout << "No Student with this Matrikelnumber in the system !" << endl;
	}
	string studentFirstName;
	studentFirstName = tmp_stdud->getFirstName();
	cout << "The Students First Name is: " << studentFirstName << endl;
	string studentLastName;
	studentLastName = tmp_stdud->getLastName();
	cout << "The Students Last Name is: " << studentLastName << endl;
	//Query Birthday information from user
	int year = 0, month = 0, day = 0;
	Poco::Data::Date localBirthday(1000, 1, 1);
	localBirthday = tmp_stdud->getDateOfBirth();
	year = localBirthday.year();
	month = localBirthday.month();
	day = localBirthday.day();
	cout << "The Students Birthday is: " << day << "." << month << "." << year
			<< endl;

	cout << "-" << endl;
	cout << "The Students Address is: " << endl;
	cout << "City: " << tmp_stdud->getAddress().getCityName() << endl;
	cout << "Postal: " << tmp_stdud->getAddress().getPostalCode() << endl;
	cout << "Street: " << tmp_stdud->getAddress().getStreet() << endl;
	cout << "Additional Info: " << tmp_stdud->getAddress().getAdditionalInfo()
			<< endl;
	cout << "-" << endl;
	cout << "Student Course Information: " << endl;
	//Enrollments
	vector<Enrollment> studentEnrollments = tmp_stdud->getEnrollments();
	//User Information
	if (studentEnrollments.size() > 0)
	{
		//Student is enrolled
		cout << "Courses of Student are listed here: " << endl;
	}
	else
	{
		//Student is not enrolled at all
		cout << "Student is not Enrolled in any Course!" << endl;
	}
	cout << "The Students Courses are Listed here: " << endl;
	//print student information
	for (auto &enr : studentEnrollments)
	{
		cout << "---" << endl;
		cout << "Title: " << enr.getCourse()->getTitle() << endl;
		cout << "Course ID: " << enr.getCourse()->getCourseKey() << endl;
		cout << "Semester: " << enr.getSemester() << endl;
		cout << "Grade: " << enr.getGrade() << endl;
	}
	return;
}

void SimpleUI::searchStudent()
{
	//Query Name
	cout << "You ve chosen to search for a student." << endl;
	cout << "Provide Name: (e.g. Steffen Schmitt)" << endl;
	string Name;
	cin.ignore();
	getline(cin, Name);
	//Extract First and Last Name
	string firstName;
	string lastName;
	bool parseFirstName = true;
	for (unsigned int index_name = 0; index_name < Name.length(); index_name++)
	{
		// If we are still in the first name section
		if (parseFirstName)
		{
			if (Name[index_name] == ' ')
			{
				// If a space is found, stop collecting
				parseFirstName = false;
			}
			else
			{
				// Collect first name character
				firstName += Name[index_name];
			}
		}
		else
		{
			// Collect last name character
			lastName += Name[index_name];
		}
	}

	// Output the last name (and first name if needed)
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	//Query students in database as vector
	vector<Student*> tmp_student = m_studentDatabase->getStudentVector();
	for (auto &studis : tmp_student)
	{
		if (studis->getFirstName() == firstName
				|| studis->getLastName() == lastName)
		{
			cout << studis->getMatrikelNumber() << endl;
			cout << firstName << lastName << endl;
		}
	}
	return;
}
void SimpleUI::updateStudent()
{
	//Query information of matrikelnumber from user
	unsigned int matrikelnumber;
	cout << "-" << endl;
	cout << "Enter the Matrikelnumber of the Student: " << endl;
	cin >> matrikelnumber;
	//Query Student to update from studentDatabase
	//This student object will be updated, since pointer is not const
	Student *tmp_student = m_studentDatabase->getStudent(matrikelnumber);
	if (tmp_student == nullptr)
	{
		//Errorhandling for no student available
		cout << "Student not found in database!!!" << endl;
		cout << "Terminate Programm!" << endl;
	}
	//if student was found, print the some information to verify for user
	cout << "1. " << tmp_student->getFirstName() << " "
			<< tmp_student->getLastName() << endl;
	cout << "2. " << tmp_student->getAddress().getCityName() << ", "
			<< tmp_student->getAddress().getPostalCode() << ", "
			<< tmp_student->getAddress().getAdditionalInfo() << endl;
	//get students Enrollments and print course information
	vector<Enrollment> enr = tmp_student->getEnrollments();
	cout << "3. Courses: " << endl;
	for (auto it_enr : enr)
	{
		cout << "--------------------------------" << endl;
		const Course *course = it_enr.getCourse();
		cout << "Title: " << course->getTitle() << endl;
		cout << "Semester: " << it_enr.getSemester() << endl;
		cout << "CP's: " << course->getCPs() << endl;
		cout << "Major: " << course->getMajor() << endl;
		cout << "Grade: " << it_enr.getGrade() << endl;
		cout << "Semester: " << it_enr.getSemester() << endl;
	}
	//no futher purpose in code, just for user
	cout << "--------" << endl;
	unsigned int choseProperty = 0;
	//query user for information: which properties should be changed
	cout << "Which Property do you want to change?" << endl;
	cout << "Press 1 for change First and Last Name!" << endl;
	cout << "Press 2 for make changes in Address!" << endl;
	cout << "Press 3 to update Enrollment!" << endl;
	cin >> choseProperty;
	//Error Handling
	if (choseProperty == 0)
	{
		//possibility to terminate the update
		cout << "Update Terminated!" << endl;
	}
	else if (choseProperty == 1)
	{
		//Change first and Last Name
		cout << "You ve Chosen to change First and Last Name!" << endl;
		string firstName, lastName;
		cin.ignore();
		cout << "Type in firstName: " << endl;
		getline(cin, firstName);
		cout << "Type in Last Name: " << endl;
		getline(cin, lastName);
		//actual change of name(first,last)
		tmp_student->setMFirstName(firstName);
		tmp_student->setMLastName(lastName);
	}
	else if (choseProperty == 2)
	{
		//user has chosen to change address
		cout << "You've chosen to change Address! Type information!" << endl;
		cout << "City Name: " << endl;
		string cityName;
		cin.ignore();
		getline(cin, cityName);
		cout << "Postal Code: " << endl;
		unsigned short PostalCode;
		cin >> PostalCode;
		cout << "Additional Info: " << endl;
		string additionalInfo;
		cin.ignore();
		getline(cin, additionalInfo);
		cout << "Street Name: " << endl;
		string streetName;
		getline(cin, streetName);
		//update studetns address
		tmp_student->setAddress(Address
		{ streetName, PostalCode, cityName, additionalInfo });
	}
	else if (choseProperty == 3)
	{
		//Update Enrollment
		cout << "-" << endl;
		cout << "You have chosen to update the enrollment" << endl;
		cout << "1 for modify grade, 2 for remove enrollment." << endl;
		int choose = 0;
		cout << "Enter the number (1 or 2): " << endl;
		cin >> choose;
		//Change grade or remove the enrollmetn
		if (choose == 1)
		{
			//Change Grade for enrollment
			cout << "Changing the Grade for which course ? Course ID: " << endl;
			for (auto &it_enr : enr)
			{
				const Course *course = it_enr.getCourse();
				cout << course->getTitle() << " " << course->getCourseKey()
						<< endl;
			}
			unsigned int courseID;
			cin >> courseID;
			cout << "You ve chosen to enter a grade, please set it: " << endl;
			float grade;
			cin >> grade;
			vector<Enrollment> enrollmetnToChange =
					tmp_student->getEnrollments();
			for (auto &it_enr : enrollmetnToChange)
			{
				if (it_enr.getCourse()->getCourseKey() == courseID)
				{
					it_enr.setGrade(grade);
				}
			}
		}
		else if (choose == 2)
		{
			cout << "You ve chosen to remove the enrollmetn" << endl;
			cout << "Here is the list with Courses! Which one should be "
					"deleted?" << endl;
			for (auto &it_enr : enr)
			{
				const Course *course = it_enr.getCourse();
				cout << course->getTitle() << " Key: " << course->getCourseKey()
						<< endl;
			}
			cout << "Type Course Key to delete: " << endl;
			unsigned int IDtoDelete = 0;
			std::cin >> IDtoDelete;
			tmp_student->removeEnrollment(IDtoDelete);
		}
		else
		{
			//regarding grade or remove enrollment
			cout << "No valid choice!" << endl;
		}
	}
	else
	{
		//regarding Address Name or Enrollment
		cout << "Wrong user Input!!" << endl;
	}
	return;
}
void SimpleUI::writeToFile()
{
	cout << "You ve chosen to write the student Database Information into a"
			" file!" << endl;
	//create file object
	fstream myFile;
	cout << "type in a file name: (eg. output.txt)" << endl;
	string filename;
	cin >> filename;
	//fileobject is an outstream
	myFile.open(filename, ios::out);
	if (myFile.is_open())
	{
		//if file opens successfully call write methods
		m_studentDatabase->write(myFile);
	}
	//close the file
	myFile.close();
	return;
}
void SimpleUI::readFromFile()
{
	cout << "You ve choses to read the database content from a file!" << endl;
	cout << "The database content will be erased! Do you want to continue?(Y/n)"
			<< endl;
	// Checks if user really want to delete Database Content
	char continueErase = '\0';
	cin >> continueErase;
	if (continueErase == 'n')
	{
		cout << "Detetion Process Stopped!" << endl;
	}
	else
	{
		cout << "Delete Database content!" << endl;
		m_studentDatabase->clearDataBase();
		//Generate file object to read database content
		fstream myFileRead;
		string filename;
		cout << "Type a Filename: (eg. datas.txt)" << endl;
		cin >> filename;
		myFileRead.open("data.txt", ios::in);
		//Separate courses from students and check if file opend correct
		if (myFileRead.is_open())
		{
			m_studentDatabase->read(myFileRead);
		}
		//close file
		myFileRead.close();
	}
	return;
}

void SimpleUI::connectWithServer()
{
	cout << "Enter the number of Students you want to add via the server!"
			<< endl;
	int nbrToAddStudent = 0;
	cin >> nbrToAddStudent;
	int counter = 0;
	while (counter < nbrToAddStudent)
	{
		//connect to hda server
		boost::asio::ip::tcp::iostream jsonString("www.hhs.users.h-da.cloud",
				"4242");
		//pipe commands in server
		jsonString << "generate" << endl;
		jsonString << "quit" << endl;
		string line;
		std::vector<std::string> jsonData;
		//read out json data into string vector
		while (std::getline(jsonString, line))
		{
			jsonData.push_back(line);
		}
		// json string to a boost::json::value
		boost::json::value cell = boost::json::parse(jsonData[1]);
		// value to object
		boost::json::object obj = cell.as_object();
		//Search object location
		boost::json::object location = obj["location"].as_object();
		//read out values for Address
		string city = location["city"].as_string().c_str();
		string postalCodeStr = location["postCode"].as_string().c_str();
		unsigned short postalCode = static_cast<unsigned short>(stoi(
				postalCodeStr));
		string street = location["street"].as_string().c_str();
		//search name location and read out name
		boost::json::object name = obj["name"].as_object();
		string firstName = name["firstName"].as_string().c_str();
		string lastName = name["lastName"].as_string().c_str();
		//search birthday object and read out values
		boost::json::object birthday = obj["dateOfBirth"].as_object();
	    int year = birthday["year"].as_int64();
	    int month = birthday["month"].as_int64();
	    int day = birthday["day"].as_int64();

	    //save into db
		Poco::Data::Date PocoObj(year,month,day);
		try {
		    m_studentDatabase->addStudent(Student{
		        firstName, lastName, street, postalCode, city, "", PocoObj
		    });
		} catch (...) {
		    cout << "Error when creating studetn" << endl;
		}
		counter++;
	}
	return;
}
void SimpleUI::run()
{
	Poco::Data::Date globalPocoObj;
	while (true)
	{
		cout << "--" << endl;
		cout << "List of Available Commands:" << endl;
		cout << "Choose '1' for command: Add new Course" << endl;
		cout << "Choose '2' for command: List Courses" << endl;
		cout << "Choose '3' for command: Add new Student" << endl;
		cout << "Choose '4' for command: Add Enrollment" << endl;
		cout << "Choose '5' for command: Print Student" << endl;
		cout << "Choose '6' for command: Search Student" << endl;
		cout << "Choose '7' for command: Update Student" << endl;
		cout << "Choose '8' for command: Write To File" << endl;
		cout << "Choose '9' for command: Read from File" << endl;
		cout << "Choose '10' for command: Connect to Server" << endl;
		cout << "Chose a command, by select a number!" << endl;
		int userInput;
		cin >> userInput;

		switch (userInput)
		{
		case 1:
			addCourse();
			break;
		case 2:
			listCourses();
			break;
		case 3:
			addStudent(globalPocoObj);
			break;
		case 4:
			addEnrollment();
			break;
		case 5:
			printStudent();
			break;
		case 6:
			searchStudent();
			break;
		case 7:
			updateStudent();
			break;
		case 8:
			writeToFile();
			break;
		case 9:
			readFromFile();
			break;
		case 10:
			connectWithServer();
			break;
		default:
			cout << "Wrong user Input!!" << endl;
			break;
		}
	}
	return;
}
