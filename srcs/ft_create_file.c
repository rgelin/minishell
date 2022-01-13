/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:30:45 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/13 16:06:47 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exit_create_file(char *file_name)
{
	g_global.exit_code = EXIT_FAILURE;
	if (file_name)
		free(file_name);
	return (g_global.exit_code);
}

static int	ft_create_file(char *name)
{
	char	*file_name;
	int		fd;

	file_name = ft_strdup(name);
	if (!file_name)
	{
		perror("malloc");
		return (ft_exit_create_file(file_name));
	}
	fd = open(file_name, O_CREAT, 0644);
	if (fd == -1)
	{
		ft_perror("open", file_name, "Impossible to open file");
		return (ft_exit_create_file(file_name));
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (ft_exit_create_file(file_name));
	}
	return (ft_exit_create_file(file_name));
}

static int	ft_create_redirect(t_exc exc)
{
	char	*current;
	int		i;

	i = 0;
	if (!exc.redirect || !ft_tabsize(exc.redirect))
		return (-2);
	current = exc.redirect[i];
	while (current)
	{
		if (ft_strncmp(current, ">>", 2) == 0)
			g_global.exit_code = ft_create_file(current + 2);
		else if (ft_strncmp(current, ">", 1) == 0)
			g_global.exit_code = ft_create_file(current + 1);
		if (g_global.exit_code == 1)
			return (1);
		current = exc.redirect[++i];
	}
	return (EXIT_SUCCESS);
}

void	ft_create_all_redirect(t_exc *exc, int size)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (!ret && i <= size)
	{
		ret = ft_create_redirect(exc[i]);
		i++;
	}
	(void)ret;
}
