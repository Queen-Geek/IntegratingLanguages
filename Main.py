from msilib import Table
import re
import string

#function displays multiplication Table
#@value is passed from C++ as an integer
#@returns multiplication table print statement using value and loop with digits 1-10

def MultiplicationTable(value):
    for i in range(1, 11):
        print(value, " x ", i, " = ", (value * i))
    return 0;
    
    #function displays doubled value
    #@value is passed from C++ as an integer
    #@returns print statement with value doubled
    def DoubleValue(value):
        print(value, " doubled is")
        value = value * 2
        return value