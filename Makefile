# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/17 14:38:19 by ssibai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D = cub3D

PARSE_DIR = ./parsing

INIT_DIR = ./init

OBJ_DIR = ./obj

SRC =	$(PARSE_DIR)/level_parsing.c \
		$(INIT_DIR)/init.c \
		main.c

CFLAGS = -Wall -Werror -Wextra -Ofast -g3 -I./includes

RM = rm -rf

LIBFT = ./includes/libft/libft.a

MINILIBX = ./includes/mlx/libmlx.a

HEAD = ./

MLX_FLAGS = -L./includes/mlx -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(CUB3D)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(INIT_DIR)

$(LIBFT):
	@$(MAKE) -C ./includes/libft

$(MINILIBX):
	@$(MAKE) -C ./includes/mlx

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I$(HEAD) $< -o $@

$(CUB3D): $(OBJ) $(MINILIBX) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -I -framework -g3 -o $(CUB3D)
	@echo "Compilation completed."

clean:
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJ)
	@echo "All object files removed."

fclean: clean
	@$(MAKE) fclean -C ./includes/libft
	@$(RM) $(CUB3D) $(OBJ_DIR)
	@echo "$(CUB3D) and object files removed."

re: fclean all

.PHONY: all clean fclean re
