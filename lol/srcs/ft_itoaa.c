#include "minishell.h"

static void		ft_rev_str(char *str, int size)
{
	int i;
	int j;

	i = 0;
	if (str[0] == '-')
	{
		if (size != 0)
		{
			while (i < size / 2)
			{
				j = str[i + 1];
				str[i + 1] = str[size - 1 - i];
				str[size - 1 - i++] = j;
			}
		}
	}
	if (size != 0)
	{
		while (i < size / 2)
		{
			j = str[i];
			str[i] = str[size - 1 - i];
			str[size - 1 - i++] = j;
		}
	}
}

static int		ft_diz(long nb)
{
	int n;
	int res;

	n = 1;
	res = 0;
	if (nb < 0)
	{
		res = 1;
		nb = -nb;
	}
	if (nb == 0)
		return (1);
	while ((nb / n) < 0)
		n = n / 10;
	while (nb / n > 0)
	{
		n = n * 10;
		res = res + 1;
	}
	return (res);
}

char			*ft_itoaa(int n)
{
	long	nb;
	char	*str;
	int		i;

	nb = n;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (ft_diz(nb) + 1))))
		return (0);
	ft_bzero(str, ft_diz(nb) + 1);
	if (nb < 0)
	{
		str[i++] = '-';
		nb = -1 * nb;
	}
	while (nb >= 10)
	{
		str[i++] = (nb % 10 + '0');
		nb = nb / 10;
	}
	str[i++] = (nb % 10 + '0');
	str[i++] = '\0';
	ft_rev_str(str, ft_strlenn(str));
	printf("itoa renvoie -%s-, %d\n", str, n);
	return (str);
}