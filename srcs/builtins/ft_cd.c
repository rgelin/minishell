
#include "../minishell.h"

extern int	g_exit_code;

static void	set_pwd_and_oldpwd(char	*path, char ***env)
{
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
	free((*env)[index_pwd]);
	(*env)[index_pwd] = NULL;
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
		printf("minishell: cd: %s: %s\n", arg, strerror(errno));
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
		printf("minishell: cd: %s: %s\n", path_from_home, strerror(errno));
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
		printf("minishell: cd: %s: %s\n", home, strerror(errno));
		g_exit_code = 1;
	}
	else
		set_pwd_and_oldpwd(home, env);
}
//je prend comme hypothese que je recois "cd" dans le bon format(aucune erreur)
void	ft_cd(char **cmd, char ***env)
{
	char	path[1024];
	char	*arg;

	g_exit_code = 0;
	arg = cmd[1];
	if (arg)
	{
		if (!ft_strncmp(arg, "..", 3))
		{
			if (chdir("..") || !getcwd(path, 1024))
			{
				printf("minishell: cd: %s: %s\n", arg, strerror(errno));
				g_exit_code = 1;
			}
			else
				set_pwd_and_oldpwd(path, env);
		}
		else if (arg[0] == '~' && !arg[1])
			go_to_home(env);
		else if (arg[0] == '~' && arg[1] == '/')
			go_path_from_home(arg, getenv("HOME"), env);
		else
			go_to_final_path(arg, env);
	}
	else
		go_to_home(env);
}
