#include "../minitalk.h"

void	send_nul_term(int target_pid)
{
	int	bit;

	bit = 8;
	while (bit)
	{
		kill(target_pid, SIGUSR1);
		bit--;
		usleep(50);
	}
}

void	send_binary(char *str, pid_t target_pid)
{
	int		bit;
	unsigned char	c;

	if (ft_strlen(str) == 0)
		error_exit("Error : input is empty\n");
	while (*str)
	{
		bit = 7;
		while (bit >= 0)
		{
			c = *str;
			if (((c >> bit) & 1) == 0)
			{
				if (kill(target_pid, SIGUSR1) == -1)
					error_exit("Error : signal can't reach(USR1)");
			}
			else if (kill(target_pid, SIGUSR2) == -1)
				error_exit("Error : signal can't reach(USR1)");
			bit--;
			usleep(60);
		}
		str++;
	}
	send_nul_term(target_pid);
}

void	handle_client_sig(int sig_type, siginfo_t *sig_info, void *ucontent)
{
	char	*s;

	(void)ucontent;
	s = ft_itoa(sig_info -> si_pid);
	if (sig_type == SIGUSR1)
	{
		write(STDOUT_FILENO, "Server : ", 9);
		write(STDOUT_FILENO, s, ft_strlen(s)) ;
		write(STDOUT_FILENO, " > message transfer was successful\n", 35);
	}
	free(s);
}

int	main(int ac, char* av[])
{
	pid_t			target_pid;
	struct sigaction	sig;

	if (ac != 3)
		error_exit("Error : invalid input\n");
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = &handle_client_sig;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		error_exit("Error : invalid input\n");
	target_pid = strict_atoi(av[1]);
	send_binary(av[2], target_pid);
	while (1)
		pause();
	return (0);
}
