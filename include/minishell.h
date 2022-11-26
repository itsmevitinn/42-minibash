#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct	s_prompt
{
	char *logname;
	char *hostname;
	char *current_dir;
	char *display;
}				t_prompt;

void	run_bin_cmd(char *command);
void	exec_bin_cmd(char **paths, char **arguments);
char	*display_prompt(void);

//SIGNAL_FUNCTIONS
void	setup_signals(void);

#endif
