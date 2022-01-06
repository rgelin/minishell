/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:03:27 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/08 16:51:10 by jlong            ###   ########.fr       */
=======
/*   Updated: 2021/12/15 13:05:12 by jvander-         ###   ########.fr       */
>>>>>>> 39e4f50cbdccc263bc71400fcc7c837447357a8c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	size;

	i = 0;
	//sub_str = NULL;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub_str = (ft_calloc(sizeof(char), 1));
		if (sub_str == NULL)
			return (NULL);
		return (sub_str);
	}
	size = len;
	if (ft_strlen(s) < len)
		size = ft_strlen(s);
	sub_str = malloc(sizeof(char) * size + 1);
	if (sub_str == NULL)
		return (NULL);
	while (s[start] && i < len)
		sub_str[i++] = s[start++];
	sub_str[i] = '\0';
	return (sub_str);
}
