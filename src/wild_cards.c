/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:49:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 14:15:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int			compare_matches(char *realfile, char *myfile);
static int			skip_unkown(char *realfile, char *myfile);
static t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory);

static t_arguments	*open_cwd(char *str)
{
	DIR				*directory;
	struct dirent	*dir;
	t_arguments		*files;

	files = NULL;
	directory = opendir(".");
	files = get_files(str, files, directory);
	closedir(directory);
	return (files);
}

void	wild_cards(t_arguments **args)
{
	t_arguments	*files;
	char		*tmp;

	if (!*args)
		return ;
	if (((*args)->type & IS_STR) && ft_strchr((*args)->str, '*'))
	{
		tmp = (*args)->str;
		files = open_cwd((*args)->str);
		if (files)
		{
			replace_arg(args, args, files);
			free (tmp);
		}
	}
	else
		wild_cards(&(*args)->next);
}

static int	skip_unkown(char *myfile, char *realfile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (myfile[i] == '*')
		i++;
	if (!myfile[i])
		while (realfile[j])
			j++;
	else
		while (myfile[i] && realfile[j] && realfile[j] != myfile[i])
			j++;
	if (myfile[i] && realfile[j] && realfile[j] == myfile[i])
		return (compare_matches(myfile + i, realfile + j));
	else if (!myfile[i] && !realfile[j])
		return (1);
	else
		return (0);
}

static int	compare_matches(char *myfile, char *realfile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (myfile[i] && realfile[j] && myfile[i] == realfile[j])
	{
		i++;
		j++;
	}
	if (myfile[i] == '*')
		return (skip_unkown(myfile + i, realfile + j));
	else if (!myfile[i] && !realfile[j])
		return (1);
	else
		return (0);
}

t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory)
{
	struct dirent	*dir;
	int				i;

	i = 0;
	dir = readdir(directory);
	if (!dir)
		return (args);
	if (*str != '.' && *dir->d_name == '.')
	{
		args = get_files(str, args, directory);
		return (args);
	}
	if (ft_strncmp(dir->d_name, ".", 2) && ft_strncmp(dir->d_name, "..", 3))
	{
		if (compare_matches(str, dir->d_name))
			args = arguments_constructor(args, \
			ft_strdup(dir->d_name), IS_STR | IS_FILE, 0);
	}
	args = get_files(str, args, directory);
	return (args);
}
