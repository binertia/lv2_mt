#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

//utils
void	error_exit(char *s);
char	*ft_itoa(int n);
int		strict_atoi(const char *str);
int		ft_strlen(char *s);
#endif
