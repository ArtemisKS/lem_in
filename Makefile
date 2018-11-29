# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdzhanaz <vdzhanaz@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/03 20:22:26 by akupriia          #+#    #+#              #
#    Updated: 2018/11/29 16:52:48 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
LIB		=	ft_printf/
LIB_HDR	=	$(LIB)hdr/
SRCD	=	src/
SRC		=	$(SRCD)main_al_exec.c \
			$(SRCD)det_mul_ways.c \
			$(SRCD)auxilary_func.c \
			$(SRCD)ft_lem_in.c \
			$(SRCD)proc_cond_st.c \
			$(SRCD)cout_emmets.c \
			$(SRCD)extra_funcs.c \
			$(SRCD)parse_a_valid.c \
			$(SRCD)parse_rms_lnks.c \
			$(SRCD)init_classes.c \
			$(SRCD)det_paths.c \
			$(SRCD)utils.c
OBJ_D	=	obj/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
LFLAGS	=	-lftprintf -L $(LIB)
IFLAGS	=	-I $(LIB_HDR) -I ./
CFLAGS	=	-g -Wall -Wextra -Werror


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
