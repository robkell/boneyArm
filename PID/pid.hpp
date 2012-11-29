#ifndef PID_H_
#define PID_H_

#include <fstream>
#include <string>

namespace PID {

class PID {
private:
	int id;
	int dest;
	int pos;
	int prev_error;
	int current_error;
	int P;
	int I;
	int D;
	int pid;

	#define Kp 0.1
	#define Ki 0
	#define Kd 0.02

public:
	PID(int id);
	virtual ~PID();

	int calcPID(int dest, int pos, long dt);
};

} /* namespace PID */
#endif /* PID_H_ */
