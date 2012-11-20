//#ifndef CPWM_H_
//#define CPWM_H_

#include <fstream>
#include <string>

namespace ik {

	class ik {
		private:
			std::string id;
			int xCoord;
			int yCoord;
			int zCoord;

			int LRAngle;
			int SAngle;
			int EAngle;
			int WAngle;

			int LRCount_current;
			int SCount_current;
			int ECount_current;
			int WCount_current;

			int LRCount_required;
			int SCount_required;
			int ECount_required; 
			int WCount_required;

			#define	LRMaxPulses 100
			#define	LRMinPulses 100
			#define	SMaxPulses 100
			#define	SMinPulses 100
			#define	EMaxPulses 100
			#define	EMinPulses 100
			#define	WMaxPulses 100
			#define	WMinPulses 100
			
			#define	LRDegPerPulse 100
			#define	SDegPerPulse 100
			#define	EDegPerPulse 100
			#define	WDegPerPulse 100
			

		//	#define SYSFS_PWM_PREFIX "/sys/class/pwm/"
		//	std::ofstream sysfsfid_request;

		public:
			ik();
			virtual ~ik();

			int setCounts(int LR, int S, int E, int W);
			int solveIK(int x, int y, int z);
			int returnXYZ();
	};

} /* namespace ik */
//#endif /* CPWM_H_ */
