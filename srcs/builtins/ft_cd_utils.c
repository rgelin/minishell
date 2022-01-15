/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:23:32 by jvander-          #+#    #+#             */
/*   Updated: 2022/01/15 14:05:26 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwd_and_oldpwd(char	*path, char *old_path, char ***env)
{
	char	*old_pwd;
	char	*pwd;
	int		index_old;
	int		index_pwd;

	index_old = find_var_in_env("OLDPWD", *env);
	index_pwd = find_var_in_env("PWD", *env);
	pwd = ft_strjoin("PWD=", path);
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	if (index_pwd != -1)
	{
		free((*env)[index_pwd]);
		(*env)[index_pwd] = NULL;
		(*env)[index_pwd] = pwd;
	}
	if (index_old != -1)
	{
		free((*env)[index_old]);
		(*env)[index_old] = NULL;
		(*env)[index_old] = old_pwd;
	}
}
