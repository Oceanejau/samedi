
#include "minishell.h"

int	where_charly(char *str, int x, char c)
{
	while (str[x] != '\0')
	{
		if (str[x] == c)
			return (x);
		x++;
	}
	return (-1);
}