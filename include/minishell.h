#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct	s_prompt
{
	char *logname;
	char *hostname;
	char *current_dir;
	char *display;
}				t_prompt;

void	get_prompt_msg(t_prompt *prompt_msg);
void	get_hostname(t_prompt *prompt_msg);
void	get_current_dir(t_prompt *prompt_msg);
void	build_prompt_msg(t_prompt *prompt_msg);
void	run_bin_cmd(char *command);
void	exec_bin_cmd(char **paths, char **arguments);

//SIGNAL_FUNCTIONS
void	setup_signals(struct sigaction *sa);

#endif
