#include <iostream>
#include "TestSystem.h"





int main()
{
	TestSystem ts("source_folder", "destination_folder");
	//ts.makeTest({1, 2, 4, 8, 16});
	ts.makeTest({1, 2, 3, 4, 5, 6, 7, 8});
	system("pause");
}
