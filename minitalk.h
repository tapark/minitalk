#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int get_current_time(void);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif