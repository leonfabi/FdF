# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 09:15:48 by fkrug             #+#    #+#              #
#    Updated: 2023/06/21 14:05:09 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= FdF

OPSYS := $(shell uname)
ifeq ($(OPSYS), Linux)
	CC := gcc
	DB := gdb
	CFLAGS ?= -g
#	-Wextra -Wall -Werror -Wunreachable-code -Ofast
else ifeq ($(OPSYS), Darwin)
	CC := cc
	DB := lldb
	CFLAGS ?= -g
#-Wunreachable-code -Ofast
# -Wextra -Wall -Werror 
	LIB_PATH := -L"$(shell brew --prefix glfw)/lib/"
else
	$(error $(OPSYS))
endif
LIBMLX	:= MLX42
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADERS	:= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT_DIR)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl $(LIB_PATH) -lglfw -pthread -lm \
			$(LIBFT)
SRCS	:= fdf.c fdf_read_map.c fdf_utils_1.c fdf_draw_utils_1.c fdf_rotate.c \
			fdf_move_zoom.c
OBJS	:= ${SRCS:.c=.o}

all: $(LIBFT) libmlx $(OBJS) $(NAME)

libmlx:
	@if [ ! -d "./$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJS): %.o:%.c
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@ && printf "Compiling: $(notdir $<)\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@if [ -d "$(LIBMLX)/build" ]; then \
		rm -r $(LIBMLX)/build; \
	fi
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx