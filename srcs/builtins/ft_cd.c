
#include "../minishell.h"

extern int	g_exit_code;

static void	set_pwd_and_oldpwd(char	*path, char ***env) //segfault dans le cas ou on unset PWD
{
	(void)path;
	(void)env;
	char	*old_pwd;
	char	*pwd;
	int		index_old;
	int		index_pwd;

	index_old = find_var_in_env("OLDPWD", *env);
	index_pwd = find_var_in_env("PWD", *env);
	pwd = ft_strtrim((*env)[index_pwd], "PWD=");
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	pwd = NULL;
	pwd = ft_strjoin("PWD=", path);
	// free((*env)[index_pwd]);
	// (*env)[index_pwd] = NULL;
	free((*env)[index_old]);
	(*env)[index_old] = NULL;
	(*env)[index_pwd] = pwd;
	(*env)[index_old] = old_pwd;
}

static void	go_to_final_path(char *arg, char ***env)
{
	char	*final_path;
	char	path[1024];
	char	*temp;
	
	getcwd(path, 1024); //voir pour la taille du buffer
	temp = ft_strjoin(path, "/");
	final_path = ft_strjoin(temp, arg);
	free(temp);
	temp = NULL;
	if (chdir(final_path))
	{
		ft_perror("cd", arg, strerror(errno));
		g_exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(final_path, env);
	free(final_path);
	final_path = NULL;
}

static void	go_path_from_home(char *arg, char *home, char ***env)
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
		g_exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(path_from_home, env);
	free(path_from_home);
	path_from_home = NULL;
}

void	go_to_home(char ***env)
{
	char	*home;

	home = getenv("HOME");
	if (chdir(home))
	{
		ft_perror("cd", home, strerror(errno));
		g_exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(home, env);
}
//je prend comme hypothese que je recois "cd" dans le bon format(aucune erreur)

void	ft_cd(t_exc exc, char ***env)
{
	char	path[1024];

	g_exit_code = 0;
	if (exc.arg != NULL)
	{
		if (!ft_strncmp(exc.arg[0], "..", 3))
		{
			if (chdir("..") || !getcwd(path, 1024))
			{
				ft_perror("cd", exc.arg[0], strerror(errno));
				g_exit_code = 1;
			}
			else
				set_pwd_and_oldpwd(path, env);
		}
		else if (exc.arg[0][0] == '~' && !exc.arg[0][1])
			go_to_home(env);
		else if (exc.arg[0][0] == '~' && exc.arg[0][1] == '/')
			go_path_from_home(exc.arg[0], getenv("HOME"), env);
		else
			go_to_final_path(exc.arg[0], env);
	}
	else
		go_to_home(env);
}
