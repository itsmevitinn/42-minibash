/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:53:23 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/04 22:03:29 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin_cmd(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst **env_lst)
{
	if (!try_echo_execution(cmd))
		return (0);
	else if (!try_cd_execution(cmd, data, env_lst))
		return (0);
	else if (!try_pwd_execution(cmd))
		return (0);
	else if (!try_export_execution(cmd, data, env_lst))
		return (0);
	else if (!try_unset_execution(cmd, data, env_lst))
		return (0);
	else if (!try_env_execution(cmd, env_lst))
		return (0);
	else if (!try_exit_execution(cmd, data))
		return (0);
	return (1);
}

