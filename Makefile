# Makefile can't refuse to execute these commands.
.PHONY: all run clean mrproper named

# Color
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
YELLOW='\033[0;33m'

# when user write make
.DEFAULT_GOAL := help

# for all file .cpp in the directory src/
SRC	= $(wildcard src/*.cpp src/contoller/*.cpp src/model/*.cpp src/view/*.cpp)

# Transform all file .cpp in the directory src/ in file .o
OBJ	= $(SRC:.cpp=.o)

# ajoute bin/ devant chaque element dans la liste OBJ
COMPILE_OBJ = $(addprefix bin/,$(OBJ))

# Compilator
CC = g++

# Name Executable
NAME = N-Corps
CFLAGS =
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -pthread -lsfml-system -lsfml-window -lsfml-graphics
LDFLAGS	=

all: $(NAME) clean ## Compile link and clean all .o file

$(NAME): $(OBJ) ## Compile and link
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(COMPILE_OBJ) -o $(NAME)

run: ## Execute the executable
	@./$(NAME)

help: ## Affiche la liste des commandes
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

named: ## List all file .cpp in the directory
	@echo "Name: $(SRC)"

%.o: %.cpp ## Compile the file into an object file
	$(CC) -c $< -o $@ $(CXXFLAGS)
	@mv $@ bin/$@

clean:	## Vide les fichiers .o et le fichier executable
	@rm -rf $(COMPILE_OBJ)

mrproper: clean  ## Vide les fichiers .o et le fichier executable
	@rm -rf $(NAME)

init: ## Create the directory bin/ and obj/
	@mkdir -p bin bin/src/model bin/src/view bin/src/controller