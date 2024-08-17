/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:02:28 by relamine          #+#    #+#             */
/*   Updated: 2024/08/17 19:23:36 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
    {
		
		g_a.exitstatus_singnal = 1;
		if (g_a.stpsignal_inparent == 1)
			return;
		if (g_a.stphedorc_insgin == 1)
		{
			g_a.stphedorc_insgin = 2;
			close(0);
			return;
		}
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
