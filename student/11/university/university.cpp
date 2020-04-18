#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_instance(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
            std::cout << CANT_FIND << params.at(0) << std::endl;
            return;
        }
    if (courses_.at(params.at(0))->has_instance(params.at(1))) {
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    }

    Instance *new_ins = new Instance(params.at(1), courses_.at(params.at(0)), utils::today);
    courses_.at(params.at(0))->new_instance(new_ins);

}

void University::sign_up_on_course(Params params)
{
    // Check if the parameters are correct.
    if (courses_.find(params.at(0)) == courses_.end()  ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    Course *course_to_sign_up = courses_.at(params.at(0));
    if (!course_to_sign_up->has_instance(params.at(1))) {
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(2)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }
    // Check if the student have already signed up for the instance
    if (!iter->second->add_instance(course_to_sign_up->get_instance(params.at(1)))) {
        return;
    }

    // Check if the instance is already started
    Date start = course_to_sign_up->get_instance(params.at(1))->get_start_date();
    if (start.operator<(utils::today)) {
        std::cout << "Error: Can't sign up on instance after the starting date." << std::endl;
        return;
    }
    course_to_sign_up->get_instance(params.at(1))->add_student(iter->second);

}

void University::complete_course(Params params)
{
    // Check if the parameters are correct
        if (courses_.find(params.at(0)) == courses_.end()  ){
            std::cout << CANT_FIND << params.at(0) << std::endl;
            return;
        }
        Course *course_to_complete = courses_.at(params.at(0));
        if (!course_to_complete->has_instance(params.at(1))) {
            std::cout << CANT_FIND << params.at(1) << std::endl;
            return;
        }
        std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(2)));
        if ( iter == accounts_.end() ){
            std::cout << CANT_FIND << params.at(2) << std::endl;
            return;
        }

        // Check if the student have signed up for the course
        Instance *complete_ins = course_to_complete->get_instance(params.at(1));
        if (!iter->second->complete_course(complete_ins)) {
            return;
        }
}

void University::print_signups(Params params)
{
    if (courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    courses_.find(params.at(0))->second->print_signups();

}

void University::print_study_state(Params params)
{
    // Check if the student number exists
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if (iter == accounts_.end()) {
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    Account student = *iter->second;
    std::cout << "Current:" << std::endl;
    for (Instance* ins : student.get_currents()) {
        ins->get_course()->print_info(false);
        std::cout << " " + ins->get_name() << std::endl;
    }

    std::cout << "Completed: " << std::endl;
    for (auto course : student.get_completed()) {
        course->print_info(true);
    }
    std::cout << "Total credits: " << student.get_credit() << std::endl;
}

void University::print_completed(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
        if (iter == accounts_.end()) {
            std::cout << CANT_FIND << params.at(0) << std::endl;
            return;
        }
        for (auto *course : iter->second->get_completed()) {
            course->print_info(true);
        }
        std::cout << "Total credits: " << iter->second->get_credit() << std::endl;
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
