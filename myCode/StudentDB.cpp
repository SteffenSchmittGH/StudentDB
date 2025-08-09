/*
 * StudentDB.cpp
 *
 *  Created on: 10.01.2025
 *      Author: schmi
 */

#include "StudentDB.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
StudentDB::StudentDB()
{
	// TODO Auto-generated constructor stub

}

StudentDB::~StudentDB()
{
	// TODO Auto-generated destructor stub
}

void StudentDB::addWeeklyCourse(const WeeklyCourse &course)
{
	unsigned int key = course.getCourseKey();
	unique_ptr<const WeeklyCourse> local_course =
			make_unique<const WeeklyCourse>(key, course.getTitle(),
					course.getCPs(), course.getMajor(), course.getMStartTime(),
					course.getMEndTime(), course.getDaysOfWeek());
	m_courses.insert(
			pair<unsigned int, unique_ptr<const Course>>(key,
					std::move(local_course)));
	return;
}

void StudentDB::addBlockCourse(const BlockCourse &course)
{
	unsigned int key = course.getCourseKey();
	unique_ptr<const BlockCourse> local_course = make_unique<const BlockCourse>(
			key, course.getTitle(), course.getCPs(), course.getMajor(),
			course.getMStartDate(), course.getMEndDate(),
			course.getMStartTime(), course.getMEndTime());
	m_courses.insert(
			pair<unsigned int, unique_ptr<const BlockCourse>>(key,
					std::move(local_course)));
	return;
}

//with Course const* the Course obj can just read out. Can i now change the adress of the courses ?
vector<Course const*> StudentDB::listCourses() const
{
	vector<const Course*> courseList;
	for (auto &pair : m_courses)
	{
		courseList.push_back(pair.second.get());
	}
	return courseList;
}

void StudentDB::addStudent(Student student)
{
	m_students.insert(pair<int, Student>(student.getMatrikelNumber(), student));
}

Course const* StudentDB::getCourse(unsigned int key)
{
	auto it = m_courses.find(key);
	if (it != m_courses.end())
	{
		return m_courses[key].get();
	}
	else
	{
		return nullptr;
	}
}

Student* StudentDB::getStudent(unsigned int matrikelnumber)
{
	auto student = m_students.find(matrikelnumber); //returnsKeyValuePair
	if (student != m_students.end())
	{
		return &student->second;
	}
	return nullptr;
}

vector<Student*> StudentDB::getStudentVector()
{
	vector<Student*> tmp;
	for (auto pair : m_students)
	{
		tmp.push_back(&pair.second);
	}
	return tmp;
}


void StudentDB::clearDataBase()
{
	m_courses.clear();
	m_students.clear();
}

void StudentDB::write(std::ostream &out)
{
	out << m_courses.size() << endl;
	for (auto const &courses : this->listCourses())
	{
		courses->write(out);
		out << endl;
	}
	out << m_students.size() << endl;
	for (auto pair : m_students)
	{
		pair.second.write(out);
		out << endl;
	}
	for (auto pair : m_students)
	{
		std::vector<Enrollment> enrol = pair.second.getEnrollments();
		out << enrol.size() << endl;
		out << pair.second.getMatrikelNumber() << ";";
		for (auto enrollo : enrol)
		{
			out << enrollo.getCourse()->getCourseKey() << ";";
			out << enrollo.getSemester() << ";" << enrollo.getGrade();
		}
	}
	return;
}

void StudentDB::readCoursesIntoString(istream &in, string &line)
{
	int countCourses = 0;
	int maxCourses = 0;
	string tmp;
	getline(in, tmp);
	maxCourses = stoi(tmp);
	line += tmp;
	line += '\n';
	while (countCourses < maxCourses)
	{
		getline(in, tmp);
		line += tmp;
		line += '\n';
		countCourses++;
	}
	return;
}

void StudentDB::read(std::istream &in)
{
	//String to hold just courseDatas from &in
	string courseDatas;
	//reads course datas out from &in into courseData
	readCoursesIntoString(in, courseDatas);
	//transform this data into stream object again
	std::istringstream inputStream(courseDatas);

	//Process of course datas

	//get first line of stream object to identify number of courses
	string nbrCourses;
	int int_nbrCourses;
	getline(inputStream, nbrCourses);
	int_nbrCourses = stoi(nbrCourses);
	int courseCounter = 0;
	string courseType;
	//process courses until maximal number of courses is reached
	while (courseCounter < int_nbrCourses)
	{
		//get stream until delimiter expected value is Course identifier(W or B)
		getline(inputStream, courseType, ';');
		if (courseType == "W")
		{
			//call read function of weekly course
			WeeklyCourse weekly;
			weekly.read(inputStream);
			addWeeklyCourse(weekly);
		}
		else if (courseType == "B")
		{
			//call write function of block course
			BlockCourse block;
			block.read(inputStream);
			addBlockCourse(block);
		}
		else
		{
			cout << "Wrong input from file" << endl;
		}
		//keep track of number of courses
		courseCounter++;
	}
	//Process of Student datas(continue with processing &in)
	string nbrStudents;
	int int_nbrStudents;

	//next expected element is number of students
	getline(in, nbrStudents);
	//transform into integer to sava max number of students
	int_nbrStudents = stoi(nbrStudents);
	//create student counter
	int studentCounter = 0;
	while (studentCounter < int_nbrStudents)
	{
		//call read method of student for each student in (&in)
		Student student;
		student.read(in);
		addStudent(student);
		studentCounter++;
	}

	//Process of Enrollments
	string nbrEnrollments;
	int int_nbrEnrollments;
	//expected element is number of enrollments
	getline(in, nbrEnrollments);
	int_nbrEnrollments = stoi(nbrEnrollments);
	//create enrollment counter
	int enrollmetnCounter = 0;
	while (enrollmetnCounter < int_nbrEnrollments)
	{
		//create course and student
		//course should store read courseID in a first step.
		//course is also needed to create an enrollment.
		//course needs to be requested from DB.
		//student should set the Enrollment
		Course const *l_course;
		Student *l_student;
		//read and store matrikelnumber and courseID from &in
		string matrikelnumber;
		string courseID;
		getline(in, matrikelnumber, ';');
		getline(in, courseID, ';');
		//finally create the enrollment
		//get student with matrikelnumber from file
		l_student = getStudent(stoul(matrikelnumber));
		//get course with matrikelnumber from file
		l_course = getCourse(stoul(courseID));
		//set the enrollment of student with l_course
		l_student->setEnrollment("", *l_course, 0.0);
		//call read() method of enrollment with last added enrollment of student
		l_student->updateEnrollment(stoul(courseID),
				l_student->getEnrollments().back().read(in));
		//increase enrollment counter
		enrollmetnCounter++;
	}

	return;
}
