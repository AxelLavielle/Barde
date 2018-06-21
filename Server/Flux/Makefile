SRC				=	src/main.cpp							\
						src/CmdManager.cpp

OBJ 			= $(SRC:.cpp=.o)

CPPFLAGS	=	-Iinclude

NAME			=	player

all:				$(NAME)

$(NAME):		$(OBJ)
						g++ $(OBJ) -o $(NAME)

clean:
						rm -f $(OBJ)

fclean:			clean
						rm -f $(NAME)

re:					clean all

.PHONY:			all clean fclean re
