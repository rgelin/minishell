/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:14:06 by rgelin            #+#    #+#             */
/*   Updated: 2021/11/10 14:51:49 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

t_exp_list	*add_front(t_exp_list *stack, char *str)
{
	t_exp_list	*element;

	element = malloc(sizeof(t_exp_list));
	if (!element)
		exit(EXIT_FAILURE);
	element->line = str;
	element->next = stack;
	return (element);
}

t_exp_list	*add_back(t_exp_list *stack, char *str)
{
	t_exp_list	*element;
	t_exp_list	*temp;

	element = malloc(sizeof(t_exp_list));
	if (!element)
		exit(EXIT_FAILURE);
	element->line = str;
	element->next = NULL;
	if (!stack)
		return (element);
	temp = stack;
	while (temp->next)
		temp = temp->next;
	temp->next = element;
	return (stack);
}

t_exp_list	*remove_back(t_exp_list *stack)
{
	t_exp_list	*temp;
	t_exp_list	*save;

	if (!stack)
		return (NULL);
	if (stack->next == NULL)
	{
		free(stack);
		stack = NULL;
		return (NULL);
	}
	temp = stack;
	save = stack;
	while (temp->next)
	{
		save = temp;
		temp = temp->next;
	}
	save->next = NULL;
	free(temp);
	temp = NULL;
	return (stack);
}

t_exp_list	*remove_front(t_exp_list *stack)
{
	t_exp_list	*new_list;

	if (!stack)
		return (stack);
	new_list = stack;
	stack = stack->next;
	free (new_list);
	new_list = NULL;
	return (stack);
}

t_exp_list	*freelist(t_exp_list *stack)
{
	t_exp_list	*temp;

	if (!stack)
		return (NULL);
	while (stack)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
	free(stack);
	stack = NULL;
	return (stack);
}
