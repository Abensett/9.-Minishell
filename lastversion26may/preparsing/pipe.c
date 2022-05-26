/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:50:31 by shamizi           #+#    #+#             */
/*   Updated: 2022/04/24 16:48:06 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


/*
   suite du travail de la modification du split :
   pour commencer meme chose que pour les guillemet mais avec single quote
   faire un if / else en fonction du premier caractere trouvé pour compenser les regles des dites quote
   ensuite trouvé un moyen de transformé un $arg dans un double quote

   théorie plausible, si le 1er caractere est un " passer une valeur dans la structure a 1 et donc changer la case ou on trouve un $ par son argument correspondant
   si le 1er caractere est un ' écrire le dollar normal vu qu'il perd sa signification


   idée de la structure :
   {
   int doublequote = 0 ou 1 si cette case est une double quote
   int singlequote même chose (pour cas particulier si ou il y a un $)
   si on est dans un de ses cas echo "cat | ls -l" on éxécute pas la commande entre guillemet, du coup attention quand je split les pipes pour créer les différent argument de pas séparé si le PIPE est entre guillement simple ou double

   utiliser le même split qu'en dessous mais le modifier encore une fois; flemme de ouf pour l'instant 
   }

 */


static char	**freestrings2(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int	nb_mot2(char *s, char c)
{
	int		i;
	int		j;
	int		compt;

	i = 0;
	j = 0;
	compt = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (s[i] == c)
			j = 0;
		else if (j == 0)
		{
			j = 1;
			compt++;
		}
		i++;
	}
	return (compt);
}

static int	len_word2(char *s, char c, int i)
{
	int		len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\"')
		{
			i++;
			len++;
			while (s[i] && s[i] != '\"')
			{
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	**affect2(char *s, char **tab, char c, int l)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(sizeof(char) * (len_word2(s, c, i) + 1));
		if (tab[j] == NULL)
			return (freestrings2(tab));

		while (s[i] && s[i] != c)
		{
			if (s[i] == '\"')
			{
				tab[j][k++] = s[i++];
				while (s[i] && s[i] != '\"')
					tab[j][k++] = s[i++];
				tab[j][k++] = s[i++];
			}
			else
				tab[j][k++] = s[i++];
		}
		tab[j][k] = '\0';
		j++;
	}
	/*	while (s[i] != c && s[i] != '\"' && s[i])
		tab[j][k++] = s[i++];
		if (s[i] == '\"')
		{
		tab[j][k++] = s[i++];
		while (s[i] && s[i] != '\"')
		tab[j][k++] = s[i++];
		tab[j][k++] = s[i++];
		}

		while (s[i] && s[i] != c)
		tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
		}*/

tab[j] = 0;
return (tab);
}

char	**ft_split2(char *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = nb_mot2(s, c);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (0);
	return (affect2(s, tab, c, i));
}

//avec ce test d'execve il faut bien que j'enleve les double/single quote dans l'exec
//ne pas oublier la gestion du dollar ->entre double cote transformer dollar machin par ce qu'il faut
//pour les redirections voir si il y en a après le pipe

/*

   ma piste pour demain split les pipes -> vers cmd
   ensuite split les espace vers cmd.arg
   ensuite split les redirections / plusieur redirection sont possible ex > outfile > infile met le resultat dans les deux

 */

int	ft_strlen(char *str)
{
	int i =0;
	while (str[i])
		i++;
	return i;
}

void	initarg(t_arg *arg)
{
	arg->argu = NULL;
	arg->next = NULL;
	arg->prev = NULL;
}

void	initcmd(t_cmd *cmd)
{
	cmd->com = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->arg = NULL;
}

// je vérifie avec un split si il va y avoir des séparation
// si c'est le cas j'ajoute des maillon a ma liste chainé, je garde encore les "" et les $ comme ils sont
void	checkargu(t_cmd *cmd)
{
	char **tmp;
	int i;

	while (cmd)
	{
		i = 0;		
		tmp = ft_split2(cmd->com, ' ');
		if(tmp)
		{
			while (tmp[i])
			{
				cmd->arg = argadd(cmd->arg, tmp[i], i);
				i++;
			}
		}
		cmd = cmd->next;
	}
}



int main(int argc, char **argv, char **env)
{
	t_cmd cmd;
	char **tmp;
	int i = 0;

	char *test1 = "< infile echo \"bon|jour\"-n \"bien ou |quoi aymen ?|\" > outfile| grep \"bonjour la street\" -rza";
	char *test3 = NULL;
	char *test4 = "la|la|la[lalalala";
	char *test5 = "touch              b";
	initcmd(&cmd);
	tmp = ft_split2(test5, '|');
	if(tmp)
	{
		cmd.com = tmp[0];
		while (tmp[i])
		{
			cmd = *listadd(&cmd, tmp[i], i);
			i++;
		}
	}
	checkargu(&cmd);
	print_list(&cmd);
	return 0;
}
