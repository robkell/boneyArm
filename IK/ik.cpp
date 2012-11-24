#include "ik.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>

#define PI 3.14159
#define LOW_LIMIT 0.0001
#define RAD2DEG (180/PI)
#define WRIST_LENGTH 90
#define SHOULDER_LENGTH 90
#define ELBOW_LENGTH 115
#define LEFTRIGHT_DPP 0.85
#define SHOULDER_DPP 0.55
#define ELBOW_DPP 0.5
#define WRIST_DPP 0.68

#define LEFTRIGHT_MIN -215
#define LEFTRIGHT_MAX 215
#define SHOULDER_MIN -20
#define SHOULDER_MAX 300
#define ELBOW_MIN -150
#define ELBOW_MAX 150
#define WRIST_MIN -70
#define WRIST_MAX 70


double round(double r)
{
	return (r>0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

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
		int tvl; //top view length
		std::cout << "solving ik for position: " << x << ", " << y << ", " << z << std::endl;
		//apply lower boudaries for x/y/z to prevent division by 0
		if(x==0)x=LOW_LIMIT;
		if(y==0)y=LOW_LIMIT;
		if(z==0)z=LOW_LIMIT;

		//check quadrant -> calc thetaLR
		if((x==LOW_LIMIT)&&(y==LOW_LIMIT))
		{
			/* catch the condition where
			 * x and y equal 0
			 */
			thetaLR = 0;
			std::cout << "thetaLR = " << thetaLR << std::endl;
		}
		else if((y>0)&&(x>0))
		{
			//First Quadrant
			thetaLR = atan2(y,x);
			std::cout << "Q1, thetaLR = " << thetaLR << std::endl;
		}
		else if((y>0)&&(x<0))
		{
			//Second Quadrant
			thetaLR = PI - atan2(y,std::fabs(x));
			std::cout << "Q2, thetaLR = " << thetaLR << std::endl;
		}
		else if((y<0)&&(x<0))
		{
			//Third Quadrant
			thetaLR = -PI + atan2(std::fabs(y),std::fabs(x));
			std::cout << "Q3, thetaLR = " << thetaLR << std::endl;
		}
		else
		{
			//Fourth Quadrant
			thetaLR = -atan2(y,std::fabs(x));
			std::cout << "Q4, thetaLR = " << thetaLR << std::endl;
		}
		
		tvl = sqrt((x*x) + (y*y));
		std::cout << "tvl: " << tvl << std::endl;
		std::vector< std::vector<int> > pulses;
		std::vector<int> pulses1;
		std::vector<int> pulses2;

		for (float phi = -2*PI; phi<=2*PI; phi=phi+(PI/90) )
		{
//			float phi=0;
			pulses1.clear();
			pulses2.clear();
			float yprime = z-WRIST_LENGTH*std::sin(phi);
			float yprimesq = yprime*yprime;
			float xprime = tvl-WRIST_LENGTH*std::cos(phi);
			float xprimesq = xprime*xprime;

//			std::cout << "X'^2: " << xprimesq << ", y'^2: " << yprimesq << std::endl;

			float length = sqrt( yprimesq+xprimesq );
			float stuff = ( ( (length*length) - (SHOULDER_LENGTH*SHOULDER_LENGTH) - (ELBOW_LENGTH*ELBOW_LENGTH) ) / (2*SHOULDER_LENGTH*ELBOW_LENGTH));

//			std::cout << "length: " << length << std::endl;
//			std::cout << "stuff: " << stuff << std::endl;

			float why = sqrt(1-(stuff*stuff));
//			std::cout << "why: " << why << std::endl;
			float thetaE1 = atan2(why,stuff);
			float thetaE2 = atan2(-sqrt(1-(stuff*stuff)),stuff);
//			std::cout << "thetaE1: " << thetaE1 << std::endl;
//			std::cout << "thetaE2: " << thetaE2 << std::endl;

			float in1 = atan2(ELBOW_LENGTH*sin(thetaE1), (SHOULDER_LENGTH+ELBOW_LENGTH*cos(thetaE1)) );
			float in2 = atan2(ELBOW_LENGTH*sin(thetaE2), (SHOULDER_LENGTH+ELBOW_LENGTH*cos(thetaE2)) );
			float out = atan2(yprime, xprime);
//			std::cout << "in1: " << in1 << std::endl;
//			std::cout << "out: " << out << std::endl;


			float thetaS1 = in2 + out;
			float thetaS2 = in1 + out;

			float thetaW1 = phi - thetaS1 - thetaE1;
			float thetaW2 = phi - thetaS2 - thetaE2;
			
			double LRPulses1 = round((thetaLR*RAD2DEG)/LEFTRIGHT_DPP);
			double SPulses1 = round((thetaS1*RAD2DEG)/SHOULDER_DPP);
			double EPulses1 = round((thetaE1*RAD2DEG)/ELBOW_DPP);
			double WPulses1 = round((thetaW1*RAD2DEG)/WRIST_DPP);

			double LRPulses2 = LRPulses1;
			double SPulses2 = round((thetaS2*RAD2DEG)/SHOULDER_DPP);
			double EPulses2 = round((thetaE2*RAD2DEG)/ELBOW_DPP);
			double WPulses2 = round((thetaW2*RAD2DEG)/WRIST_DPP);

			//std::cout<<"debug\n";
/*			if(isnan(SPulses1))
			{
				std::cout << "isnan" << std::endl;
			}
*/
			if(	(LRPulses1 < LEFTRIGHT_MAX)&&(LRPulses1 > LEFTRIGHT_MIN)
				&&(SPulses1 > SHOULDER_MIN)&&(SPulses1 < SHOULDER_MAX)
				&&(EPulses1 > ELBOW_MIN)&&(EPulses1 < ELBOW_MAX)
				&&(WPulses1 > WRIST_MIN)&&(WPulses1 < WRIST_MAX)
			)
			{
				//std::cout << "Pulses1 all in range!\nLR: " << LRPulses1 << " S: " << SPulses1 << " E: " << EPulses1 << " W: " << WPulses1 << std::endl;
				pulses1.push_back(LRPulses1);
				pulses1.push_back(SPulses1);
				pulses1.push_back(EPulses1);
				pulses1.push_back(WPulses1);
				pulses.push_back(pulses1);
			}
			if(	(LRPulses2 < LEFTRIGHT_MAX) && (LRPulses2 > LEFTRIGHT_MIN)
				&&(SPulses2 > SHOULDER_MIN) && (SPulses2 < SHOULDER_MAX)
				&&(EPulses2 > ELBOW_MIN) && (EPulses2 < ELBOW_MAX)
				&&(WPulses2 > WRIST_MIN) && (WPulses2 < WRIST_MAX) )
			{
				//std::cout << "Pulses2 all in range!\nLR: " << LRPulses2 << " S: " << SPulses2 << " E: " << EPulses2 << " W: " << WPulses2 << std::endl;
				pulses2.push_back(LRPulses1);
				pulses2.push_back(SPulses1);
				pulses2.push_back(EPulses1);
				pulses2.push_back(WPulses1);
				pulses.push_back(pulses2);
			}
/*			for(int i=0; i<pulses.size();i++){
				for(int j=0; j<4;j++){
					std::cout << "pulses [" <<i<<"]["<<j<<"] = "<< pulses[i][j] << std::endl;
				}
			}
*/

		}// end of for(phi)
		
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


