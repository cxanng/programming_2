#include "queue.hh"
#include "iostream"

// Implement the member functions of Queue here
const unsigned int VEHICLES_PER_GREEN_PERIOD = 3;
Queue::Queue(unsigned int cycle): cycle_(cycle){
}
Queue::~Queue() {
    while( first_ != nullptr) {
        Vehicle *vehicle_to_be_deleted = first_;
        first_ = first_->next;
        delete vehicle_to_be_deleted;
    }
}

void Queue::enqueue(string reg) {
    if (is_green_ == false) {
        Vehicle *new_vehicle = new Vehicle;
        new_vehicle->reg_num = reg;
        new_vehicle->next = nullptr;
        if (first_ == nullptr) {
            first_ = new_vehicle;
            last_ = new_vehicle;
        }
        else {
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }
    }
    else {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" <<std::endl;
    }
}

void Queue::dequeue() {
    Vehicle* vehicle_to_move = first_;
    first_ = first_->next;
    delete vehicle_to_move;
}

void Queue::print() {
    if (is_green_) {
        std::cout << "GREEN: ";
    }
    else {
        std::cout <<"RED: ";
    }
    if (first_ == nullptr) {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    }
    else {
        std::cout << "Vehicle(s) ";
        Vehicle* temp = first_;
        while (temp != nullptr) {
            std::cout<< temp->reg_num + " ";
            temp = temp->next;
        }
        std::cout << "waiting in traffic lights" << std::endl;
    }
}

void Queue::switch_light() {
    if (is_green_) {
        is_green_ = false;
        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
    }
    else {
        if (first_ == nullptr) {
            is_green_ = true;
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        }
        else {
            std::cout << "GREEN: Vehicle(s) ";
            Vehicle *temp = first_;
            unsigned int count = 1;
            while (temp != nullptr && count <= cycle_ ) {
                std::cout << temp->reg_num + " ";
                dequeue();
                count++;
                temp = temp->next;
            }
            std::cout << "can go on" << std::endl;
        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}






