#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number),
    current_({}),
    completed_({}),
    credits_(0)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}

// Prints basic informations of the account user
void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

// Returns email
std::string Account::get_email()
{
    return email_;
}

// Adds instance to current instance list
bool Account::add_instance(Instance *ins) {
    for (auto *instance : current_) {
        if (instance == ins) {
            std::cout << ALREADY_REGISTERED << std::endl;
            return false;
        }
    }
    current_.push_back(ins);
    return true;
}

// Completes course
bool Account::complete_course(Instance *ins) {
    std::vector<Instance*>::iterator iter = current_.begin();
    for (iter = current_.begin() ; iter != current_.end(); iter++) {
        if (*iter == ins) {
            completed_.push_back(ins->get_course());
            current_.erase(iter);
            credits_ += ins->get_course()->get_credits();
            std::cout << COMPLETED << std::endl;
            return true;
        }
    }
    std::cout << NO_SIGNUPS << std::endl;
    return false;
}

// Returns current
std::vector<Instance*> Account::get_currents() {
    return current_;
}

// Returns completed courses
std::vector<Course*> Account::get_completed() {
    return completed_;
}

// Returns credits
unsigned int Account::get_credit() {
    return credits_;
}
