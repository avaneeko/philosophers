#include "philo.h"

//$ This file defines a sleep_aware function, that induces microsleeps
// to still yield the thread, but wake up in small periods of time to check
// whether the simulation has stopped to stop it's own thread.

// Sleep, perdiodically waking up to check whether the simulation has to end.
// Returns non-zero if the simulation has to end, zero otherwise.

static unsigned long now_us(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)tv.tv_sec * 1000000ul + (unsigned long)tv.tv_usec;
}
int sleep_aware(int unsigned dur_us, int const volatile *sim_end)
{
    const unsigned long end = now_us() + dur_us;
	unsigned long now;
	unsigned long rem;

    while (!*sim_end)
    {
        now = now_us();
        if (now >= end)
            break;
        rem = end - now;
        /* Yield, but don't oversleep near the end */
        if (rem > 20000ul)
			usleep(rem / 4);   /* coarse chunk */
        else if (rem > 2000ul)
			usleep(1000);      /* ~1 ms */
        else
			usleep(200);       /* fine nudge */
    }
	return (*sim_end);
}
