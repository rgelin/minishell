
#include "../minishell.h"

static void	set_pwd_and_oldpwd(char	*path, char *old_path, char ***env)
{
	char	*old_pwd;
	char	*pwd;
	int		index_old;
	int		index_pwd;

	index_old = find_var_in_env("OLDPWD", *env);
	index_pwd = find_var_in_env("PWD", *env);
	pwd = ft_strjoin("PWD=", path);
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	if (index_pwd != -1)
	{
		free((*env)[index_pwd]);
		(*env)[index_pwd] = NULL;
		(*env)[index_pwd] = pwd;
	}
	if (index_old != -1)
	{
		free((*env)[index_old]);
		(*env)[index_old] = NULL;
		(*env)[index_old] = old_pwd;
	}

}

static void	go_to_final_path(char *arg, char ***env, char *old_path)
{
	char	*final_path;
	char	path[1024];
	char	*temp;
	
	getcwd(path, 1024);
	temp = ft_strjoin(path, "/");
	final_path = ft_strjoin(temp, arg);
	free(temp);
	temp = NULL;
	if (chdir(final_path))
	{
		ft_perror("cd", arg, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(final_path, old_path, env);
	free(final_path);
	final_path = NULL;
}

static void	go_path_from_home(char *arg, char *home, char ***env, char *old_path)
{
	char	*path_from_home;
	char	*temp;

	temp = ft_strtrim(arg, "~");
	path_from_home = ft_strjoin(home, temp);
	free(temp);
	temp = NULL;
	if (chdir(path_from_home))
	{
		ft_perror("cd", path_from_home, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(path_from_home, old_path, env);
	free(path_from_home);
	path_from_home = NULL;
}

void	go_to_home(char ***env, char *old_path)
{
	char	*home;

	home = getenv("HOME");
	if (chdir(home))
	{
		ft_perror("cd", home, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(home, old_path, env);
}

void	go_previous(char *arg, char *old_path, char ***env)
{
	char	path[1024];

	if (chdir("..") || !getcwd(path, 1024))
	{
		ft_perror("cd", arg, strerror(errno));
		g_global.exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(path, old_path, env);
}

void	ft_cd(t_exc exc, char ***env)
{
	char	old_path[1024];

	g_global.exit_code = 0;
	getcwd(old_path, 1024);
	if (exc.arg != NULL)
	{
		if (!ft_strncmp(exc.arg[0], "..", 3))
			go_previous(exc.arg[0], old_path, env);
		else if (exc.arg[0][0] == '~' && !exc.arg[0][1])
			go_to_home(env, old_path);
		else if (exc.arg[0][0] == '~' && exc.arg[0][1] == '/')
			go_path_from_home(exc.arg[0], getenv("HOME"), env, old_path);
		else
			go_to_final_path(exc.arg[0], env, old_path);
	}
	else
		go_to_home(env, old_path);
}
