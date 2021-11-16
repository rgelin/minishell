
#include "../minishell.h"

extern int	g_exit_code;

static void	set_PWD_and_OLDPWD(char	*path, char ***env)
{
	char	*old_pwd;
	char	*pwd;
	int		index_old;
	int		index_pwd;

	index_old = find_var_in_env("OLDPWD", *env);
	index_pwd = find_var_in_env("PWD", *env);
	old_pwd = ft_strtrim((*env)[index_pwd], "PWD=");
	old_pwd = ft_strjoin("OLDPWD=", old_pwd); //leak
	pwd = ft_strjoin("PWD=", path);


	free((*env)[index_pwd]);
	(*env)[index_pwd] = NULL;
	free((*env)[index_old]);
	(*env)[index_old] = NULL;


	// printf("\n\npwd: %s\n\n", pwd);
	// printf("\n\nold: %s\n\n", old_pwd);
	(*env)[index_pwd] = pwd;
	(*env)[index_old] = old_pwd;
}

static void	go_to_final_path(char **cmd, char ***env)
{
	char	*final_path;
	char	path[1024];
	char	*temp;
	
	getcwd(path, 1024); //voir pour la taille du buffer
	temp = ft_strjoin(path, "/");
	final_path = ft_strjoin(temp, cmd[1]);
	free(temp);
	temp = NULL;
	// if (access(final_path, X_OK) == -1 && errno == EACCES)
	// 	printf("cd: permission denied: %s\n", cmd[1]);
	// else if (access(final_path, F_OK) == -1)
	// 	printf("cd: no such file or directory: %s\n", cmd[1]);
	// else
	{
		if (chdir(final_path))
		{
			printf("cd: %s: %s\n", strerror(errno), cmd[1]);
			g_exit_code = 1;
		}
		else
			set_PWD_and_OLDPWD(final_path, env);
		printf("%d\n", g_exit_code);
	}
	free(final_path);
	final_path = NULL;
}

static void	go_path_from_home(char **cmd, char *home, char ***env)
{
	char	*path_from_home;

	path_from_home = ft_strtrim(cmd[1], "~");
	path_from_home = ft_strjoin(home, path_from_home);
	if (access(path_from_home, X_OK) == -1 && errno == EACCES)
		printf("cd: permission denied: %s\n", path_from_home);
	else if (access(path_from_home, F_OK) == -1)
		printf("cd: no such file or directory: %s\n", path_from_home);
	else
	{
		chdir(path_from_home);
		set_PWD_and_OLDPWD(path_from_home, env);
	}
	free(path_from_home);
	path_from_home = NULL;
}

//je prend comme hypothese que je recois "cd" dans le bon format(aucune erreur)
void	ft_cd(char **cmd, char ***env)
{
	char	*home;
	char	path[1024];
	
	home = getenv("HOME");
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "..", 3))
		{
			chdir("..");
			getcwd(path, 1024);
			set_PWD_and_OLDPWD(path, env);
		}
		else if (cmd[1][0] == '~' && !cmd[1][1])
		{
			chdir(home);
			set_PWD_and_OLDPWD(home, env);
		}
		else if (cmd[1][0] == '~' && cmd[1][1] == '/')
			go_path_from_home(cmd, home, env);
		else
			go_to_final_path(cmd, env);
	}
	else if (!ft_strncmp(cmd[0], "cd", 3))
	{
		chdir(home);
		set_PWD_and_OLDPWD(home, env);
	}
}
