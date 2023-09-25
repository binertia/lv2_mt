#include "../minitalk.h"

static void	server_sig_handler(int sig_type, siginfo_t *info, void *ucontent)
{
	static int		bit;
	static unsigned char	c;

	if (!bit)
		bit = 8;
	if (sig_type == SIGUSR2)
		c += (1 << (bit - 1));
	bit--;
	if (!bit && c)
	{
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;
	pid_t			pid;
	char			*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	write(STDOUT_FILENO, pid_str, ft_strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
	free(pid_str);
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = &server_sig_handler;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		error_exit("Error : sending signal error(*USR1)\n");
	if (sigaction(SIGUSR2, &sig, NULL) == -1)
		error_exit("Error : sending signal error(*USR2)\n");
	while (1)
		pause();
	return (0);
}
