#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

typedef struct s_handler
{
	char* binary;
	int index;

} t_handler;

t_handler g_handler;

void init_server(void)
{
	printf("\n");
	printf("[minitalk server]\n");
	printf("server pid : %d\n", getpid());
	printf("\n");
}

int get_ascii_from_binary(void)
{
	int num;

	num = (g_handler.binary[0] - '0') * 1 
		+ (g_handler.binary[1] - '0') * 2
		+ (g_handler.binary[2] - '0') * 4
		+ (g_handler.binary[3] - '0') * 8
		+ (g_handler.binary[4] - '0') * 16
		+ (g_handler.binary[5] - '0') * 32
		+ (g_handler.binary[6] - '0') * 64
		+ (g_handler.binary[7] - '0') * 128;
	printf("%d ", num);
	return (num);
}

void handler_usr1(int signo)
{
	g_handler.binary[g_handler.index] = '0';
//	write(1, "0", 1);
	g_handler.index++;

	if (g_handler.index == 8)
	{
		g_handler.index = 0;
		write(1, g_handler.binary, 9);
		write(1, "\n", 1);
	}
}

void handler_usr2(int signo)
{
	g_handler.binary[g_handler.index] = '1';
//	write(1, "1", 1);
	g_handler.index++;
	
	if (g_handler.index == 8)
	{
		g_handler.index = 0;
		write(1, g_handler.binary, 9);
		write(1, "\n", 1);
	}
}


int main(void)
{
	init_server();
	g_handler.binary = (char *)malloc(sizeof(char) * 9);
	g_handler.binary[8] = '\0';
	g_handler.index = 0;

	signal(SIGUSR1, (void *)handler_usr1);
	signal(SIGUSR2, (void *)handler_usr2);
	while (1)
	{
		sleep(1);
	}
	return (0);
}