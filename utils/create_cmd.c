#include "../srcs/minishell.h"

static char	*ft_join_arg(char **args)
{
	char	*to_ret;
	int		i;
	int		size;

	size = ft_tabsize(args);
	i = 0;
	while (i < size)
	{
		to_ret = ft_strjoin(to_ret, args[i]);
		if (!to_ret)
			exit(EXIT_FAILURE);
		if (i < size - 1)
		{
			to_ret = ft_strjoin(to_ret, " ");
			if (!to_ret)
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (to_ret);
}

char	**create_cmd(t_exc command)
{
	char	**to_ret;
	int		i;

	i = 0;
	to_ret = (char **)malloc(sizeof(char *) * 4);
	if (!to_ret)
		return (NULL);
	if (command.cmd)
		to_ret[i++] = command.cmd;
	if (command.opt)
		to_ret[i++] = command.opt;
	if (command.arg)
		to_ret[i++] = ft_join_arg(command.arg);
	to_ret[i] = NULL;
	while (--i >= 0)
	{
		if (!to_ret[i])
			return (NULL);
	}
	return (to_ret);
}
