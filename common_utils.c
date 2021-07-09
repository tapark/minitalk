#include "minitalk.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' ||
			str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] != '\0' && '0' <= str[i] && str[i] <= '9')
	{
		result = result * 10;
		result = result + str[i] - '0';
		i++;
	}
	result = result * sign;
	return (result);
}

int		get_len(int n)
{
	int len;

	len = 0;
	if (n <= 0)
		len = len + 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;
	size_t	av;
	int		i;

	len = get_len(n);
	i = 1;
	if (n < 0)
		av = (long)n * -1;
	else
		av = (long)n;
	if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	while (len - i != -1)
	{
		dest[len - i] = av % 10 + '0';
		av = av / 10;
		i++;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}