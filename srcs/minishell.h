#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h" 
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

/* a rendre pour un tableau avec cette structure
*	pour les exc
*/
typedef struct s_global
{
	pid_t	fork_pid;
	int		exit_code;
}	t_global;

t_global	g_global;

typedef struct s_exc
{
	char	*cmd;
	char	*opt;
	char	**arg;
	char	**input;
	char	**output;
	char	**heredoc; //{"cat", "ls", NULL}
	char	**redirect;
	char	**env_cpy;
}				t_exc;

/*structure pour le parsin qui sera free
*quand le tableau de t_exc sera parfait
*	char	**input;
	char	**output;
*/
typedef struct s_pars
{
	int		pipe;
	char	*command;
	char	**option;
	char	**arg;
	char	**redirect;
	char	*next_char;
}				t_pars;

typedef struct s_state
{
	char	*line;
	int		eof;
	int		n_of_pipe;
	int		*pipe;
	char	**cm;

}				t_state;

typedef struct s_quote
{
	int	simple_quote;
	int	double_quote;

}				t_quote;

typedef struct s_exp_list
{
	char				*line;
	struct s_exp_list	*next;
}	t_exp_list;

/*=========UTILS=========*/

int			ft_tabsize(char **tab);
int			ft_atoi_modified(const char *s);
int			ft_strchr_modified(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			size_list(t_exp_list *stack);
int			check_str_digit(char *str);
char		*ft_strtrim_modified(char const *s1, char const *set);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_get_last_input(t_exc cmd);
char		*ft_get_last_output(t_exc cmd);
void		ft_sort_string_tab(char **tab);
char		**create_cmd(t_exc command);
t_exp_list	*add_front(t_exp_list *stack, char *str);
t_exp_list	*add_back(t_exp_list *stack, char *str);
t_exp_list	*remove_back(t_exp_list *stack);
t_exp_list	*remove_front(t_exp_list *stack);
t_exp_list	*freelist(t_exp_list *stack);

/*=========SRCS=========*/

int			ft_execute_command(t_exc cmd, char ***env);
int			execute(t_exc exc, char ***env);
int			ft_create_all_redirect(t_exc *exc, int size);
long		get_lvl_shlvl(char ***env);
char		**cpy_env(char **env);
void		update_shlvl(char ***env);
void		ft_execute_pipe(t_exc *cmds, int nbr_pipe, char **env);
void		ft_redirect_input(t_exc cmd, int n_pipe, int *fds);
void		ft_redirect_output(t_exc cmd, int n_pipe, int *fds, int nbr_pipe);
void		ft_heredoc(char **heredoc);

/*=========PARSING=========*/

t_pars	*parsing(t_state *s);
t_pars	*split_line(t_state *line);
t_pars	*find_command(t_state *s);
int		ft_get_index(char *s);
int		ft_test(char *line);
int		ft_check_space(char *line);
int		check_redirection(char *line);
int		check_quote(char *line, int index);
int		*get_index(char *line, size_t size, char c);
int		*get_index(char *line, size_t size, char c);
void	init_tab(t_pars *tab);
void	ft_free_pars_tab(t_state *s);
void	ft_free_pars_error(t_state *s);
//void	ft_free_pars_tab(t_state *s);
char	*our_getenv(char *line, char **env);
char	**ft_split_parsing(char *s, char c);
char	**get_redirect(char *line);
char	**ft_arg(char **arg, char **env);
//char	**get_everything(char *line, char c);
t_exc	*last_parsing(t_pars *tab, char **env);
char	*ft_strjoin_double_free(char *s1, char *s2);
void	ft_free_tab_exc(t_exc *last_tab, t_pars *tab);
char	**get_opt(char *line);
char	**get_arg(char *line);

void	split_pipe(t_state *s);

/*=========ERROR=========*/

int			check_builtin(char *cmd);
void		ft_perror(char *cmd, char *arg, char *err_msg);

/*=========BUILTIN=========*/

void		ft_echo(t_exc exc);
void		ft_env(char **env);
void		ft_pwd(void);
void		ft_cd(t_exc exc, char ***env);
void		ft_export(t_exc exc, char ***env);
void		ft_unset(t_exc exc, char ***env);
void		ft_exit(t_exc exc);
void		create_new_var_env(char *arg, char ***env);
void		modify_var_in_env(char *arg, char ***env);
int			find_var_in_env(char *arg, char **env);
int			check_if_already_in_env(char *arg, char ***env);
char		**cpy_env(char **env);
char		**ft_realloc_env(char ***env, int size);
// void	ft_env(t_exc *exc);

/*=========READLINE=========*/

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
//void	rl_redisplay (void);
//int	rl_on_new_line (void);
//int	rl_on_new_line (void);

/*==========SIGNAL==========*/
void		ft_signal_msg(int exit_code);
void		ft_ctrl_c(int signal);
void		ft_ctrl_backslash(int signal);

#endif
