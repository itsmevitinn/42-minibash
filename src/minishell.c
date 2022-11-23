/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:04:21 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/23 17:09:05 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	char *current_dir;
	char *logname;
	char *user_input;

	//Returns the current directory (pwd) from terminal
	current_dir = getcwd(NULL, 0);
	printf("Current dir: %s\n", current_dir);
	
	//Need do this malloc dinamically
	logname = malloc(100);
	//Returns the value of a variable from environment
	logname = getenv("LOGNAME");
	printf("Logname: %s\n", logname);

	//print a prompt message and waits for user input from terminal 
	user_input = readline(getenv("LOGNAME"));
	printf("Input from terminal: %s\n", user_input);
}
