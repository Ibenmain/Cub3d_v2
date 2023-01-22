NAME = cub3d
INC = cub3d_src/cub3d.h
LIBFT = ./libft_cub/libft.a
CFLAGS = -Wall -Werror -Wextra 
CC = cc
RM = rm -rf
SRCS = cub3d_src/main.c cub3d_src/get_next_line.c cub3d_src/get_next_line_utils.c\
		cub3d_src/error_up_map.c cub3d_src/error_up_map1.c cub3d_src/error_up_map2.c \
		cub3d_src/parssing.c cub3d_src/error_redirection.c cub3d_src/error_directions.c\
		cub3d_src/cub3d.c cub3d_src/mlx.c cub3d_src/player.c cub3d_src/player_movement.c \
		cub3d_src/mlx_hook.c
OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft_cub

clean:
	$(RM) $(OBJS)
	make -C ./libft_cub clean

fclean : clean
	$(RM) $(NAME)
	make -C ./libft_cub fclean

re : fclean all