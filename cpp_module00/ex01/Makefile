NAME = phonebook
CPP = c++
CPPFLAGS  = -Wall -Wextra -Werror -std=c++98 -pedantic-errors -MMD -MP
SRCS = Contact.cpp \
		PhoneBook.cpp \
		main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re