#include "../srcs/minishell.h"

int	ft_strchr_modified(const char *s, int c)
{
	char	*char_s;
	char	char_c;
	int		i;

	i = 0;
	if (s == NULL)
		return (-1);
	char_c = (char) c;
	char_s = (char *) s;
	while (char_s[i])
	{
		if (char_s[i] == char_c)
			return (i);
		i++;
	}
	if (c == '\0' && char_s[i] == '\0')
		return (i);
	return (-1);
}
