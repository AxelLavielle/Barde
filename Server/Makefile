NAME = server
SRC_FOLDER = src
OBJ = $(SRC:.cpp=.o)
CXXFLAGS += -Wall -Wextra -Werror
LDFLAGS = -lboost_system

SRC = $(SRC_FOLDER)/main.cpp \
	$(SRC_FOLDER)/Server.cpp \
	$(SRC_FOLDER)/Connection.cpp

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
