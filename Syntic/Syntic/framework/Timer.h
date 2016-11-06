#pragma once

#define MAX_DELTA_TIMES_TO_STORE 60

class sTimer
{
public:
	sTimer();
	~sTimer();

	// Update timer
	void				UpdateTime();

	// Return delta
	double				GetTimePassed();

	// Get elapsed time
	double				GetTotalTime();

	double				GetFPS();

private:
	void				UpdateDeltaTimerStore();
	double	newTime, deltaTime, oldTime, totalTime;
	double	deltaTimes[MAX_DELTA_TIMES_TO_STORE];
};

