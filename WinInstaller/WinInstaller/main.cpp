#include "install.h"
#include <iostream>


using std::exception;
using std::cerr;
using std::endl;


int main()
{
	try
	{
		mywininstaller::install();
		return 0;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "An unhandled exception was thrown." << endl;
		return 1;
	}
}
