/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:25 by abou              #+#    #+#             */
/*   Updated: 2022/04/09 10:27:57 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>


/*LISTE CHAINEES BLOCK = FUNCTIONS+OPTION+ARG */

typedef struct s_all_commands   
{
		char	**cmd; 
		struct	s_all_commands *next;
}               t_all_commands;
/*Donne le nombre d'arguments + 1 car nom fonction + args */
typedef struct  s_cmd_details     
{
		int			nb_arguments;       
		char 		**av;
}  t_cmd_details;
/* struture de tout*/
typedef struct s_minishell        
{
		char *prompt;      
		int	 number_cmd;    
		t_cmd_details *cmd;

} t_minishell;   


#endif