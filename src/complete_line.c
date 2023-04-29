/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:52:14 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/29 09:13:13 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_until_chr(char *line, char c)
{
	char	*dquote;
	int		quote_pos;

	while (1337)
	{
		if (c == '\'')
			dquote = readline("quote> ");
		else
			dquote = readline("dquote> ");
		if (!dquote)
		{
			free (line);
			ft_putendl_fd("unexpected EOF while looking for matching \"\'", 2);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			return (NULL);
		}
		line = ft_strjoin_free(line, ft_strdup("\n"));
		line = ft_strjoin_free(line, dquote);
		quote_pos = ft_chrpos(line, c);
		if (quote_pos != -1)
			break ;
	}
	return (line);
}

static int	only_spaces_left(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

void	get_is_complete(char *line, int *quote, int *dquote, int *operator)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !(*quote))
			(*dquote) = !(*dquote);
		if (line[i] == '\'' && !(*dquote))
			(*quote) = !(*quote);
		if (!line[i + 1] || only_spaces_left(line + i + 1))
		{
			if (i - 2 >= 0)
			{
				if ((!ft_isspace(line[i - 2]) && line[i - 1] == '&' && line[i] == '&')
				|| (!ft_isspace(line[i - 2]) && line[i - 1] == '|' && line[i] == '|'))
					*operator = 1;
			}
			if (i - 1 >= 0)
			{
				if (line[i] == '|' || (line[i - 1] == '&' && line[i] == '&') || (line[i - 1] == '|' && line[i] == '|'))
					*operator = 1;
			}
		}
		i++;
	}
} 

void	complete_line(char **line)
{
	int		quote;
	int		dquote;
	int		operator;
	char	*tmp;

	quote = 0;
	operator = 0;
	dquote = 0;
	if (!line || !*line)
		return ;
	get_is_complete(*line, &quote, &dquote, &operator);
	if (dquote)
		*line = read_until_chr(ft_strdup(*line), '\"');
	else if (quote)
		*line = read_until_chr(ft_strdup(*line), '\'');
	else if (operator)
	{
		tmp = readline("> ");
		*line = ft_strjoin_free(*line, tmp);
	}
	else
		return ;
	complete_line(line);
}