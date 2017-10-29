#ifndef TIMER_H
#define TIMER_H

class Timer{
	
		unsigned long prevMillis;
		unsigned long prevEventMillis; //Last read from Timer (Last use of calc Diff)
		int rollovers;
		static int overallRollovers;
	public:
    	Timer();		
		unsigned long checkForRollover();
		double calcDiff();
		~Timer();
};

#endif
