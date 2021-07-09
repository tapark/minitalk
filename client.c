#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int ft_atoi(char *s)
{
	int num;
	int i;

	num = 0;
	i = 0;
	while (s[i])
	{
		num = num * 10;
		num = num + s[i++] - '0';
	}
	return (num);
}

int ft_itoa(int n)
{
	int len;
	int num;

	len = 0;
	num = n;
	while (num / 10 != 0)
	{
		len++;
		num = num / 10;
	}
}

char *char_to_binary_string(char c)
{
	char *dest;
	int i;

	dest = (char *)malloc(sizeof(char) * 9);
	i = 0;
	while (i < 8)
		dest[i++] = '0';
	dest[i] = '\0';
	i = 7;
	while (c / 2 != 0)
	{
		dest[i--] = c % 2 + '0';
		c = c / 2;
	}
	dest[i] = c % 2 + '0';
	return (dest);
}

void send_message_to_server(int pid, char *s)
{
	int i;
	int j;
	char *binary;

	i = 0;
	while (s[i])
	{
		binary = char_to_binary_string(s[i]);
		j = 0;
		printf("%s\n", binary);
		while (binary[j])
		{
			usleep(1);
			if (binary[j] == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j++;
		}
		i++;
		free(binary);
	}
}

int main(int argc, char **argv)
{
	int server_pid;
	int client_pid;
	char *binary;

	if (argc != 3)
		return (-1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 100 && 99998 < server_pid)
		return (-1);
	client_pid = getpid()
	printf("client pid : %d\n", client_pid);
	send_message_to_server(server_pid, argv[1]);
//	send_message_to_server(server_pid, argv[2]);

	return (0);
}