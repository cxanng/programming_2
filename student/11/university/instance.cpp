#include "instance.hh"
#include "course.hh"
#include "account.hh"
#include <iostream>
#include <string>

Instance::Instance(std::string instance_code, Course* course,Date date):
    code_(instance_code), course_(course), student_list_({}), starting_(date)
{

}

// Prints out the starting date and number of students registered
void Instance::print(){
    std::cout << code_ << std::endl;
    std::cout << "    Starting date: " << starting_.get_day() << "." <<
              starting_.get_month() << "." << starting_.get_year() << std::endl;
    std::cout << "    Amount of students: " << student_list_.size() << std::endl;
}

// Prints informations of students who registered
void Instance::print_students() {
    for (auto *stu : student_list_) {
        std::cout << "    ";
        stu->print();
    }
}

// Checks if the string given is the instance's name
bool Instance::is_named(std::string name) {
    if (code_ != name) {
        return false;
    }
    return true;
}

// Adds a pointer pointing to the student who registered to the list
void Instance::add_student(Account *student) {
    // First check if this student has already registered to this instance.
    // Prints out the error message if that happens.
    bool check = false;
    for (auto *member: student_list_) {
        if (member == student) {
            std::cout << ALREADY_REGISTERED << std::endl;
            check = true;
            break;
        }
    }

    // Adds the pointer and prints out the signed up message
    if (!check) {
        student_list_.push_back(student);
        std::cout << SIGNED_UP << std::endl;
    }
}

// Returns the starting date
Date Instance::get_start_date() {
    return starting_;
}

// Returns the course pointer
Course* Instance::get_course() {
    return course_;
}

// Returns the instance name
std::string Instance::get_name() {
    return code_;
}
