#include "array_operations.hh"

int greatest_v1(int* itemptr, int size) {
    int max_value = *itemptr;
    for (int* position = itemptr; position < itemptr + size; position++) {
        if (*position > max_value) {
            max_value = *position;
        }
    }
    return max_value;
}

int greatest_v2(int *itemptr, int *endptr) {
    int max_value = *itemptr;
    for (int* position = itemptr; position < endptr; position++) {
        if (*position > max_value) {
            max_value = *position;
        }
    }
    return max_value;
}

void copy(int *itemptr, int *endptr, int *targetptr) {
    int i = 0;
    for (int* position = itemptr; position < endptr; position++) {
        *(targetptr + i) = *position;
        i++;
    }
}

void reverse(int *leftptr, int *rightptr) {
    int i = 1;
    for (int* position = leftptr; position < rightptr; ++position) {
        if(position >= rightptr - i) {
            continue;
        }
        int center = *position;
        *position = *(rightptr - i);
        *(rightptr - i) = center;
        ++i;
    }
}
