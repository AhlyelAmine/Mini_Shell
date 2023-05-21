/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_controll.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:25:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/21 22:54:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*arguments_constructor(t_arguments *arguments, char *str, unsigned short type)
{
	t_arguments	*new;
	t_arguments	*tmp;


	new = malloc(sizeof(t_arguments));
	if (!new)
		return (NULL);
	new->str = NULL;
	if (type != DQUOTE && type != QUOTE)
		new->str = str;
	new->type = type;
	new->next = NULL;
	new->down = NULL;
	if (type == DQUOTE || type == QUOTE)
		new->down = arguments_constructor(new->down, str, IS_STR | type);
	if (!arguments)
		return (new);
	tmp = arguments;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (arguments);
}

void	arguments_destructor(t_arguments **arguments)
{
	t_arguments	*tmp;
	t_arguments	*head;

	tmp = *arguments;
	head = *arguments;
	while (head)
	{
		if (head->type & IS_STR || head->type & IS_VARIABLE)
		{
			tmp = head;
			head = head->next;
			free (tmp->str);
			free (tmp);
		}
		else if (head->type & DQUOTE || head->type & QUOTE)
		{
			tmp = head;
			head = head->next;
			arguments_destructor(&tmp->down);
			free(tmp);
		}
	}
	*arguments = NULL;
}

t_arguments	*str_to_arguments(char *str)
{
	char		**splited;
	t_arguments	*arguments;

	arguments = NULL;
	return (arguments);
}

void	replace_arg(t_arguments **head, t_arguments *old, t_arguments *new)
{
	t_arguments	*tmp;
	t_arguments	*prev;

	if (!new)
		return ;
	if (*head == old)
	{
		tmp = (*head)->next;
		*head = new;
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->next == old)
		{
			tmp->next = new;
			while (new->next)
				new = new->next;
			new->next = old->next;
		}
		tmp = tmp->next;
	}
}

void	arguments_add_back(t_arguments **head, t_arguments *new)
{
	t_arguments	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}