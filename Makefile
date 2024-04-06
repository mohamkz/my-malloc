CC := cc
CFLAGS := -O0 -g -Wall -Wextra -Werror -fpic
OBJ := my_malloc.o
TARGET := libmy_malloc.so

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

