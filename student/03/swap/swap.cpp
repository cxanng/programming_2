#include "swap.hh"

// TODO: Implement swap function here
using namespace std;

void swap(int& num1,int& num2) {
    int mid1 = num1, mid2 = num2;
    num1 = mid2;
    num2 = mid1;
}
