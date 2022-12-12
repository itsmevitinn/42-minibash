/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:54:31 by Vitor             #+#    #+#             */
/*   Updated: 2022/12/11 23:40:17 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int oldpwd(t_var_lst *env);
static int relative_or_absolute(char *path);
static void update_oldpwd(char *current_dir, t_var_lst *env);
static char *get_content(char *name, t_var_lst *env);

void cd(char **splitted_cmd, t_var_lst *env)
{
	char *current_dir;
	char *path;

	current_dir = getcwd(NULL, 0);
	path = splitted_cmd[1];

	if (!path)
		chdir(get_content("HOME", env));
	else if (*path == '-' && ft_strlen(path) == 1)
	{
		if (!oldpwd(env))
			return ;
	}
	else if (!relative_or_absolute(path))
		return ;
	update_oldpwd(current_dir, env);
	exit_status = 0;
}

static int oldpwd(t_var_lst *env)
{
	if (is_env("OLDPWD", env))
	{
		chdir(get_content("OLDPWD", env));
		printf("%s\n", get_content("OLDPWD", env));
	}
	else if (!is_env("OLDPWD", env))
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		exit_status = 1;
		return (0);
	}
	return (1);
}

static int relative_or_absolute(char *path)
{
	char *error_msg;

	if (chdir(path) == -1)
	{
		error_msg = strerror(2);
		printf("bash: cd: %s: %s\n", path, error_msg);
		exit_status = 1;
		return (0);
	}
	return (1);
}

static void update_oldpwd(char *current_dir, t_var_lst *env)
{
	if (is_env("OLDPWD", env))
		change_content("OLDPWD", current_dir, env);
	else
		ft_varadd_back(&env, ft_var_new("OLDPWD", current_dir));
}

static char *get_content(char *name, t_var_lst *env)
{
	int name_len;

	name_len = ft_strlen(name);
	while (env && ft_strncmp(name, env->name, name_len + 1))
		env = env->next;
	if (env)
		return (env->content);
	return (NULL);
}