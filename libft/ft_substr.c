/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:03:27 by jvander-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/06 15:01:06 by rgelin           ###   ########.fr       */
=======
/*   Updated: 2022/01/11 14:55:21 by jvander-         ###   ########.fr       */
>>>>>>> 2494621c22fbf943b2d5d02bfcdb77dff409227c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	size;

	i = 0;
	sub_str = NULL;
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
	sub_str = malloc(sizeof(char) * (size + 1));
	if (sub_str == NULL)
		return (NULL);
	while (s[start] && i < len)
		sub_str[i++] = s[start++];
	sub_str[i] = '\0';
	return (sub_str);
}
