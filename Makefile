# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hsillem <hsillem@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/01 14:17:23 by hsillem       #+#    #+#                  #
#    Updated: 2020/12/09 15:58:32 by hsillem       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libminirt.a
SRC = image_utils ray_gun math sphere plane triangle parcer linked_list visual_utils utils get_color
SRCC = $(SRC:%=%.c)
SRCO = $(SRC:%=%.o)
GNLSRC = get_next_line_utils get_next_line
GNLSRCC = $(GNLSRC:%=gnl/%.c)
GNLSRCO = $(GNLSRC:%=%.o)
FLAGS = -Wall -Werror -Wextra
MLXFLAGS = -L minilibx -lmlx -framework OpenGL -framework AppKit

ifdef DEBUG
	FLAGS += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(SRCC)
	gcc -c $(FLAGS) $(SRCC) $(GNLSRCC) -I.
	ar -rc $(NAME) $(SRCO) $(GNLSRCO)

minilibx:
	$(MAKE) -C minilibx

clean:
	/bin/rm -f $(SRCO)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

cr: all
	gcc main.c $(FLAGS) $(MLXFLAGS) $(NAME)
	./a.out
	/bin/rm -f $(SRCO)