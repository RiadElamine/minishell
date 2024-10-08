/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:21:12 by relamine          #+#    #+#             */
/*   Updated: 2024/08/26 10:58:03 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_sign_and_whitespace(char **str, int *error_msg)
{
	int	signe;

	signe = 1;
	if (**str == '\0')
		return (*error_msg = -1);
	while ((**str >= 9 && **str <= 13) || **str == 32)
	{
		(*str)++;
		if (**str == '\0')
			return (*error_msg = -1);
	}
	if (**str == '-' || **str == '+')
	{
		if (*((*str)++) == '-')
			signe = -1;
		if (**str == '\0')
			return (*error_msg = -1);
	}
	return (signe);
}

static long	ft_atoi_checker(char *str, int *error_msg)
{
	int		signe;
	long	res;

	signe = parse_sign_and_whitespace(&str, error_msg);
	if (*error_msg == -1)
		return (*error_msg);
	res = 0;
	while (*str)
	{
		while ((*str >= 9 && *str <= 13) || *str == 32)
		{
			str++;
			if (*str == '\0')
				return (res * signe);
		}
		if (!ft_isdigit(*str))
			return (*error_msg = -1);
		if (res > MAXLONG || (res == MAXLONG && *str > '7' && signe == 1)
			|| (res == MAXLONG && *str > '8' && signe == -1))
			return (*error_msg = -2);
		res = res * 10 + (*(str++) - '0');
	}
	return (res * signe);
}

static int	print_exit_error(int error_msg, int checker, char *arg, t_norm n)
{
	int	argc;

	argc = n.bol;
	if (argc >= 2 && error_msg != -1 && error_msg != -2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if ((error_msg == -1 || error_msg == -2))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (ft_free(n.l_gc), ft_free(n.lst), exit(255), 1);
	}
	else
		return (ft_free(n.l_gc), ft_free(n.lst), exit(checker), 1);
}

static void	exit_no_arg(t_norm helper, char **env)
{
	int		status;
	t_env	*env_lst;
	char	*exit_s;

	env_lst = NULL;
	intit_env_list(&env_lst, env, helper.lst);
	exit_s = my_getenv("@exitstatus", env_lst);
	status = 0;
	if (g_a.exitstatus_singnal == 1)
	{
		status = 1;
		g_a.exitstatus_singnal = 0;
	}
	else if (exit_s)
		status = ft_atoi(exit_s);
	ft_free(helper.l_gc);
	ft_free(helper.lst);
	exit(status);
}

int	exit_0(char **argv, int *flag_pipe, t_norm n, char **env)
{
	long	checker;
	int		error_msg;

	n.bol = ft_strlen_double(argv + 1);
	if (*flag_pipe != 1)
		ft_putstr_fd("exit\n", 1);
	if (argv[1] != NULL)
	{
		error_msg = 0;
		checker = ft_atoi_checker(argv[1], &error_msg);
		if (print_exit_error(error_msg, checker, argv[1], n))
			return (1);
	}
	return (exit_no_arg(n, env), 0);
}
