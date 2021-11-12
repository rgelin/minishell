
#include "minishell.h"

static char	**create_cmd(t_exc command)
{
	char	**to_ret;

	to_ret = (char **)malloc(sizeof(char *) * 4);
	if (!to_ret)
		return (NULL);
	to_ret[3] = NULL;

	if (command.cmd)
	{
		to_ret[0] = command.cmd;
		if (!to_ret)
			return (NULL);
		// printf("to_ret = %s\n", to_ret);
	}
	if (command.opt)
	{
		to_ret[1] = command.opt;
		if (!to_ret)
			return (NULL);
		// printf("to_ret = %s\n", to_ret);
	}
	if (command.arg)
	{
		to_ret[2] = command.arg;
		if (!to_ret)
			return (NULL);
		// printf("to_ret = %s\n", to_ret);
	}
	return (to_ret);
}

// /bin/mkdir = 0      plop = 1
int	ft_exec(t_exc command)
{
	char	**folder;
	int		find;
	char	*exec;
	int		i;
	char	**cmd;

	cmd = create_cmd(command);
	if (!cmd)
		return (EXIT_FAILURE);
	i = -1;
	find = 0;
	folder = ft_split(getenv("PATH"), ':');
	if (!folder)
		return (EXIT_FAILURE);
	while (folder[++i])
	{
		printf("folder i = %s\n", folder[i]);
		exec = ft_strjoin(folder[i], "/");
		exec = ft_strjoin(exec, command.cmd);
		if (!exec)
		{
			ft_free(folder, ft_tabsize(folder));
			return (EXIT_FAILURE);
		}
		
		find = execve(exec, cmd, NULL);
	}
	ft_free(folder, ft_tabsize(folder));
	if(exec)
		free(exec);
	if (cmd)
		free(cmd);
	return (find);
}