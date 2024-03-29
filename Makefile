# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkrug <fkrug@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 09:15:48 by fkrug             #+#    #+#              #
#    Updated: 2023/07/03 14:35:49 by fkrug            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf

OPSYS := $(shell uname)
ifeq ($(OPSYS), Linux)
	CC := gcc
	DB := gdb
else ifeq ($(OPSYS), Darwin)
	CC := cc
	DB := lldb
	LIB_PATH := -L"$(shell brew --prefix glfw)/lib/"
endif
CFLAGS := -Wextra -Wall -Werror
# -Ofast -Wunreachable-code 
LIBMLX	:= MLX42
MLX := $(LIBMLX)/build/libmlx42.a
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADERS	:= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT_DIR)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl $(LIB_PATH) -lglfw -pthread -lm \
			$(LIBFT)
SRCS_DIR:= ./src/
SRCS	:= fdf.c fdf_read_map.c fdf_utils.c fdf_draw_utils.c fdf_rotate.c \
			fdf_move_zoom.c fdf_init.c fdf_projections.c fdf_color.c \
			fdf_font.c
SRCS := $(addprefix $(SRCS_DIR),$(SRCS))
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(MLX):
	@if [ ! -d "./$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJS): %.o:%.c
	@$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@ && printf "Compiling: $(notdir $<)\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
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

.PHONY: all clean fclean re