NAME = megaphone
CPP = c++
CPPFLAGS  = -Wall -Wextra -Werror -std=c++98 -pedantic-errors
SRCS = megaphone.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -r $(OBJS)

fclean: clean
	rm -r $(NAME)

re: fclean all

.PHONY: all clean fclean re