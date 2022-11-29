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

//PROMPT FUNCTIONS
char	*display_prompt(void);

//PARSER FUNCTIONS
void	parse_cmd(char *command);

//EXEC FUNCTIONS
void	exec_bin_cmd(char *right_path, char **splitted_cmd);

//BULT-IN FUNCTIONS
void	isbuiltin(char *command);

//SIGNAL_FUNCTIONS
void	setup_signals(void);

extern int g_running_process;

#endif
