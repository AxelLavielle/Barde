SRC				=	src/main.cpp \
						src/Player.cpp

OBJ 			= $(SRC:.cpp=.o)

CPPFLAGS	=	-Iinclude

LDLIBS		= -lvlc

NAME			=	player

all:				$(NAME)

$(NAME):		$(OBJ)
						g++ $(OBJ) $(LDLIBS) -o $(NAME)

clean:
						rm -f $(OBJ)

fclean:			clean
						rm -f $(NAME)

re:					clean all

.PHONY:			all clean fclean re
