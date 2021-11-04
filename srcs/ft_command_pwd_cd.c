
#include "minishell.h"

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
	
	getcwd(path, 1024); //voir pour la taille du buffer --> le chemin peut faire 6 octets max sinon getcwd renvoie null
	temp = ft_strjoin(path, "/"); //path est free dans le strjoin
	final_path = ft_strjoin(temp, cmd[1]);
	free(temp);
	temp = NULL;
	if (chdir(final_path) == -1)
		printf("cd: no such file or directory: %s\n", cmd[1]);
	free(final_path);
	final_path = NULL;
}

//a voir si on recoit d'office cd ou il peut y avoir cd..
void	ft_cd(char **cmd) // il y a un leak de plus a chaque commande
{
	char	*home;
	char	*path_from_home;
	
	home = getenv("HOME");
	if (cmd[1])
	{
		if (!ft_strncmp(cmd[1], "..", 3))
			chdir("..");
		else if (cmd[1][0] == '~' && !cmd[1][1])
			chdir(home);
		else if (cmd[1][0] == '~' && cmd[1][1] == '/')
		{
			path_from_home = ft_strtrim(cmd[1], "~");
			path_from_home = ft_strjoin(home, path_from_home); //modifier strjoin pcq on free s1 et ca casse un peu les couilles
			printf("%s\n", path_from_home);
			if (chdir(path_from_home) == -1)
				printf("cd: no such file or directory: %s\n", path_from_home);
			free(path_from_home);
			path_from_home = NULL;
		}
		else
			go_to_final_path(cmd);
	}
	else if (!ft_strncmp(cmd[0], "cd", 3))
		chdir(home);
	else
		return ;
}
