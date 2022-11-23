/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/23 18:41:35 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	char *current_dir;
	char *logname;
	int cmd_pipe[2];
	char *user_input;
	char *prompt_msg;
	
	char *hostname;
	int child_hostname;

	pipe(cmd_pipe);
	//Variable that will receive value from read
	hostname = malloc(100);
	//Returns the current directory (pwd) from terminal
	current_dir = getcwd(NULL, 0);
	printf("Current dir: %s\n", current_dir);
	
	//Need do this malloc dinamically
	logname = malloc(100);
	//Returns the value of a variable from environment
	logname = getenv("LOGNAME");
	printf("Logname: %s\n", logname);
	

	child_hostname = fork();
	if (child_hostname == 0)
		get_hostname(cmd_pipe);
	waitpid(child_hostname, NULL, 0);
	//Read the hostname from pipe and send to variable "hostname"
	read(cmd_pipe[0], hostname, 6);


	logname = ft_strjoin(logname, "@");
	prompt_msg = ft_strjoin(logname, hostname);
	//print a prompt message and waits for user input from terminal
	user_input = readline(prompt_msg);
	printf("Input from terminal: %s\n", user_input);
}

void	get_hostname(int *cmd_output)
{
	dup2(cmd_output[1], 1);
	execve("/bin/hostname", NULL, NULL);
}
