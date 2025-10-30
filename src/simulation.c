#include "philo.h"

//$ This file implements the philosopher simulation.

void    monitor(t_prog *p)
{
    while (p->sim_stop == 0)
    {
        unsigned    i;
        unsigned long   now;

        now = now_ms();
        i = 0;
        while (i < p->n_philo)
        {
            if (now - p->philos[i].last_meal >= p->t_die)
            {
                log_state(p->philos[i].id, MSG_DIED, &p->sim_stop);
                p->sim_stop = 1;
                break ;
            }
            if (p->n_to_eat != ~0u && p->philos[i].n_eaten < p->n_to_eat)
                break ;
            i++;
        }
        if (i == p->n_philo && p->n_to_eat != ~0u)
        {
            p->sim_stop = 1;
            break ;
        }
        usleep(100); // Check every 0.1 ms
    }
}

void	start_simulation(t_prog *p)
{
    unsigned	i;

    // Open the start barrier.
    p->s_barrier = 1;
    monitor(p);
    // Wait for all threads to finish.
    i = 0;
    while (i < p->n_philo)
    {
        pthread_join(p->th[i], NULL);
        i++;
    }
}