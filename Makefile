# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/16 14:55:46 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D			= cub3D

CFLAGS			= -Wall -Werror -Wextra -D Ofast -g3

RM				= rm -rf

LIBFT			= ./includes/libft/libft.a

MINILIBX		= ./includes/libraries/

HEAD			= ./

SRC				= 

OBJ_DIR			= ./obj

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(CUB3D)

$(LIBFT):
	@$(MAKE) -C ./includes/libft

/* if im in mac os operating system run this */
$(MINILIBX):
	@$(MAKE) -C ./includes/libraries/
	
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@
	
$(CUB3D): $(OBJ) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX) -I -framework OpenGL -framework AppKit -g3 -o cub3D
	@echo "compilation completed"

clean:
	@$(MAKE) clean -C ./includes/libraries/
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJ)
	@echo "all object files removed"

fclean: clean
	@$(MAKE) fclean -C ./includes/libft
	@$(RM) $(CUB3D)

re: fclean all

.phony:	all clean fclean re 