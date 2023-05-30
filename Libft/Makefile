# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 16:35:57 by fkrug             #+#    #+#              #
#    Updated: 2023/05/30 09:44:22 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror

HEADERS	:= -I ./include
VPATH = printf getnextline
LIBFT :=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c	\
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c	\
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c	\
			ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c 		\
			ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c			\
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c 		\
			ft_tolower.c ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c 			\
			ft_lstdelone.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstclear.c		\
			ft_lstiter.c ft_lstmap.c
PRINTF =	ft_printf.c ft_printf_utils_chr.c ft_printf_utils_nbr.c
GNL =		get_next_line.c get_next_line_utils.c
SRC = $(LIBFT) $(addprefix printf/,$(PRINTF)) $(addprefix getnextline/,$(GNL))
OBJ := $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ): %.o:%.c
	$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
