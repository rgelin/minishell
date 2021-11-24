
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
	char	**arg;
	//int		pipe;
	char	**input;
	char	**output;
	char	**redirect;
	char	**env_cpy;
}				t_exc;

//structure pour le parsin qui sera free
//quand le tableau de t_exc sera parfait

typedef struct s_pars
{
	int		pipe;
	char 	*command;
	char	**option;
	char	**arg;
	char	**redirect;
	//char	**input;
	//char	**output;
	char	*next_char;
}				t_pars;

typedef struct s_state
{
	char *line;
	int	eof;
	int	n_of_pipe;
	int	*pipe;
	char **cm;

}				t_state;

typedef	struct	s_exp_list
{
	char				*line;
	struct	s_exp_list	*next;
}				t_exp_list;


int		ft_tabsize(char **tab);
int		check_builtin(char *cmd);
int		ft_execute_command(t_exc cmd, char ***env);
void	ft_echo(t_exc exc);
// void	ft_env(t_exc *exc);
void	rl_replace_line (const char *text, int clear_undo);

int		ft_atoi_modified(const char *s);
// int		rl_on_new_line (void);
// void	rl_redisplay (void);
// int		rl_on_new_line (void);
void	rl_clear_history (void);
int		ft_exec(t_exc command);

void	ft_env(char **env);
int		ft_strchr_modified(const char *s, int c);

void	ft_pwd();
void	ft_cd(t_exc exc, char ***env);

void	ft_export(t_exc exc, char ***env);
char	**ft_realloc_env(char ***env, int size);
char	*ft_strtrim_modified(char const *s1, char const *set);
char	*ft_strjoin_free(char const *s1, char const *s2);
int		find_var_in_env(char *arg, char **env);
int		check_if_already_in_env(char *arg, char ***env);
void	modify_var_in_env(char *arg, char ***env);
int		ft_strcmp(char *s1, char *s2);

void	ft_perror(char *cmd, char *arg, char *err_msg);

void	ft_unset(t_exc exc, char ***env);

char	**cpy_env(char **env);
void	ft_sort_string_tab(char **tab);

t_exp_list	*add_front(t_exp_list *stack, char *str);
t_exp_list	*add_back(t_exp_list *stack, char *str);
t_exp_list	*remove_back(t_exp_list *stack);
t_exp_list	*remove_front(t_exp_list *stack);
t_exp_list	*freelist(t_exp_list *stack);
int			size_list(t_exp_list *stack);
char	**create_cmd(t_exc command);

//parsing
t_pars	*parsing(t_state *s);
t_pars	*split_line(t_state *line);
int		*get_index(char *line, size_t size, char c);
t_pars	*find_command(t_state *s);
int		ft_get_index(char *s);
int		ft_get_index_opt(char *s, char c, int i);
int		ft_test(char *line);
int		ft_check_space(char *line);
int		*get_index(char *line, size_t size, char c);
int		check_redirection(char *line);
void	init_tab(t_pars *tab);
//char	**get_everything(char *line, char c);
int		check_quote(char *line, int	index);
//void	ft_free_pars_tab(t_state *s);
char	**ft_split_parsing(char *s, char c);
void	ft_free_pars_tab(t_state *s);
void	ft_free_pars_error(t_state *s);
t_exc 	*last_parsing(t_pars *tab);
char 	**get_redirect(char *line, char c);
char	**ft_arg(char **arg);

#endif
