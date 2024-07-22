

CUB3D = cub3D

PARSE_DIR = ./parsing

INIT_DIR = ./init

CUB_UTILS_DIR = ./cub_utils

GAMEPLAY_DIR = ./gameplay

CLEAN_DIR = ./cleanup

OBJ_DIR = ./obj

SRC =	$(PARSE_DIR)/level_parsing.c \
		$(PARSE_DIR)/validate_textures.c \
		$(PARSE_DIR)/validate_map.c \
		$(PARSE_DIR)/validate_map_utils.c \
		$(INIT_DIR)/init.c \
		$(CUB_UTILS_DIR)/general_utils.c \
		$(CUB_UTILS_DIR)/map_utils.c \
		$(GAMEPLAY_DIR)/cub3D.c \
		$(GAMEPLAY_DIR)/window_handler.c \
		$(GAMEPLAY_DIR)/draw_utils.c \
		$(CLEAN_DIR)/error_handler.c \
		main.c

CFLAGS = -Wall -Werror -Wextra -Ofast -g3 -I./includes

RM = rm -rf

LIBFT = ./includes/libs/libft/libft.a

MINILIBX = ./includes/libs/mlx_mac/libmlx.a

HEAD = ./

MLX_FLAGS = -L./includes/libs/mlx_mac -lmlx -framework OpenGL -framework AppKit

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(CUB3D)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(INIT_DIR) \
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