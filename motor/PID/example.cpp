#include "pid.hpp"
#include <iostream>

using namespace std;

int main()
{

	cout << "PID example" << endl;
	PID::PID* x;
	x = new PID::PID(1);
	int i;
	int res;
	for(i=0;i<20200;i=i+100)
	{
		res = x->calcPID(20000, i);
		cout << "PID = " << res << endl;
	}

	return 1;

}

