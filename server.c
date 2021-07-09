#include "minitalk.h"

t_handler g_handler;

void init_server(void)
{
	printf("\n");
	printf("[minitalk server]\n");
	printf("server pid : %d\n", getpid());
	printf("\n");
}

char get_char_from_binary(void)
{
	char c;

	c = (g_handler.binary[0] - '0') * 128
		+ (g_handler.binary[1] - '0') * 64
		+ (g_handler.binary[2] - '0') * 32
		+ (g_handler.binary[3] - '0') * 16
		+ (g_handler.binary[4] - '0') * 8
		+ (g_handler.binary[5] - '0') * 4
		+ (g_handler.binary[6] - '0') * 2
		+ (g_handler.binary[7] - '0') * 1;
	return (c);
}

void wirte_character(void)
{
	char c;

	if (g_handler.index == 8)
	{
		g_handler.index = 0;
		c = get_char_from_binary();
		if (c == '\0')
		{
			g_handler.end_count++;
			if (g_handler.end_count == 1)
				write(1, " > ", 3);
			if (g_handler.end_count == 2)
			{
				write(1, "\n", 1);
				g_handler.end_count = 0;
				g_handler.is_client_pid = 1;
			}
		}
		else
			write(1, &c, 1);
	}
}

void handler_usr(int signo)
{
	char c;

	if (signo == SIGUSR1)
	{
		g_handler.binary[g_handler.index] = '0';
		g_handler.index++;
		wirte_character();
	}
	else
	{
		g_handler.binary[g_handler.index] = '1';
		g_handler.index++;
		wirte_character();
	}
}

int main(void)
{
	init_server();
	g_handler.binary = (char *)malloc(sizeof(char) * 9);
	g_handler.binary[8] = '\0';
	g_handler.index = 0;
	g_handler.end_count = 0;
	g_handler.is_client_pid = 1;
	signal(SIGUSR1, (void *)handler_usr);
	signal(SIGUSR2, (void *)handler_usr);
	while (42)
	{
		sleep(42);
	}
	return (0);
}