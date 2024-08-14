# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/08/14 16:14:56 by ssibai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D = cub3D

PARSE_DIR = ./parsing

CUB_UTILS_DIR = ./cub_utils

GAMEPLAY_DIR = ./gameplay

TEXTURE_DIR = ./texture

CLEAN_DIR = ./cleanup

OBJ_DIR = ./obj

VISUALS_DIR = ./visuals

SRC =	$(PARSE_DIR)/level_parsing.c \
		$(PARSE_DIR)/validate_textures.c \
		$(PARSE_DIR)/validate_map.c \
		$(PARSE_DIR)/validate_clr.c \
		$(PARSE_DIR)/validate_map_utils.c \
		$(CUB_UTILS_DIR)/init.c \
		$(CUB_UTILS_DIR)/general_utils.c \
		$(CUB_UTILS_DIR)/map_utils.c \
		$(GAMEPLAY_DIR)/cub3D.c \
		$(GAMEPLAY_DIR)/window_handler.c \
		$(GAMEPLAY_DIR)/player_init.c \
		$(GAMEPLAY_DIR)/player_controller.c \
		$(GAMEPLAY_DIR)/player_transform.c \
		$(GAMEPLAY_DIR)/keys_handler.c \
		$(GAMEPLAY_DIR)/level_collisions.c \
		$(GAMEPLAY_DIR)/horizontal_ray.c \
		$(GAMEPLAY_DIR)/vertical_ray.c \
		$(GAMEPLAY_DIR)/ray_cast.c \
		$(GAMEPLAY_DIR)/ray_casting.c \
		$(VISUALS_DIR)/player_visuals.c \
		$(VISUALS_DIR)/visuals.c \
		$(VISUALS_DIR)/3d_visuals.c \
		$(CLEAN_DIR)/error_handler.c \
		$(TEXTURE_DIR)/texture_utils.c \
		$(TEXTURE_DIR)/load_textures.c \
		main.c

CFLAGS = -Wall -Werror -Wextra -Ofast -fsanitize=address -g3 -I./includes

RM = rm -rf

LIBFT = ./includes/libs/libft/libft.a

MINILIBX = ./includes/libs/mlx_mac/libmlx.a

HEAD = ./

MLX_FLAGS = -L./includes/libs/mlx_mac -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(CUB3D)

run: $(CUB3D)
	./$(CUB3D) includes/levels/map1.cub

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(INIT_DIR) $(OBJ_DIR)/$(VISUALS_DIR) \
			 $(OBJ_DIR)/$(CUB_UTILS_DIR) $(OBJ_DIR)/$(GAMEPLAY_DIR) $(OBJ_DIR)/$(CLEAN_DIR) \
			 $(OBJ_DIR)/$(TEXTURE_DIR) 

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

fclean: 
	make clean
	@$(MAKE) fclean -C ./includes/libs/libft
	@$(RM) $(CUB3D) $(OBJ_DIR)
	@echo "$(CUB3D) and object files removed."

re: 
	make fclean
	make all


.PHONY: all clean fclean re 