#ifndef TIMER_H
#define TIMER_H

class Timer
{
	private:
		unsigned long startTime;
		unsigned long prevMillis;
		unsigned long prevEventMillis; //Last read from Timer (Last use of calc Diff)
		int rollovers;
		static int overallRollovers;
	public:
    	Timer();
		~Timer();
		void checkForRollover();
		double calcDiff();
};

#endif