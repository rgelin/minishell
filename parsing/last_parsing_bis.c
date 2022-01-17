/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parsing_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlong <jlong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:30:52 by jlong             #+#    #+#             */
/*   Updated: 2022/01/17 13:54:21 by jlong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*get_var_env_bis(char *tab_redirect, char **env, int i)
{
	t_tmp new;

	init_tmp(&new);
	new.tmp = ft_substr(tab_redirect, 0, i);
	new.rest = ft_substr(tab_redirect, i, (ft_strlen(tab_redirect) - i));
	new.var = ft_arg_bis(new.rest, env);
	new.new_line = ft_strjoin_double_free(new.tmp, new.var);
	free(tab_redirect);
	free(new.var);
	tab_redirect = NULL;
	return (new.new_line);
}
