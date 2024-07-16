# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 10:37:13 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/16 10:46:30 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D = cub3D	

CFLAGS = -Wall -Werror -Wextra -D Ofast -g3

RM = rm -rf

MINILIBX = ./includes/libraries

HEAD = ./

SRC = 

OBJ = $(SRC:%.c=%.o)


all: $(CUB3D)

$(LIBFT):
	@$(MAKE) -C ./includes/libft
	
$(MINILIBX):
	@$(MAKE) -C ./includes/minilibx_macos
	
$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@
	
$(CUB3D): $(OBJ) $(MINILIBX)
	@$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) -I -framework OpenGL -framework AppKit -g3 -o cub3D
	@echo "compilation completed"

clean:
	@$(MAKE) clean -C ./includes/minilibx_macos
	@$(RM) $(OBJ)
	@echo "all object files removed"

fclean: clean 
	@$(RM) $(CUB3D)

re: fclean all

.phony:	all clean fclean re 