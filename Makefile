# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/21 00:13:19 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D = cub3D

CFLAGS = -Wall -Werror -Wextra -Ofast -fsanitize=address -g3 -D $(OS)

RM = rm -rf

HEAD = ./

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
		$(CLEAN_DIR)/error_handler.c \
		main.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT 		= ./includes/libs/libft/libft.a

INCLUDE		:=
MLX_FOLDER	:=	
MLXLIB		:=	
LINKS		:= 

OS := $(shell uname)

ifeq ($(OS), Linux)
	MLX_FOLDER += ./includes/libs/mlx_linux
	# MLXLIB += ./includes/libs/mlx_linux/libmlx_Linux.a
	LINKS += -L/usr/lib -L$(MLX_FOLDER) -lXext -lX11
	INCLUDE +=	-I./ -I./includes/libs/mlx_linux -I./includes/libs/libft 
else
	MLX_FOLDER += ./includes/libs/mlx_mac
	MLXLIB += ./includes/libs/mlx_mac/libmlx.a
	LINKS += -L$(MLX_FOLDER) -framework OpenGL -framework AppKit
	INCLUDE +=	-I./ -I./includes/libs/mlx_mac -I./includes/libs/libft 
endif

all: $(CUB3D)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(INIT_DIR) \
			 $(OBJ_DIR)/$(CUB_UTILS_DIR) $(OBJ_DIR)/$(GAMEPLAY_DIR) $(OBJ_DIR)/$(CLEAN_DIR) 

$(LIBFT):
	@$(MAKE) -C ./includes/libs/libft
	
$(MLXLIB):
	@echo $(YELLOW)"Creating $(MLXLIB)"$(RESET)
	make -C $(MLX_FOLDER)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I$(HEAD) $< -o $@

$(CUB3D): $(OBJ) $(MLXLIB) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXLIB) -I./includes/cub3D.h -o $(CUB3D) $(LINKS)
	@echo "Compilation completed."
	
valgrind: $(OBJS) $(NAME)
	@valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(CUB3D) includes/levels/map1.cub
	
clean:
	@$(MAKE) clean -C ./includes/libs/libft
	@make clean -C $(MLX_FOLDER)
	@$(RM) $(OBJ)
	@echo "All object files removed."

fclean: clean
	@$(MAKE) fclean -C ./includes/libs/libft
	@$(RM) $(CUB3D) $(OBJ_DIR)
	@echo "$(CUB3D) and object files removed."

re: fclean all

.PHONY: all clean fclean re valgrind
