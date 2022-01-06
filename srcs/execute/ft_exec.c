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

static int	ft_free_exec(char **folder, char **cmd, int exit_code)
{
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	g_global.exit_code = exit_code;
	return (exit_code);
}

int	ft_try_exec(t_exc command, char **cmd, char **folder)
{
	int	exit_code;
	int	i;

	i = -1;
	while (folder[++i])
		exit_code = execve(folder[i], cmd, NULL);
	if (exit_code == -1)
		exit_code = execve(command.cmd, cmd, NULL);
	if (i == ft_tabsize(folder))
	{
		ft_perror(command.cmd, NULL, "command not found");
		g_global.exit_code = 127;
	}
	else
		g_global.exit_code = exit_code;
	return (g_global.exit_code);
}

static int	ft_exec(t_exc command, char **env)
{
	char	**folder;
	int		i;
	char	**cmd;

	cmd = create_cmd(command);
	if (!cmd)
		return (EXIT_FAILURE);
	i = -1;
	if (find_var_in_env("PATH", env) == -1)
	{
		ft_perror(command.cmd, NULL, "command not found");
		g_global.exit_code = 127;
		exit(g_global.exit_code);
	}
	folder = ft_split(getenv(env[find_var_in_env("PATH", env)]), ':');
	if (!folder)
<<<<<<< HEAD
		exit (EXIT_FAILURE);
	if (!folder || !ft_create_all_exec(&folder, command))
	{
		ft_free(folder, ft_tabsize(folder));
		ft_free(cmd, ft_tabsize(cmd));
		exit (EXIT_FAILURE);
	}
	exit_code = execve(command.cmd, cmd, NULL);
	if (exit_code == 0)
	{
		ft_free(folder, ft_tabsize(folder));
		ft_free(cmd, ft_tabsize(cmd));
		exit(EXIT_SUCCESS);
	}
	while (folder[++i])
		exit_code = execve(folder[i], cmd, NULL);
	if (i == ft_tabsize(folder))
	{
		ft_perror(command.cmd, NULL, "command not found");
		exit_code = 127;
		exit(exit_code);
	}
	ft_free(folder, ft_tabsize(folder));
	ft_free(cmd, ft_tabsize(cmd));
	exit (exit_code);
=======
	{
		g_global.exit_code = EXIT_FAILURE;
		exit (g_global.exit_code);
	}
	if (!ft_create_all_exec(&folder, command))
		exit (ft_free_exec(folder, cmd, EXIT_FAILURE));
	ft_try_exec(command, cmd, folder);
	return (ft_free_exec(folder, cmd, g_global.exit_code));
>>>>>>> 39e4f50cbdccc263bc71400fcc7c837447357a8c
}

int	execute(t_exc exc, char ***env)
{
	if (check_builtin(exc.cmd) != 0)
	{
		ft_execute_command(exc, env);
		exit (g_global.exit_code);
	}
	else
		exit (ft_exec(exc, *env));
}
