/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:33:56 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/12 11:33:57 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_heredoc(int sig_code)
{
	if (!g_global.fork_pid)
	{
		if (sig_code == SIGINT)
			exit(1);
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
		if (sig_code == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_set_signal(void)
{
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, ft_handler_heredoc);
}
