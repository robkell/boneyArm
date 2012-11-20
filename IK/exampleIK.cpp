#include "ik.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

int main()
{
	cout << "example IK!" << endl;

	ik::ik* a;
	a = new ik::ik();

	a->setCounts(3, 34, 334, 99);
	a->solveIK(100, 150, 200);
	a->returnXYZ();
	
	return 0;

}
