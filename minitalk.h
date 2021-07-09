#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

typedef struct s_handler
{
	char	* binary;
	int 	index;
	int 	end_count;
	int 	is_client_pid;
}			t_handler;

int		ft_strlen(char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif