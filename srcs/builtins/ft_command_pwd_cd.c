
#include "../minishell.h"

void	ft_pwd(char **cmd)
{
	char	pwd[1024]; //redefinir la taille en mode bien

	if (cmd[1]) //pour l'instant protecion comme ca mais a voir avec les pipes pour plusieurs arguments
	{
		write (2, "pwd: too many arguments\n", 24); //faire une fonction de gestion d'erreur (avec perror je pense)
		return ;
	}
	printf("%s\n", getcwd(pwd, 1024));
}

static void	go_to_final_path(char **cmd)
{
	char	*final_path;
	char	path[1024];
	char	*temp;
	
	getcwd(path, 1024); //voir pour la taille du buffer
	temp = ft_strjoin(path, "/");
	final_path = ft_strjoin(temp, cmd[1]);
	free(temp);
	temp = NULL;
	if (access(final_path, X_OK) == -1 && errno == EACCES)
		printf("cd: permission denied: %s\n", cmd[1]);
	else if (access(final_path, F_OK) == -1)
		printf("cd: no such file or directory: %s\n", cmd[1]);
	else
		chdir(final_path);
	free(final_path);
	final_path = NULL;
}

static void	go_path_from_home(char **cmd, char *home)
{
	char	*path_from_home;

	path_from_home = ft_strtrim(cmd[1], "~");
	path_from_home = ft_strjoin(home, path_from_home);
	if (access(path_from_home, X_OK) == -1 && errno == EACCES)
		printf("cd: permission denied: %s\n", path_from_home);
	else if (access(path_from_home, F_OK) == -1)
		printf("cd: no such file or directory: %s\n", path_from_home);
	else
		chdir(path_from_home);
	free(path_from_home);
	path_from_home = NULL;
}

//je prend comme hypothese que je recois "cd" dans le bon format(aucune erreur)
void	ft_cd(char **cmd)
{
	char	*home;
	
	home = getenv("HOME");
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "..", 3))
			chdir("..");
		else if (cmd[1][0] == '~' && !cmd[1][1])
			chdir(home);
		else if (cmd[1][0] == '~' && cmd[1][1] == '/')
			go_path_from_home(cmd, home);
		else
			go_to_final_path(cmd);
	}
	else if (!ft_strncmp(cmd[0], "cd", 3))
		chdir(home);
}
