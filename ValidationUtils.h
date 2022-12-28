#pragma once

class ValidationUtils {
    public:
        ValidationUtils(int, int);
        bool validateMenuChoice(int);
        int getMinValue();
        int getMaxValue();
    
    private:
        int min;
        int max;
};