/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 *
 * Student's information:
 *
 * Name: The Anh Nguyen
 * Student number: 292126
 * User ID: cxanng
 * Email: anh.t.nguyen@tuni.fi
 *
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    // Constructor
    Instance(std::string instance_code, Course* course, Date date);

    /**
     * @brief is_named
     * @param name
     * This function takes a string as a parameter
     * and check if it is the Instance's name
     */
    bool is_named(std::string name);

    /**
     * @brief print
     * This function prints the starting date and
     * the number of student registered
     */
    void print();

    /**
     * @brief print_students
     * This function prints out informations of
     * students who registered to the instance
     */
    void print_students();

    /**
     * @brief add_student
     * @param student
     * This function adds the account pointer to
     * the student list
     */
    void add_student(Account *student);

    /**
     * @brief get_start_date
     * This function returns the starting date
     */
    Date get_start_date();

    /**
     * @brief get_course
     * This function returns a pointer to the course
     * to which this instance belongs
     */
    Course* get_course();

    /**
     * @brief get_name
     * This function returns the name of the instance
     */
    std::string get_name();

private:
    // Instance name
    std::string code_;

    // A pointer points to the course to which
    // the instance belongs
    Course* course_;

    // A list contains students who registered
    // to the instance
    std::vector<Account*> student_list_;

    // Starting date
    Date starting_;

};

#endif // INSTANCE_HH
