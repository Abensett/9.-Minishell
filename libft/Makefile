#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makesrc/file                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abensett <marvin@42.src/fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 13:38:46 by abensett          #+#    #+#              #
#    Updated: 2021/06/10 11:30:38 by abensett         ###   ########.src/fr        #
#                                                                              #
# **************************************************************************** #

GREEN   = \033[1;32m
WHITE   = \033[0;m

NAME = libft.a

SRC = src/ft_abs.c \
	src/ft_atol.c \
	src/ft_atoll.c \
	src/ft_atoi.c \
	src/ft_bzero.c \
	src/ft_calloc.c \
	src/ft_double_abs.c \
	src/ft_double_pow.c\
	src/ft_isalnum.c \
	src/ft_isstr_alnum.c \
	src/ft_isstr_num.c \
	src/ft_isdigit.c \
	src/ft_isalpha.c \
	src/ft_isascii.c \
	src/ft_isprint.c \
	src/ft_itoa.c \
	src/ft_memccpy.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_memcpy.c \
	src/ft_memmove.c\
	src/ft_memset.c \
	src/ft_min.c \
	src/ft_putchar_fd.c\
	src/ft_putendl_fd.c \
	src/ft_putnbr_fd.c \
	src/ft_putstr_fd.c \
	src/ft_split.c \
	src/ft_str_add.c \
	src/ft_str_delete.c \
	src/ft_strjoin.c \
	src/ft_strtrim.c \
	src/ft_strmapi.c \
	src/ft_strchr.c \
	src/ft_strdup.c \
	src/ft_strlcat.c \
	src/ft_strlcpy.c \
	src/ft_strlen.c \
	src/ft_strncmp.c \
	src/ft_strnstr.c \
	src/ft_strrchr.c \
	src/ft_substr.c \
	src/ft_tab_long_print.c \
	src/ft_tab_int_print.c \
	src/ft_tab_long_sort.c \
	src/ft_tab_str_print.c \
	src/ft_tolower.c \
	src/ft_toupper.c \


SRCBONUS = src/ft_lstnew.c \
	  src/ft_lstsize.c \
	  src/ft_lstlast.c \
	  src/ft_lstadd_back.c \
	  src/ft_lstadd_front.c \
	  src/ft_lstdelone.c \
	  src/ft_lstclear.c \
	  src/ft_lstiter.c \
	  src/ft_lstfree.c \
	  src/ft_lstmap.c \
	  src/ft_lst_int_print.c \
	  src/ft_lst_int_search.c \
	  src/ft_lst_int_search_index.c \
	  src/ft_lst_int_occurence.c \
	  src/ft_lst_int_check_order.c \
	  src/ft_lst_get_median.c \
	  src/ft_lst_long_check_order.c \
	  src/ft_lst_long_fill.c \
	  src/ft_lst_str_print.c \


OBJS = 		$(SRC:.c=.o)

OBJSBONUS = $(SRCBONUS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rc $(NAME) $(OBJS)
			@printf "\n[$(GREEN)OK$(WHITE)] $(NAME)📙 generated \n"

bonus:		$(OBJSBONUS)
			@ar rc $(NAME) $(OBJSBONUS)
			@printf "\n[$(GREEN)OK$(WHITE)] $(NAME)📙🅱  generated \n"
.c.o:
			@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
			@gcc -Wall -Wextra -Werror -I ./ -c $< -o $(<:.c=.o)
			@printf "\n[$(GREEN)OK$(WHITE)] $(<) generated \n"
clean:
			@rm -rf $(OBJS)	$(OBJSBONUS)
			@printf "\n[$(GREEN)cleaned$(WHITE)] .o src/FILES \n"

fclean:		clean
			@rm -rf $(NAME)
			@printf "\n[$(GREEN)cleaned$(WHITE)] $(NAME) \n"

re:			fclean all

.PHONY: all clean fclean re
