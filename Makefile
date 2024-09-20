
PROTACTION = protaction/protaction.c protaction/freememory.c \
			protaction/checkglobal.c

EXPANDING = expanding/expanding.c expanding/expanding_utils.c  expanding/expanding_variable.c \
			expanding/expanding_split.c 

UTILS = utils/utils_file.c utils/function_utils.c utils/utils_fils.c \
		utils/function_utils_s.c utils/list_utils.c utils/quots_utils.c

LIB = 	lib/list.c lib/split_commandline.c lib/signal.c \
		lib/ft_count.c  lib/split_pipline.c 

BUILTINS =	builtins/cd_builtin.c builtins/echo_builtin.c builtins/export_builtin.c \
			builtins/unset_builtin.c builtinUtils/builtin_utils_1.c builtinUtils/builtin_utils_2.c \
			builtinUtils/builtin_utils_3.c \
			builtins/exit_builtin.c builtinUtils/builtin_utils_4.c

EXECUTION = execution/execution.c execution/errors.c executionUtils/execution_utils_3.c \
			execution/make_envlst.c executionUtils/execution_utils_1.c execution/redirecting.c \
			executionUtils/execution_utils_2.c execution/heredoc.c execution/make_prompt.c \
			executionUtils/execution_utils_4.c executionUtils/execution_utils_5.c \
			executionUtils/execution_utils_6.c

LIBFT_SRCS = ./libft/ft_lstnew_bonus.c ./libft/ft_lstadd_front_bonus.c ./libft/ft_lstsize_bonus.c ./libft/ft_lstlast_bonus.c \
			./libft/ft_lstadd_back_bonus.c ./libft/ft_lstdelone_bonus.c ./libft/ft_lstclear_bonus.c \
			./libft/ft_lstiter_bonus.c ./libft/ft_lstmap_bonus.c ./libft/ft_putnbr_fd.c ./libft/ft_strcat.c \
            ./libft/ft_isalpha.c ./libft/ft_isdigit.c ./libft/ft_isalnum.c ./libft/ft_isascii.c \
            ./libft/ft_isprint.c ./libft/ft_strlen.c ./libft/ft_memset.c ./libft/ft_bzero.c \
            ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_strlcpy.c ./libft/ft_strlcat.c \
            ./libft/ft_calloc.c ./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_putendl_fd.c \
            ./libft/ft_strchr.c ./libft/ft_strncmp.c ./libft/ft_memchr.c ./libft/ft_memcmp.c \
            ./libft/ft_strnstr.c ./libft/ft_atoi.c ./libft/ft_strrchr.c ./libft/ft_substr.c \
            ./libft/ft_strjoin.c ./libft/ft_strtrim.c ./libft/ft_split.c ./libft/ft_itoa.c \
            ./libft/ft_strmapi.c ./libft/ft_striteri.c ./libft/ft_putchar_fd.c \
            ./libft/ft_putstr_fd.c

RED = \033[0;31m
GREEN = \033[0;32m
BOLD = \033[1m
RESET = \033[0m

FILE = main.c $(BUILTINS) $(EXECUTION) $(PROTACTION) $(EXPANDING) $(LIB) $(UTILS)

CC = cc  -Wall -Wextra -Werror
LIBC = ar rc

OBJECTFILES = $(FILE:.c=.o)

LIBFT = ./libft/libft.a
NAME = minishell

USR = $(shell echo "$$USER")
READLINE_L = /Users/$(USR)/.brew/opt/readline/lib
READLINE_I = /Users/$(USR)/.brew/opt/readline/include

all: $(NAME)

$(LIBFT): $(LIBFT_SRCS) ./libft/libft.h
		make -C ./libft
		@echo "$(GREEN)$(BOLD)Library created: $(RESET)$(GREEN)$(BOLD)$(LIBFT)$(RESET)"

$(NAME): $(LIBFT) $(OBJECTFILES)
	$(CC) $(OBJECTFILES) -L $(READLINE_L) -lreadline -lncurses $(LIBFT) -o $@
	@echo "$(GREEN)$(BOLD)Executable created: $(RESET)$(GREEN)$(BOLD)$(NAME)$(RESET)"

%.o: %.c ./include/minishel.h  ./libft/libft.h
	$(CC) -c -I $(READLINE_I) $< -o $@

clean:
	rm -f $(OBJECTFILES)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make fclean -C ./libft

re: fclean all

.PHONY: clean