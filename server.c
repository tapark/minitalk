#include "minitalk.h"

char get_char_from_binary(char *binary)
{
	char c;

	c = (binary[0] - '0') * 128
		+ (binary[1] - '0') * 64
		+ (binary[2] - '0') * 32
		+ (binary[3] - '0') * 16
		+ (binary[4] - '0') * 8
		+ (binary[5] - '0') * 4
		+ (binary[6] - '0') * 2
		+ (binary[7] - '0') * 1;
	return (c);
}

void wirte_character(char *binary)
{
	static char buffer[101];
	char c;
	static int i;
	static int end_count;
	static int client_pid;

	c = get_char_from_binary(binary);
	buffer[i++] = c;
	if (c == '\0' || i == 100)
	{
		if (i == 100)
			buffer[i] = '\0';
		if (c == '\0')
			end_count++;
		write(1, buffer, ft_strlen(buffer));
		if (end_count == 1)
		{
			client_pid = ft_atoi(buffer);
			write(1, " > ", 3);
		}
		if (end_count == 2)
		{
			write(1, "\n", 1);
			printf("Receive Massage : %d ms\n\n", get_current_time());
			end_count = 0;
		}
		i = 0;
	}
}

void handler_usr(int signo)
{
	static char binary[9];
	static int i;

	if (signo == SIGUSR1)
		binary[i++] = '0';
	else
		binary[i++] = '1';
	if (i == 8)
	{
		binary[8] = '\0';
		wirte_character(binary);
		i = 0;
	}
}

int main(void)
{
	printf("\n[minitalk server]\n");
	printf("server pid : %d\n\n", getpid());
	signal(SIGUSR1, (void *)handler_usr);
	signal(SIGUSR2, (void *)handler_usr);
	while (42)
	{
		sleep(42);
	}
	return (0);
}