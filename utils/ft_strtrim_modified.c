#include "../srcs/minishell.h"

static int	in_charset(char c, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_new_length(char const *s1, char const *set)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s1[++i])
	{
		if (!in_charset(s1[i], set))
			count++;
	}
	return (count);
}

char		*ft_strtrim_modified(char const *s1, char const *set) //leak
{
	int		i;
	int		index;
	char	*res;

	i = -1;
	index = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_new_length(s1, set) + 1));
	if (!res)
		exit(EXIT_FAILURE);
	while (s1[++i])
	{
		if (!in_charset(s1[i], set))
			res[index++] = s1[i];
	}
	res[index] = '\0';
	return (res);
}
