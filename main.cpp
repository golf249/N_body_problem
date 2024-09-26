#include "nbody.h"

int main()
{
    string fileName = "parameters.txt";			// store file name in a variable
    nbody Nbody(fileName);						// initialising the N body system
    Nbody.printFile();							// runs the function in class nbody to print values into a textfile
    return 0;
    }