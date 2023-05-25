# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 13:38:07 by fkrug             #+#    #+#              #
#    Updated: 2023/05/25 17:02:25 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf

CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_PSWAP = 
SRC_UTILS = fdf.c
SRC = $(SRC_PSWAP) $(SRC_UTILS)
OBJ := $(SRC:.c=.o)

#BON_NAME = 
#BON_DIR = 
#BON_SRC = 	
#BON_FILE = $(addprefix $(BON_DIR),$(BON_SRC))
#SRC_BON = $(BON_FILE) $(SRC_UTILS)
#BON_OBJ := $(BON_FILE:.c=.o)

#all: $(LIBFT) $(NAME)
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC)
#	$(CC) $(CFLAGS) $(SRC) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(BON_FILE)
	$(CC) $(CFLAGS) $(SRC_BON) -L$(LIBFT_DIR) -lft -o $(BON_NAME)

clean:
	/bin/rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	/bin/rm -f $(NAME) $(BON_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all clean

.PHONY: all clean fclean re bonus