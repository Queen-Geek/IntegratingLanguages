#include "ValidationUtils.h"

ValidationUtils::ValidationUtils(int min, int max) {
    this->min = min;
    this->max = max;
}

//validates userSelection and called in cout statement to prompt for min and maxvalues in menu range
//@menuChoice is the user's input
//@returns false if user's menu choice is not one of the options

bool ValidationUtils::validateMenuChoice(int menuChoice) {
    if ((menuChoice < min) || (menuChoice > max)) {
        return false;
    }
    else {
        return true;
    }
}

//function defines minimum menu value
//@no parameter taken
//@returns minimum menu value

int ValidationUtils::getMinValue() {
    return min;
}

// function defines maximum menu value
//@no parameter taken
//@returns maximum menu value

int ValidationUtils::getMaxValue() {
    return max;
}