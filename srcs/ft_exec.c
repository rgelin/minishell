#include "minishell.h"

static char	**create_cmd(t_exc command)
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
	//if (command.arg)
	//	to_ret[i++] = command.arg;
	to_ret[i] = NULL;
	while (--i >= 0)
	{
		if (!to_ret[i])
			return (NULL);
	}
	return (to_ret);
}

int	ft_create_all_exec(char ***folder, t_exc command)
{
	int	i;

	i = 0;
	if (!(*folder))
		return (0);
	while ((*folder)[i])
	{
		(*folder)[i] = ft_strjoin((*folder)[i], "/");
		if (!(*folder)[i])
			return (0);
		(*folder)[i] = ft_strjoin((*folder)[i], command.cmd);
		if (!(*folder)[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_exec(t_exc command)
{
	char	**folder;
	int		i;
	char	**cmd;

	cmd = create_cmd(command);
	if (!cmd)
		return (EXIT_FAILURE);
	i = -1;
	folder = ft_split(getenv("PATH"), ':');
	if (!folder)
		return (EXIT_FAILURE);
	if (!ft_create_all_exec(&folder, command))
	{
		ft_free(folder, ft_tabsize(folder));
		ft_free(cmd, ft_tabsize(cmd));
		return (EXIT_FAILURE);
	}
	while (folder[++i])
		execve(folder[i], cmd, NULL);
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	return (EXIT_SUCCESS);
}
