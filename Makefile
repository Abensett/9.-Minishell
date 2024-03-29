
# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

GREEN		= \033[32;1m
RED			= \033[31;1m
YELLOW		= \033[33;1m
CYAN		= \033[36;1m
RESET		= \033[0m
WHITE 		= \033[0;m

# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME			= minishell

DIRSRC			= src/

DIROBJ			= objs/

# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC				= gcc

CFLAGS 			=  -Wall -Wextra -Werror -g3

INCLUDES 		= -I ./includes -I /opt/homebrew/opt/readline/include

LDFLAGS			= -L/opt/homebrew/opt/readline/lib -lreadline libft/libft.a


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRC_FILES = arglist.c \
			quotes_handling.c \
			quotes_handling_2.c \
			expansion.c \
			space_handling.c \
			ft_env.c \
			ft_env_2.c \
			parsing.c \
			parsing_utils.c \
			valid.c \
			heredoc.c \
			exec_binary.c \
			executor.c \
			executor2.c \
			built-ins.c \
			built-ins_2.c \
			ft_error.c \
			non_interactive.c \
			signals.c \
			minishell.c \
			exit_clear.c \
			exit_clear2.c
OBJ := $(SRC_FILES:.c=.o)

SRC = $(addprefix ${DIRSRC}, $(SRC))

DIROBJS	= $(addprefix $(DIROBJ), $(OBJ))

# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #

all: header	$(NAME)

leaks : all
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=.ignore_readline --track-origins=yes ./minishell

$(DIROBJ)%.o:$(DIRSRC)%.c
			@mkdir -p $(DIROBJ)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(DIROBJS)
			@make  bonus --no-print-directory -C libft
			@make  --no-print-directory -C libft
			@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
			$(CC) $(CFLAGS) $(DIROBJS) $(INCLUDES)  $(LDFLAGS) -o $@
			@printf "\n[$(GREEN)OK$(WHITE)] $(NAME) generated 🐚\n"


clean:
			@make -C libft clean
			@rm -rf $(OBJS)	$(DIROBJ)
			@printf "\n[$(GREEN)cleaned$(WHITE)] .o FILES \n"

fclean:		clean
			@make -C libft fclean
			@rm -rf $(NAME)
			@printf "\n[$(GREEN)cleaned$(WHITE)] $(NAME) \n"

re:			fclean all

.PHONY: all clean fclean re

header :
	@printf "$(RED)"
	@printf "    __  ________   ___________ __  __________    __ \n"
	@printf "   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n"
	@printf "  / /|_/ // //  |/ // / \__ \/ /_/ / __/ / /   / /  \n"
	@printf " / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n"
	@printf "/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n"
	@printf "\n"
	@printf "MINISHELL COMPILATION\n"
	@printf "$(RESET)"

