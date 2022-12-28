#include <Python.h>
#include <cmath>
#include <string>
#include <iostream>
#include <Windows.h>

#include "ValidationUtils.h"

using namespace std;

/*
function passess the parameters to the python function
@string value - calls the DoubleValue or MultiplicationTable function from thepython code
@integer value - passes the value to the python function
@returns value as double or multiplication table based on user menu selection 
*/
int callIntFunc(string proc, int param) {
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());
    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult= nullptr;
    
    // Initialize the Python Interpreter
    Py_Initialize();

    //Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    
    // Load the module object
    pModule = PyImport_Import(pName);
    
    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);
    
    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, procname);

    if (PyCallable_Check(pFunc)) {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    
    // Finish the Python Interpreter
    Py_Finalize();

    // clean
    delete[] procname;
    return _PyLong_AsInt(presult);
}

/*
display menu
@no parameters
@no return value 
*/
void printMenu() {
    cout << "1: Display a Multiplication Table" << endl;
    cout << "2: Double a Value" << endl;
    cout << "3: Exit" << endl;
    cout << "Enter your selection as a number 1, 2, or 3: ";
}
//displays main menu, gets user input, calls functions
void main() {
    int userSelection;
    int userNumber;
    const int menuChoice1 = 1;
    const int menuChoice2 = 2;
    const int menuChoice3 = 3;

    ValidationUtils validationUtils(menuChoice1, menuChoice3);
    
    printMenu();
    
    cin >> userSelection;
    
    while (userSelection != menuChoice3) {
        //conditional options from Menu based on user selection
        if (userSelection == menuChoice1) {
            cout << "Enter a number for Multiplication Table: ";
            cin >> userNumber;
            
            //handle user entering something other than integer
            if (cin.fail()) {
                cout << "Please enter a valid integer!";
                cin.clear(); //clear input
                cin.ignore(1000, '\n'); //ignore rest of the input line and get a new input
                
                cin >> userNumber;
            }
            
            cout << endl;
            callIntFunc("MultiplicationTable", userNumber);
            cout << endl;
            
            //printMenu again before cycling through loop
            printMenu();
            
            cin >> userSelection;
        }
        else if (userSelection == menuChoice2) {
            cout << "Enter a number to double: ";
            cin >> userNumber;
            
            //handle user entering something other than integer
            if (cin.fail()) {
                cout << "Please enter a valid integer!";
                cin.clear(); //clear input
                cin.ignore(1000, '\n'); //ignore rest of the input line andget a new input
                cin >> userNumber;
            }
            
            cout << endl;
            int value = callIntFunc("DoubleValue", userNumber);
            cout << value << endl;

            //printMenu again before cycling through loop
            printMenu();

            cin >> userSelection;
        }
        //validation of user input; if it's not one of the menu choices
        while (validationUtils.validateMenuChoice(userSelection) == false) {
            cout << "Please enter a valid choice " <<validationUtils.getMinValue() 
            << " to " << validationUtils.getMaxValue() << " :";
            cin.clear(); //clear input
            cin.ignore(1000, '\n'); //ignore rest of the input line and get anew input
            cin >> userSelection;
        }
    }
    
    //when user wants to exit
    while (userSelection == menuChoice3) {
        cout << "Goodbye." << endl;
        break;
    }
}