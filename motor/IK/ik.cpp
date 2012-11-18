#include "ik.hpp"
#include <iostream>
#include <string>


namespace ik {
	
	ik::ik()
	{
		std::cout << "called ik constructor" << std::endl;
		
	}


	int ik::setCounts(int LR, int S, int E, int W)
	{
		std::cout << "setting counts for ik... " << std::endl;
		ik::LRCount_current = LR;
		ik::SCount_current = S;
		ik::ECount_current = E;
		ik::WCount_current = W;
		
		std::cout << "Left-Right count = " << ik::LRCount_current << std::endl;
		std::cout << "Shoulder count = " << ik::SCount_current << std::endl;
		std::cout << "Elbow count = " << ik::ECount_current << std::endl;
		std::cout << "Wrist count = " << ik::WCount_current << std::endl;
		
		ik::xCoord = (LR+S)/2;
		ik::yCoord = (S+E)/2;
		ik::zCoord = (E+W)/2;

		std::cout << "calculating current coordinates... " << std::endl;
		std::cout << "current position: " << ik::xCoord << ", " << ik::yCoord << ", " << ik::zCoord << std::endl;
		
		return 1;
	}

	int ik::solveIK(int x, int y, int z)
	{
		std::cout << "solving ik for position: " << x << ", " << y << ", " << z << std::endl;
		return 1;	
	}
	
	int ik::returnXYZ()
	{
		std::cout << "returning the current position: " << ik::xCoord << ", " << ik::yCoord << ", " << ik::zCoord << std::endl;
		return 1;	
	}
	

	ik::~ik()
	{
		std::cout << "called ik destructor" << std::endl;
		
	}


} //end ik namespace

