/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:30:08 by jvander-          #+#    #+#             */
/*   Updated: 2021/11/22 00:43:38 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	count;
	char	*new_str;

	if (s1 == NULL)
		s1 = ft_calloc(1, sizeof(char));
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	count = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[count])
	{
		new_str[count] = s1[count];
		count++;
	}
	count = 0;
	while (s2 && s2[count])
	{
		new_str[count + ft_strlen(s1)] = s2[count];
		count++;
	}
	new_str[count + ft_strlen(s1)] = '\0';
	free((char *)s1);
	return (new_str);
}
