#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct	s_prompt
{
	char *logname;
	char *hostname;
	char *pwd;
	char *final_msg;
}				t_prompt;

void	get_prompt_dir(t_prompt *prompt_msg);
void	get_prompt_msg(t_prompt *prompt_msg);
void	get_hostname(int *cmd_output);

#endif
