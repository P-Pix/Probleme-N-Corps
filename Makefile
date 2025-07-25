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
SRC	= $(wildcard src/*.cpp src/controller/*.cpp src/model/*.cpp src/view/*.cpp)

# Transform all file .cpp in the directory src/ in file .o
OBJ	= $(SRC:.cpp=.o)

# ajoute bin/ devant chaque element dans la liste OBJ
COMPILE_OBJ = $(addprefix bin/,$(OBJ))

# Compilator
CC = g++

# Name Executable
NAME = N-Corps
CFLAGS =
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -pthread $(shell pkg-config --cflags sdl2 SDL2_ttf)
LDFLAGS	= $(shell pkg-config --libs sdl2 SDL2_ttf)

all: $(NAME) clean ## Compile link and clean all .o file

$(NAME): $(OBJ) ## Compile and link
	$(CC) $(CXXFLAGS) $(COMPILE_OBJ) -o $(NAME) $(LDFLAGS)

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

demo: ## Run physics demonstration (no graphics)
	@echo -e $(CYAN)"Compilation de la démonstration..."$(NC)
	g++ $(CXXFLAGS) -I./include demo/demo_simulation.cpp src/model/Body.cpp src/model/Simulation.cpp -o demo_runner
	@echo -e $(GREEN)"Exécution de la démonstration..."$(NC)
	./demo_runner
	@rm -f demo_runner

test: ## Run unit tests
	@echo -e $(CYAN)"Compilation des tests..."$(NC)
	g++ $(CXXFLAGS) -I./include test/test_simulation.cpp src/model/Body.cpp src/model/Simulation.cpp -o test_runner
	@echo -e $(GREEN)"Exécution des tests..."$(NC)
	./test_runner
	@rm -f test_runner

test-features: ## Test new interactive features
	@echo -e $(CYAN)"Test des nouvelles fonctionnalités..."$(NC)
	g++ $(CXXFLAGS) -I./include test/test_features.cpp src/controller/Application.cpp src/view/ConfigWindow.cpp src/view/Renderer.cpp src/model/Body.cpp src/model/Simulation.cpp -o test_features $(LDFLAGS)
	@echo -e $(GREEN)"Exécution des tests de fonctionnalités..."$(NC)
	./test_features
	@rm -f test_features

init: ## Create the directory bin/ and obj/
	@mkdir -p bin bin/src/model bin/src/view bin/src/controller