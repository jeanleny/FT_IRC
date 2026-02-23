#include "BotGameMaster.hpp"

volatile sig_atomic_t    g_exit = 0;

void    sigint_handler(int sig)
{
    if (sig == SIGINT)
        g_exit = 1;
}

void    BotGameMaster::setSigaction()
{
    struct sigaction    act;

    bzero(&act, sizeof(act));
    act.sa_handler = &sigint_handler;
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
}
