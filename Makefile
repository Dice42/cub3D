# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtcsbza <vtcsbza@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/08/03 22:12:34 by vtcsbza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D = cub3D

PARSE_DIR = ./parsing

INIT_DIR = ./init

CUB_UTILS_DIR = ./cub_utils

GAMEPLAY_DIR = ./gameplay

CLEAN_DIR = ./cleanup

OBJ_DIR = ./obj

VISUALS_DIR = ./visuals

SRC =	$(PARSE_DIR)/level_parsing.c \
		$(PARSE_DIR)/validate_textures.c \
		$(PARSE_DIR)/validate_map.c \
		$(PARSE_DIR)/validate_map_utils.c \
		$(INIT_DIR)/init.c \
		$(CUB_UTILS_DIR)/general_utils.c \
		$(CUB_UTILS_DIR)/map_utils.c \
		$(GAMEPLAY_DIR)/cub3D.c \
		$(GAMEPLAY_DIR)/window_handler.c \
		$(GAMEPLAY_DIR)/player_init.c \
		$(GAMEPLAY_DIR)/player_controller.c \
		$(GAMEPLAY_DIR)/player_transform.c \
		$(GAMEPLAY_DIR)/keys_handler.c \
		$(GAMEPLAY_DIR)/ray_casting.c \
		$(GAMEPLAY_DIR)/level_collisions.c \
		$(GAMEPLAY_DIR)/ray_cast.c \
		$(VISUALS_DIR)/player_visuals.c \
		$(VISUALS_DIR)/minimap_visuals.c \
		$(VISUALS_DIR)/draw_utils.c \
		$(VISUALS_DIR)/3d_visuals.c \
		$(CLEAN_DIR)/error_handler.c \
		main.c

# CFLAGS = -Wall -Werror -Wextra -Ofast -fsanitize=address -g3 -I./includes
CFLAGS = -fsanitize=address -g3 -I./includes

RM = rm -rf

LIBFT = ./includes/libs/libft/libft.a

MINILIBX = ./includes/libs/mlx_mac/libmlx.a

HEAD = ./

MLX_FLAGS = -L./includes/libs/mlx_mac -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(CUB3D)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(INIT_DIR) $(OBJ_DIR)/$(VISUALS_DIR) \
			 $(OBJ_DIR)/$(CUB_UTILS_DIR) $(OBJ_DIR)/$(GAMEPLAY_DIR) $(OBJ_DIR)/$(CLEAN_DIR) 

$(LIBFT):
	@$(MAKE) -C ./includes/libs/libft

$(MINILIBX):
	@$(MAKE) -C ./includes/libs/mlx_mac

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I$(HEAD) $< -o $@

$(CUB3D): $(OBJ) $(MINILIBX) $(LIBFT) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -I -framework -g3 -o $(CUB3D)
clean:
	@$(MAKE) clean -C ./includes/libs/libft
	@$(MAKE) clean -C ./includes/libs/mlx_mac
	@$(RM) $(OBJ)
	@echo "All object files removed."

fclean: clean
	@$(MAKE) fclean -C ./includes/libs/libft
	@$(RM) $(CUB3D) $(OBJ_DIR)
	@echo "$(CUB3D) and object files removed."

re: fclean all


.PHONY: all clean fclean re 