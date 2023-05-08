/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/08 20:20:11 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

void	parse_line(char **line)
{
	t_cmd	*cmd;

	cmd = NULL;
	complete_line(line);
	// printf("[%s]\n", line);
	if (line && *line)
		cmd = tokenize_line(*line);
	cd(cmd);
	if (cmd)
		free_line(cmd);
}
