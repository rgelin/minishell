#include "minishell.h"

static char	**create_cmd(t_exc command)
{
	char	**to_ret;
	int		i;

	i = 0;
	to_ret = (char **)malloc(sizeof(char *) * 4);
	if (!to_ret)
		return (NULL);
	to_ret[3] = NULL;
	if (command.cmd)
		to_ret[i++] = command.cmd;
	if (command.opt)
		to_ret[i++] = command.opt;
	if (command.arg)
		to_ret[i] = command.arg;
	while (i >= 0)
	{
		if (!to_ret[i--])
			return (NULL);
	}
	return (to_ret);
}

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
		exec = ft_strjoin(folder[i], "/");
		exec = ft_strjoin(exec, command.cmd);
		if (!exec)
		{
			ft_free(folder, ft_tabsize(folder));
			return (EXIT_FAILURE);
		}
		free(cmd[0]);
		cmd[0] = exec;
		find = execve(exec, cmd, NULL);
	}
	ft_free(folder, ft_tabsize(folder));
	if (exec)
		free(exec);
	ft_free(cmd, ft_tabsize(cmd));
	return (find);
}
