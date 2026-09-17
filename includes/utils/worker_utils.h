#include "simulation.h"
#ifndef WORKER_UTILS_H
# define WORKER_UTILS_H

void sleep_remaining_cooldown(t_dongle *d, long long cooldown);
void print_status(t_coder *coder, const char *status);

#endif
