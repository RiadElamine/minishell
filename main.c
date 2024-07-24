/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/24 20:06:15 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


void readline_loop(char **line, t_gc **lst, char **env) 
{
    t_token *token_lst;
    char **token;
    t_env *env_lst;
    t_gc *l_gc;
    t_cmd *cmd;
	char **shelvl;
	int bol = 0;
	char **exitstatus;
	char **tmp_env;
	int stexit;
	int flag_pipe;
    
    l_gc = NULL;
	stexit = -9999;
    token_lst = NULL;
    env_lst = NULL;
    cmd = NULL;
    token = NULL;
	exitstatus = NULL;
	tmp_env = NULL;

	shelvl = NULL;
	if (*env == NULL)
	{
		*env = ft_malloc(sizeof(char *) * 2, lst);
		env[0] = NULL;
		export_pwd(&env, &l_gc, lst);
	
		ft_export_anything("SHLVL=1", &l_gc, lst, &env);
		ft_export_anything("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin", &l_gc, lst, &env);
		ft_export_anything("_=/Users/relamine/Desktop/minishell/./minishell", &l_gc, lst, &env);
		bol = 1;
	}

	tmp_env = env;
	int g = 0;
	while (tmp_env != NULL && tmp_env[g])
	{
		if(ft_strcmp(tmp_env[g], "exitstatus") != 0 && tmp_env[g + 1] == NULL)
			export_status(0, &env, &l_gc, lst);
		g++;
	}
    // printf("--argv[i]: %d\n", *line);
    while (1) {
		flag_pipe = 0;
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(g_a.exitstatus_singnal);
        }
		if (g_a.exitstatus_singnal == 1)
		{
			export_status(g_a.exitstatus_singnal, &env, &l_gc, lst);
			g_a.exitstatus_singnal = 0;
		}
    	intit_env_list(&env_lst, env, lst);
        if (*line[0] != '\0')
		{
			add_history(*line);
			
			// sp_uq_handling(*line);
			token = ft_tokinize(*line, &l_gc);
			syntax_error(token, &token_lst, &l_gc);
			env_handling(&token_lst, env_lst, &l_gc);
			her_doc_handling(&token_lst, &l_gc);
			init_cmd(&cmd, token_lst, &l_gc);
			open_redirection(&cmd, &l_gc);
			// for (t_cmd *tmp = cmd; tmp; tmp = tmp->next) 
			// {
			// 	printf("cmd: %s\n", tmp->cmd);
			// 	printf("red_in: %s\n", tmp->red_in);
			// 	printf("red_out: %s\n", tmp->red_out);
			// 	for (int i = 0; tmp->args[i]; i++) 
			// 	{
			// 		printf("args[%d]: %s\n", i, tmp->args[i]);
			// 	}
			// }
			// ft_lstlast(cmd)->next = NULL;
			t_cmd *tmp = cmd;
			while (tmp && tmp->cmd)
			{
				if (tmp->next)
					flag_pipe = 1;
				if (!flag_pipe)
					ft_export_(tmp->args, &env, &l_gc, lst);
				else
					ft_export_anything("_=", &l_gc, lst, &env);
				stexit = ft_builtin_func(tmp->args, &env, &l_gc,lst, &bol);
				if (stexit != -9999)
					export_status(stexit, &env, &l_gc, lst);
				tmp = tmp->next;
			}

			free(*line);
			*line = NULL;
			ft_free(&l_gc);
			cmd = NULL;
			token_lst = NULL;
			env_lst = NULL;
			token = NULL;
		}
    }
}

void f() {
    system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
    t_gc *lst;
    char *line;
	// atexit(f);
	lst = NULL;
    if (ac != 1)
        return (printf("Usage: %s\n", av[0]),1);
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);
    ft_free(&lst);
    return 0;
}

