/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:06:18 by vsergio           #+#    #+#             */
/*   Updated: 2023/01/09 11:06:40 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increment_shlvl(t_var_lst *env)
{
	char	*new_content;
	int		shlvl;

	shlvl = ft_atoi(get_content("SHLVL", env));
	shlvl++;
	new_content = ft_itoa(shlvl);
	change_content("SHLVL", new_content, env);
}
