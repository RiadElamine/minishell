/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:17:27 by relamine          #+#    #+#             */
/*   Updated: 2024/08/19 06:20:25 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **env, t_gc **lst, int bol)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if ((ft_strcmp(get_key(env[i], lst), "PATH") == 0 && bol == 1)
			|| !ft_strncmp(env[i], "@exitstatus", 11)
			|| !ft_strncmp(env[i], "@path_of_program", 16)
			|| !ft_strncmp(env[i], "@hidden_PATH", 12))
		{
			i++;
			continue ;
		}
		if ((!ft_strchr(env[i], '=') && get_value(env[i], lst) == NULL))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
