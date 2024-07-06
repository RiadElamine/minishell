NAME = minishell
SOURCES = main.c  gc/ft_free.c gc/ft_lstadd_back.c gc/ft_lstadd_front.c gc/ft_lstclear.c gc/ft_lstdelone.c gc/ft_lstlast.c  gc/ft_lstnew.c gc/ft_lstsize.c gc/ft_malloc.c\
<<<<<<< HEAD
		dll_utils.c dll_utils1.c tokenize.c parser.c qu_sp.c\
=======
		dll_utils.c dll_utils1.c tokenize.c parser.c signals.c\
>>>>>>> 66b7fc001a4993188a8593154d33c585d1ca60d4



OBJECTS = $(SOURCES:.c=.o)

LIBFT = cd libft && make
LIB = libft/libft.a


CC = cc
CFLAGS = -Wall -Wextra -Werror  
RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS) 
	@$(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -lreadline


%.o: %.c minishell.h ./libft/libft.h ./libft/gc/gc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	cd libft && make clean 

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean 

re: fclean all