#include "../minishell.h"

static int	ft_create_all_exec(char ***folder, t_exc command)
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

static int	ft_free_exec(char **folder, char **cmd)
{
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	return (EXIT_FAILURE);
}

int	ft_try_exec(t_exc command, char **cmd, char **folder)
{
	int	i;

	i = -1;
	while (folder[++i])
		execve(folder[i], cmd, NULL);
	execve(command.cmd, cmd, NULL);
	ft_perror(command.cmd, NULL, "command not found");
	return (127);
}

static int	ft_exec(t_exc command, char **env)
{
	char	**folder;
	//int		i;
	char	**cmd;
	int		exit_code;

	cmd = create_cmd(command);
	if (!cmd)
		exit (EXIT_FAILURE);
	//i = -1;
	if (find_var_in_env("PATH", env) == -1)
	{
		ft_perror(command.cmd, NULL, "command not found");
		g_global.exit_code = 127;
		return (g_global.exit_code);
	}
	folder = ft_split(getenv(env[find_var_in_env("PATH", env)]), ':');
	if (!folder)
		return (ft_free_exec(folder, cmd));
	if (!ft_create_all_exec(&folder, command))
		exit (ft_free_exec(folder, cmd));
	exit_code = ft_try_exec(command, cmd, folder);
	ft_free_exec(folder, cmd);
	exit (exit_code);
}

int	execute(t_exc exc, char ***env)
{
	if (check_builtin(exc.cmd) != 0)
	{
		ft_execute_command(exc, env);
		return (g_global.exit_code);
	}
	else
		return (ft_exec(exc, *env));
}
