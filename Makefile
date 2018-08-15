#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 20:22:26 by akupriia          #+#    #+#              #
#    Updated: 2018/06/03 20:22:29 by akupriia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	lem-in
LIB		=	ft_printf/
LIB_HDR	=	$(LIB)hdr/
SRCD	=	src/
SRC		=	$(SRCD)algorithm.c \
			$(SRCD)assign_rooms.c \
			$(SRCD)find_paths.c \
			$(SRCD)lst_func.c \
			$(SRCD)main.c \
			$(SRCD)parse_make_step.c \
			$(SRCD)print_ants.c \
			$(SRCD)read_validate.c \
			$(SRCD)rooms_links.c \
			$(SRCD)struct_funcs.c \
			$(SRCD)ways_rooms.c
OBJ_D	=	obj/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
LFLAGS	=	-lftprintf -L $(LIB)
IFLAGS	=	-I $(LIB_HDR) -I ./
CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)
	gcc -o $(NAME) $(CFLAGS) $(LFLAGS) $(OBJ)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRCD)

$(OBJ_D)%.o: %.c
	gcc $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_D)
	make fclean -C $(LIB)

re: fclean all

.PHONY: all clean fclean re