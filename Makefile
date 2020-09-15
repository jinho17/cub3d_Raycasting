NAME = cub3D

CC = gcc
LIB = -L./libft -lft -lmlx -framework OpenGL -framework AppKit

SRC_DIR = ./srcs/
HEADER_DIR = -I./includes
CFLAGS = -Wall -Wextra -Werror $(HEADER_DIR)

SOURCE = main.c map_file_open.c get_map_info.c get_map_info2.c get_map_info_error.c \
	   map_check.c dfs.c key_press.c \
	   loop_manager.c wall_raycasting.c sprite_raycasting.c \
	   load_texture.c save_bmp.c var_malloc.c init_dir_pos.c
SRCS = $(addprefix $(SRC_DIR), $(SOURCE))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft bonus
	$(CC) $(LIB) $(CFLAGS) $(SRCS) -o $(NAME)

bonus: all

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./libft/libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY:all clean fclean re
