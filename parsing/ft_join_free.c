#include "../srcs/minishell.h"

char	*ft_strjoin_double_free(char *s1, char *s2)
{
	size_t	count;
	char	*new_str;

	if (s1 == NULL)
		s1 = ft_calloc(1, sizeof(char));
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	count = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[++count])
		new_str[count] = s1[count];
	count = -1;
	while (s2[++count])
		new_str[count + ft_strlen(s1)] = s2[count];
	new_str[count + ft_strlen(s1)] = '\0';
	free(s1);
	if (ft_strlen(s2) > 0)
		free(s2);
	return (new_str);
}
