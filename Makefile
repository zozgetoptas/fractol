NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a # derlenmis minilibx statik kutuphanesinin pathi

# MiniLibX Kütüphane Yolları ve Bağlantıları
# -L$(MLX_DIR): Kütüphane arama yoluna MiniLibX klasörünü ekler
# -lmlx: libmlx.a dosyasını bağlar
# -lXext -lX11: MiniLibX'in ihtiyaç duyduğu X11 sistem kütüphaneleri
# -lm: Matematik kütüphanesi (Fraktallar için zorunlu)
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES = -I. -I$(MLX_DIR)
SRCS = mlx_utils.c \
	   math_utils.c \
	   libft_stuff.c \
	   drawing_fractal.c \
	   main.c
	   
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re