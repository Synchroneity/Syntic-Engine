#include "../Syntic.h"


sTimer::sTimer()
{
	newTime = deltaTime = oldTime = totalTime = 0.0f;
}

sTimer::~sTimer()
{
	newTime = deltaTime = oldTime = totalTime = 0.0f;
	ZeroMemory(deltaTimes, sizeof(deltaTimes));
}

void sTimer::UpdateDeltaTimerStore()
{
	for (int i = 0; i < MAX_DELTA_TIMES_TO_STORE - 1; i++)
	{
		deltaTimes[i] = deltaTimes[i + 1];
	}
	deltaTimes[MAX_DELTA_TIMES_TO_STORE - 1] = GetTimePassed();
}


void sTimer::UpdateTime()
{
	newTime = (double)((double)clock() / (double)CLOCKS_PER_SEC);
	deltaTime = newTime - oldTime;
	oldTime = newTime;
	totalTime += deltaTime;
	UpdateDeltaTimerStore();
}

double sTimer::GetTimePassed()
{
	return deltaTime;
}

double sTimer::GetTotalTime()
{
	return totalTime;
}

double sTimer::GetFPS()
{
	double result = 0;
	for (int i = 0; i < MAX_DELTA_TIMES_TO_STORE; i++)
	{
		result += deltaTimes[i];
	}
	result = result / (double)MAX_DELTA_TIMES_TO_STORE;
	return 1/result;
}
