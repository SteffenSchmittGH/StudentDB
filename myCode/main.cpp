// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"
#include "SimpleUI.h"
#include <Poco/Data/Date.h>
// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "StudentDB started." << endl << endl;
	StudentDB myDB;
	SimpleUI myUI(myDB);
	myUI.run();

	return 0;
}
