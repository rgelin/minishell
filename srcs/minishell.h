/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:40:08 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/02 16:45:25 by rgelin           ###   ########.fr       */
=======
/*   Updated: 2021/11/03 09:41:30 by jvander-         ###   ########.fr       */
>>>>>>> 38d9213437f46299650c86e9ae8bb2a66962612e
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "../libft/libft.h"
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

int		ft_tabsize(char **tab);
int		check_builtin(char *cmd);
int		ft_execute_command(char **cmd, char **env);
void	ft_echo(char **cmd);
void	ft_env(char **env);

void	ft_pwd(char **cmd);
void	ft_cd(char **cmd);

#endif