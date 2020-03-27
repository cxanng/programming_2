#include "cards.hh"
#include <iostream>
// TODO: Implement the methods here
using namespace std;
Cards::Cards(): top_(nullptr){
}

Cards::~Cards() {
    while ( top_ != nullptr) {
        Card_data* remove_card = top_;
        top_ = top_->next;
        
        delete remove_card;
    }
}

void Cards::add(int id) {
    Card_data* new_card = new Card_data
            ;
    new_card->data = id;
    new_card->next = nullptr;
    
    new_card->next = top_;
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    Card_data* card_to_be_printed = top_;
    int index = 1;
    while ( card_to_be_printed != nullptr) {
        s << index << ": " << card_to_be_printed->data << endl;
        ++index;
        card_to_be_printed = card_to_be_printed->next;
    }
}

bool Cards::remove(int &id) {
    if (!top_) {
        return false;
    }
    id = top_->data;
    Card_data* card_to_be_remove = top_;
    top_ = top_->next;
    delete card_to_be_remove;
    return true;
}

bool Cards::bottom_to_top() {
    if ( top_ == nullptr) {
        return false;
    }
    Card_data* temp = top_;
    Card_data* new_bottom = nullptr;
    while (temp->next != nullptr) {
        new_bottom = temp;
        temp = temp->next;
    }
    temp->next = top_;
    top_ = temp;
    new_bottom->next = nullptr;
    return true;
}

bool Cards::top_to_bottom() {
    if (!top_) {
        return false;
    }
    Card_data* bottom_ = top_;
    Card_data* temp = top_;
    while (bottom_->next != nullptr) {
        bottom_ = bottom_->next;
    }

    top_ = top_->next;
    bottom_->next = temp;
    temp->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s) {
    int i = 1;
    i = recursive_print(top_, s, i);
}

int Cards::recursive_print(Card_data* top, std::ostream &s, int &i) {
    if (top->next == nullptr) {
        s << 1 << ": " << top->data << endl;
        i++;
        return 1;
    }
    else{
        s << recursive_print( top->next, s, i) << ": " << top->data << endl;
        i++;
    }

    return i;
}

