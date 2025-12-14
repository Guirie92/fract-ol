# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 21:58:38 by guillsan          #+#    #+#              #
#    Updated: 2025/12/14 14:30:12 by guillsan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror

SRCS_DIR = src
SRCS_EVENTS_DIR = $(SRCS_DIR)/events
SRCS_DRAW_DIR = $(SRCS_DIR)/draw

SRCS_SRC = $(addprefix $(SRCS_DIR)/,            \
				init.c                          \
				parser.c                        \
				render.c                        \
				log.c                           \
				trender_progressive.c           \
				render_progressive.c            \
				free_resources.c                \
				tworker_elapsedtime.c           \
				tworker_init.c                  \
				fractol.c)
SRCS_EVENTS = $(addprefix $(SRCS_EVENTS_DIR)/,  \
				handler_key.c                   \
				handler_mouse.c                 \
				events_funcs.c                  \
				events_init.c                   \
				events.c)
SRCS_DRAW = $(addprefix $(SRCS_DRAW_DIR)/,      \
				draw_text.c                     \
				draw_help_panel.c               \
				draw_panels.c                   \
				draw_init.c)

SRCS = $(SRCS_SRC) $(SRCS_EVENTS) $(SRCS_DRAW)

OBJS = $(SRCS:.c=.o)

LIB_DIR = libft
MLX_DIR = minilibx

LIB_FILE = $(LIB_DIR)/libft.a
MLX_FILE = $(MLX_DIR)/libmlx.a

INC = -I inc
INC_INLINES = -I inc/inlines

INC_LIB = -I $(LIB_DIR)/inc
INC_MLX = -I $(MLX_DIR)

# Compilation and Linking Flags
C_INCLUDES = $(INC) $(INC_LIB) $(INC_INLINES) $(INC_MLX) 
# Links the Libft lib and its path
LDFLAGS = -L $(LIB_DIR) -lft -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

CLR_GRN = \033[0;32m
CLR_RST = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIB_FILE) $(MLX_FILE)
	@$(CC) $(CFLAGS) $(C_INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "\n$(CLR_GRN)--- compilation completed successfully ---$(CLR_RST)\n"
	
# Rule to build the libft lib
$(LIB_FILE):
	@make -C $(LIB_DIR) $(INC_MLX)
	
$(MLX_FILE):
	@make -C $(MLX_DIR)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

clean:
	@make clean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.DEFAULT_GOAL=all