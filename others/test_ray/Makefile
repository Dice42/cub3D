# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 19:02:56 by heltayb           #+#    #+#              #
#    Updated: 2024/08/04 15:52:03 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: clean
	cc -I mlx   main.c ../../includes/libs/mlx_mac/libmlx.a -framework OpenGL -framework AppKit -o raycast && ./raycast
3d: clean
	cc -I mlx   main3d.c ../../includes/libs/mlx_mac/libmlx.a -framework OpenGL -framework AppKit -o raycast3d && ./raycast3d

test: clean
	cc -fsanitize=address -g3 -I mlx   test.c ../../includes/libs/mlx_mac/libmlx.a -framework OpenGL -framework AppKit -o test && ./test

clean:
	rm -f raycast raycast3d test