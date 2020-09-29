# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngontjar <niko.gontjarow@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/08 19:59:39 by msuarez-          #+#    #+#              #
#    Updated: 2020/09/29 14:32:01 by ngontjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tiny

SOURCES =	main.c \
			vec2.c \
			vec3.c \
			vec4.c \
			mat4.c \
			draw.c \
			model.c \
			raster.c

OBJECTS = $(subst .c,.o,$(SOURCES))

LIBFT = libft/libft.a

SDL2 = libsdl/libSDL2.a

SDL2_IMAGE = libsdl/libSDL2_image.a

SDL2_MIXER = libsdl/libSDL2_mixer.a

FLAGS = -Wall -Wextra -g #-Werror

LINUX_LINKS = -I libft -L libft -l ft \
		-I ./mlx -L ./mlx -l mlx \
		-lm -lXext -lX11 -lpthread \
        -I ./libsdl -L ./libsdl -ldl

LIBSDL2 =		./libsdl-mac

MAC_INCLUDES =	-I libft -L libft -l ft \
				-I $(LIBSDL2)/SDL2.framework/Headers \
				-I $(LIBSDL2)/SDL2_image.framework/Headers

MAC_FLAGS =		-rpath $(LIBSDL2) \
				-framework SDL2 -F$(LIBSDL2)/ \
				-framework SDL2_image -F$(LIBSDL2)/

MSG = \033[38;5;214m
END = \033[0m

.PHONY: all clean fclean re linux

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(OBJECTS) $(FLAGS) $(MAC_FLAGS) $(MAC_INCLUDES) -o $(NAME)
	@echo "$(MSG)Done!$(END)"

linux: $(OBJECTS)
	@gcc $(OBJECTS) -o $(NAME) $(FLAGS) $(SDL2) $(SDL2_IMAGE) $(SDL2_MIXER) $(LINUX_LINKS)
	@echo "$(MSG)Done!$(END)"

$(OBJECTS): $(LIBFT) $(SOURCES)
	@echo "$(MSG)Compiling...$(END)"
	@gcc $(FLAGS) $(MAC_INCLUDES) $(MAC_FLAGS) $(LIBFT) -c $(SOURCES)

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
