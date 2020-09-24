# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/08 19:59:39 by msuarez-          #+#    #+#              #
#    Updated: 2020/09/24 02:46:19 by ngontjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tiny

SOURCES =	main.c \
			vec2.c \
			vec3.c \
			vec4.c \
			draw.c \
			model.c

OBJECTS = $(subst .c,.o,$(SOURCES))

LIBFT = libft/libft.a

SDL2 = libsdl/libSDL2.a

SDL2_IMAGE = libsdl/libSDL2_image.a

SDL2_MIXER = libsdl/libSDL2_mixer.a

FLAGS = -Wall -Wextra #-Werror

LINUX_LINKS = -I libft -L libft -l ft \
		-I ./mlx -L ./mlx -l mlx \
		-lm -lXext -lX11 -lpthread \
        -I ./libsdl -L ./libsdl -ldl

MSG = \033[38;5;214m
END = \033[0m

.PHONY: all clean fclean re linux

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(FLAGS) -Imlx/mlx.h $(SOURCES) $(LIBFT) \
	-lmlx -lSDL2 -lSDL2_mixer -lSDL2_image \
	-framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(MSG)Done!$(END)"

linux: $(OBJECTS)
	@gcc $(OBJECTS) -o $(NAME) $(FLAGS) $(SDL2) $(SDL2_IMAGE) $(SDL2_MIXER) $(LINUX_LINKS)
	@echo "$(MSG)Done!$(END)"

$(OBJECTS): $(LIBFT) $(SOURCES)
	@echo "$(MSG)Compiling...$(END)"
	@gcc $(FLAGS) -c $(SOURCES)

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@rm -f $(OBJECTS)
	@echo "$(MSG)Objects removed!$(END)"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(MSG)Targets removed!$(END)"

re: fclean all
