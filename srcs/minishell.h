
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

// a rendre pour un tableau avec cette structure
// pour les exc
typedef struct s_exc
{
	char	*cmd;
	char	*opt;
	char	*arg;
	int		pipe;
	char	*input;
	char	*output;
	char	*rdirect;
	char	**env_cpy;
}				t_exc;

//structure pour le parsin qui sera free
//quand le tableau de t_exc sera parfait
/*
typedef struct s_pars
{
	char *command;
	char *option;
	char **arg;
	char *input;
	char *output;
	char *next_char;
}				t_pars;
*/
typedef struct s_state
{
	char *line;
	char **command;
	char *username;
	int	*sq;
	int *dq;
}				t_state;

int		ft_tabsize(char **tab);
int		check_builtin(char *cmd);
int		ft_execute_command(char **cmd, t_exc *exc);
void	ft_echo(char **cmd);
void	ft_env(char **env);

void	ft_pwd(char **cmd);
void	ft_cd(char **cmd);
void	ft_export(char **cmd, t_exc *exc);

//parsing
void	check_quote(t_state *state);
#endif
