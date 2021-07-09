#include "minitalk.h"

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
	int len;
	char *binary;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	while (i <= len)
	{
		binary = char_to_binary_string(s[i]);
		j = 0;
		while (binary[j])
		{
			usleep(100);
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
	char *client_pid;

	if (argc != 3)
		return (-1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 100 && 99998 < server_pid)
		return (-1);
	client_pid = ft_itoa(getpid());
	printf("client pid : %s\n", client_pid);
	send_message_to_server(server_pid, client_pid);
	send_message_to_server(server_pid, argv[2]);

	free(client_pid);
	return (0);
}