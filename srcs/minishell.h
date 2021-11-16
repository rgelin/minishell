
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

# include <errno.h>
# include <string.h>

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

typedef	struct	s_exp_list
{
	char				*line;
	struct	s_exp_list	*next;
}				t_exp_list;


int		ft_tabsize(char **tab);
int		check_builtin(char *cmd);
int		ft_execute_command(char **cmd, char ***env);
void	ft_echo(char **cmd);
// void	ft_env(t_exc *exc);
void	rl_replace_line (const char *text, int clear_undo);
// int		rl_on_new_line (void);
// void	rl_redisplay (void);
// int		rl_on_new_line (void);
void	rl_clear_history (void);
int		ft_exec(t_exc command);

void	ft_env(char **env);
int		ft_strchr_modified(const char *s, int c);

void	ft_pwd(char **cmd);
void	ft_cd(char **cmd, char ***env);

void	ft_export(char **cmd, char ***env);
char	**ft_realloc_env(char ***env, int size);
char	*ft_strtrim_modified(char const *s1, char const *set);
int		find_var_in_env(char *arg, char **env);
int		check_if_already_in_env(char *arg, char ***env);
void	modify_var_in_env(char *arg, char ***env);

void	ft_unset(char **cmd, char ***env);

char	**cpy_env(char **env);
void	ft_sort_string_tab(char **tab);

t_exp_list	*add_front(t_exp_list *stack, char *str);
t_exp_list	*add_back(t_exp_list *stack, char *str);
t_exp_list	*remove_back(t_exp_list *stack);
t_exp_list	*remove_front(t_exp_list *stack);
t_exp_list	*freelist(t_exp_list *stack);
int			size_list(t_exp_list *stack);

//parsing
void	check_quote(t_state *state);
#endif
