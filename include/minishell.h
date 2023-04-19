#ifndef MINISHELL_H
#define MINISHELL_H

# include "/Users/aahlyel/homebrew/opt/readline/include/readline/readline.h"
# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include  <stdlib.h>
# include  <fcntl.h>
# include  <string.h>


typedef enum allo
{
	infile,
	outfile,
	errorfile,
}	t_alo;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	short	pipe:1;
	short	here_doc:1;
	int 	infile;
	int		outfile;
	int		errorfile;
}	t_cmd;

typedef struct s_line
{
	char			**line;
	char			*operator;
	short			is_operator:1;
	struct s_line	*next;
}	t_line;

typedef struct s_tree
{
	char			*data;
	short			is_left:1;
	short			is_root:1;
	short			is_right:1;
	struct s_tree	*prev;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

# include "parsing.h"


#endif