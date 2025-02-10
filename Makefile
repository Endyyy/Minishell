
LIBFT_PATH		=	./libs/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES	=	ft_built_in.c		\
					ft_isbuilt_in.c		\
					ft_exec.c			\
					ft_exec_path.c		\
					ft_export2.c		\
					ft_export.c			\
					ft_init_env.c		\
					main.c				\
					ft_redir.c			\
					ft_pipe.c			\
					ft_pipe_bis.c		\
					ft_pipe_alpha.c		\
					ft_main_loop.c		\
					ft_main_loop_bis.c	\
					ft_main_loop_3.c	\
					ft_manage_one_cmd.c	\
					ft_manage_env.c		\
					ft_manage_env2.c	\
					ft_complete.c		\
					ft_env_var.c		\
					ft_parser.c			\
					ft_parser2.c		\
					ft_token.c			\
					ft_create_env.c		\
					ft_free.c			\
					ft_get_utils.c		\
					ft_utils.c			\
					ft_redir_parse.c	\
					ft_print.c			\
					ft_echo.c			\
					ft_echo_bis.c		\
					ft_heredoc.c		\
					ft_heredoc_bis.c	\
					ft_utils2.c

SOURCES_DIR		=	srcs

HEADER			=	$(SOURCES_DIR)/mini.h

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	minishell

CC				=	gcc
RM				=	rm -f

CFLAGS			=	-g -Wall -Werror -Wextra

LFLAGS			=	-L/usr/local/lib -I/usr/local/include -lreadline

.c.o:
				$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)  $(LFLAGS)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:				fclean all

.SILENT:

.PHONY:			all clean fclean re libft
