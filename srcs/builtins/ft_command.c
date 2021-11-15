
#include "../minishell.h"

static void	ft_print_line(char **cmd, int i)
{
	char	*str_trim;

	while (cmd[i])
	{
		str_trim = ft_strtrim(cmd[i], "\"");
		printf("%s", str_trim);
		if (cmd[i + 1])
			printf(" ");
		i++;
		free(str_trim);
	}
}

void	ft_echo(char **cmd)
{
	if (ft_tabsize(cmd) < 2)
		return ;
	if (!ft_strncmp(cmd[1], "-n", 2))
		ft_print_line(cmd, 2);
	else
	{
		ft_print_line(cmd, 1);
		printf("\n");
	}
}

/*
*	print all the environment variables.
*	
*	@params : the environment tab to print
*	
*
*	printf("number of variables = %i\n", i); to use for debug
*/
void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (i < ft_tabsize(env))
	{
		if (ft_strchr_modified(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
