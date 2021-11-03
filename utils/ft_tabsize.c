
#include "../srcs/minishell.h"

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}
