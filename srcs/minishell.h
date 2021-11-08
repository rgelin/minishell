
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
	//int		pipe;
	char	*input;
	char	*output;
	char	*rdirect;
	char	**env_cpy;
}				t_exc;

//structure pour le parsin qui sera free
//quand le tableau de t_exc sera parfait

typedef struct s_pars
{
	char 	*command;
	char	*option;
	char	*arg;
	char	*input;
	char	*output;
	char	*rdirect;
	char	*next_char;
}				t_pars;

typedef struct s_state
{
	char *line;
	char **command;
	char **cm;
	int	n_of_sq;
	int *sq;
	int	n_of_dq;
	int *dq;
	int	n_of_pipe;
	int *pipe;
	int	n_of_dol;
	int *dol;
	int	n_of_opt;
	int	*opt;
	int	n_of_lchv;
	int	*lchv;
	int	n_of_rchv;
	int	*rchv;
	int	eof;
}				t_state;

int		ft_tabsize(char **tab);
int		check_builtin(char *cmd);
int		ft_execute_command(char **cmd, t_exc *exc);
void	ft_echo(char **cmd);
void	ft_env(t_exc *exc);
void	rl_replace_line (const char *text, int clear_undo);
int		rl_on_new_line (void);
void	rl_redisplay (void);
int		rl_on_new_line (void);
void	ft_pwd(char **cmd);
void	ft_cd(char **cmd);
t_exc	*ft_export(char **cmd, t_exc *exc);

//parsing
int		parsing(t_state *s);
void	split_line(t_state *line);
void	find_command(t_state *s);

#endif
