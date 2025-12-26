#include "minishell.h"

int g_signal_status = 0;

static void handle_sigint(int sig)
{
    (void)sig;
    g_signal_status = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void init_signals(void)
{
    struct sigaction sa_init;
    struct sigaction sa_quit;

    sa_init.sa_handler = &handle_sigint;
    sa_init.sa_flags = SA_RESTART;
    sigemptyset(&sa_init.sa_mask);
    sigaction(SIGINT, &sa_init, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void set_signals_exec(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void set_signals_child(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}