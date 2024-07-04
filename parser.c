/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:59:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/04 02:00:56 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    token_type(char *str)
{
    if (str[0] == '|')
        return (3);
    if (str[0] == '>' || str[0] == '<')
        return (2);
    return (1);
}
t_token *init_token(char **str,t_token **token)
{
    int i;
    t_token *tmp;
    

    i = 0;
    while (str[i] != NULL)
    {
        tmp = ft_dll_lstnew(str[i],token_type(str[i]));
        ft_dll_lstadd_back(token,tmp);
        i++;
    }
    return (*token);
    
}
void  init_graph(int graph[4][3])
{
    graph[0][0] = 1;
    graph[0][1] = 2;
    graph[0][2] = -1;
    graph[1][0] = 1;
    graph[1][1] = 2;
    graph[1][2] = 3;
    graph[2][0] = 1;
    graph[2][1] = -1;
    graph[2][2] = -1;
    graph[3][0] = 1;
    graph[3][1] = 2;
    graph[3][2] = -1;
}

int syntax_error(char **args)
{
    int graph[4][3];
    t_token *token;
    int state;
    
    token = NULL;
    state = 0;
    init_graph(graph);
    init_token(args,&token);
    while (token)
    {
        state = graph[state][token->type - 1];
        if (state == -1)
            return ( printf("syntax error\n"),1);
        token = token->next;
    }
    if (token == NULL && state == 1)
        return (0);
        
    return (printf("syntax error\n"),1);
}
