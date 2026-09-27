#include "simulation.h"
#ifndef WORKER_UTILS_H
# define WORKER_UTILS_H

void sleep_remaining_cooldown(t_dongle *d, long long cooldown);
void print_status(t_coder *coder, const char *status);
long long get_remaining_cooldown(t_dongle *dongle, long long cooldown);
void precise_sleep(long long duration_ms, t_simulation *sim);

#endif
