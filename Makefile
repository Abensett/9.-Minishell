
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

CFLAGS 			= -Wall -Wextra -Werror -g

INCLUDES 		= -I ./includes -I /opt/homebrew/opt/readline/include 

LDFLAGS			= -L/opt/homebrew/opt/readline/lib -lreadline libft/libft.a 


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRC_FILES = built-ins.c \
			built-ins_2.c \
			exec_binary.c \
			executor.c \
			ft_env.c \
			ft_env_2.c \
			minishell.c


OBJ := $(SRC_FILES:.c=.o)

SRC = $(addprefix ${DIRSRC}, $(SRC))

DIROBJS	= $(addprefix $(DIROBJ), $(OBJ))

# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #


all: header	$(NAME)

$(DIROBJ)%.o:$(DIRSRC)%.c
			@mkdir -p $(DIROBJ)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(DIROBJS)
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

