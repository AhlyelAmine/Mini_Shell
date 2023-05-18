/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:26:35 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/18 21:48:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_selected_parenthesis(char *line, int i, int j, int k)
{
	char	*tmp;

	j++;
	while (line[i + j] && ft_isspace(line[i + j]))
		j++;
	if (!line[i + j] && k > i)
	{
		tmp = line;
		line = remove_unused_parenthesis(ft_substr(line, i, k - i));
		free(tmp);
	}
	return (line);
}

void	set_zero_var(t_var *var)
{
	var->dquote = 0;
	var->quote = 0;
}

char	*select_unused_parenthesis(char *line, int i, t_var var, int is_open)
{
	int		j;
	int		is_closed;
	int		k;

	k = 0;
	is_closed = 0;
	j = -1;
	while (line[i + ++j])
	{
		check_out_of_quotes(line[i + j], &var);
		if (line[i + j] == '(' && !var.quote && !var.dquote)
			is_open++;
		else if (line[i + j] == ')' && !var.quote && !var.dquote)
		{
			is_closed++;
			k = i + j;
		}
		if (is_open == is_closed)
		{
			line = remove_selected_parenthesis(line, i, j, k);
			break ;
		}
	}
	return (line);
}
int	has_syntax_error(char *line, int i)
{
	int	pipe;
	int	redir;

	pipe = 0;
	redir = 0;
	while (i)
	{
		if (line[i - 1] == '|')
			pipe = 1;
		else if (line[i - 1] == '<')
			redir = 1;
		i--;
	}
	return (pipe | redir);
}
char	*remove_parenthisis_syntax_checker(char *line)
{
	char	*err;
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(' && i && !has_syntax_error(line, i))
		{
			err = ft_substr(line, 0, i);
			return (free(line), pr_custom_err(ERR_SNTX, err, err), NULL);
		}
		i++;
	}
	return (line);
}
char	*remove_unused_parenthesis(char *line)
{
	int		i;
	int		is_open;
	int		is_closed;
	t_var	var;
	char	*err;

	set_zero_var(&var);
	i = 0;
	is_open = 0;
	is_closed = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && line[i] == '(')
	{
		is_open++;
		i++;
	}
	if (is_open)
		line = select_unused_parenthesis(line, i, var, is_open);
	else	// need update
		return (remove_parenthisis_syntax_checker(line));
	// 	while (line[i])
	// 	{
	// 		if (line[i] == '(')
	// 		{
	// 			err = ft_substr(line, 0, i);
	// 			return (pr_custom_err(ERR_CMD, err, err), NULL);
	// 		}
	// 		i++;
	// 	}
	return (line);
}

t_cmd	*tokenize_line(char *line)
{
	line = remove_unused_parenthesis(ft_strdup(line));
	return (get_token_parenthesis_and(line));
}
int	count_it(int *j, int *i, int word)
{
	if (*j)
		word++;
	*i += *j;
	*j = 0;
	return (word);
}

