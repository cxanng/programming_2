/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add_instance
     * @param ins
     * This function checks if the instance has already been registered
     * and adds the instance to current list of the account
     */
    bool add_instance(Instance *ins);

    /**
     * @brief complete_course
     * @param ins
     * Adds the course to completed list, removes the instance from
     * the current list and add credits to the number of credits of
     * the student.
     */
    bool complete_course(Instance *ins);

    /**
     * @brief get_currents
     * Returns current instances
     */
    std::vector<Instance*> get_currents();

    /**
     * @brief get_completed
     * Returns completed courses
     */
    std::vector<Course*> get_completed();
    /**
     * @brief get_credit
     * Returns number of credits completed
     */
    unsigned int get_credit();


private:
    // Basic informations of the account user
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // List contains current instances and completed courses
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;

    // Number of credits earned
    unsigned int credits_;
};

#endif // ACCOUNT_HH
