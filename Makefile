OBJ = split.c main.c
NAME = test
INCLUDE = ./get_next_line/libgl.a

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) -g $(OBJ) $(INCLUDE) -lmlx -Lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)
