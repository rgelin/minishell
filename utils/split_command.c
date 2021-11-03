
#include "../srcs/minishell.h"

char	**split_command(char *line)
{
	char	**command;

	command = ft_split(line, ' ');
	if (!command)
		return (NULL);
	if (!ft_strncmp(command[0], "cd", 2))
		return (ft_free(command, ft_tabsize(command)));
	return (command);
}
