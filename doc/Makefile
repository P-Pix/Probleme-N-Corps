# Documentation Makefile pour le projet N-Corps

.PHONY: all doc pdf doxygen clean help

# Couleurs pour l'affichage
GREEN=\033[0;32m
BLUE=\033[0;34m
YELLOW=\033[0;33m
NC=\033[0m

all: doc ## Génère toute la documentation

doc: doxygen pdf ## Génère Doxygen et PDF

doxygen: ## Génère la documentation Doxygen
	@echo -e "$(BLUE)Génération de la documentation Doxygen...$(NC)"
	@doxygen ../Doxyfile
	@echo -e "$(GREEN)Documentation Doxygen générée dans doc/doxygen/html/$(NC)"

pdf: ## Compile le document LaTeX en PDF
	@echo -e "$(BLUE)Compilation du document LaTeX...$(NC)"
	@pdflatex -interaction=nonstopmode documentation_simple.tex > /dev/null 2>&1
	@pdflatex -interaction=nonstopmode documentation_simple.tex > /dev/null 2>&1
	@echo -e "$(GREEN)Document PDF généré : documentation_simple.pdf$(NC)"

pdf-full: ## Compile le document LaTeX complet (avec caractères spéciaux)
	@echo -e "$(BLUE)Compilation du document LaTeX complet...$(NC)"
	@pdflatex -interaction=nonstopmode documentation.tex > /dev/null 2>&1
	@pdflatex -interaction=nonstopmode documentation.tex > /dev/null 2>&1
	@echo -e "$(YELLOW)Document PDF généré : documentation.pdf (avec avertissements)$(NC)"

readme: ## Vérifie le README.md
	@echo -e "$(BLUE)Vérification du README.md...$(NC)"
	@if [ -f ../README.md ]; then \
		echo -e "$(GREEN)README.md présent et à jour$(NC)"; \
	else \
		echo -e "$(YELLOW)README.md non trouvé$(NC)"; \
	fi

clean: ## Nettoie les fichiers temporaires
	@echo -e "$(BLUE)Nettoyage des fichiers temporaires...$(NC)"
	@rm -f *.aux *.log *.out *.toc *.fdb_latexmk *.fls *.synctex.gz
	@rm -rf doxygen/
	@echo -e "$(GREEN)Nettoyage terminé$(NC)"

mrproper: clean ## Supprime tous les fichiers générés
	@echo -e "$(BLUE)Suppression de tous les fichiers générés...$(NC)"
	@rm -f *.pdf
	@echo -e "$(GREEN)Suppression terminée$(NC)"

help: ## Affiche cette aide
	@echo -e "$(BLUE)Documentation Makefile pour N-Corps$(NC)"
	@echo -e "$(BLUE)=================================$(NC)"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "$(GREEN)%-15s$(NC) %s\n", $$1, $$2}'

# Vérifications
check: ## Vérifie la présence des outils nécessaires
	@echo -e "$(BLUE)Vérification des outils...$(NC)"
	@command -v doxygen >/dev/null 2>&1 || { echo -e "$(YELLOW)Doxygen non installé$(NC)"; }
	@command -v pdflatex >/dev/null 2>&1 || { echo -e "$(YELLOW)PDFLaTeX non installé$(NC)"; }
	@echo -e "$(GREEN)Vérification terminée$(NC)"

install-deps: ## Installe les dépendances de documentation
	@echo -e "$(BLUE)Installation des dépendances...$(NC)"
	@sudo apt-get update
	@sudo apt-get install -y doxygen texlive-latex-base texlive-fonts-recommended texlive-lang-french
	@echo -e "$(GREEN)Installation terminée$(NC)"

stats: ## Affiche des statistiques sur la documentation
	@echo -e "$(BLUE)Statistiques de documentation$(NC)"
	@echo -e "$(BLUE)============================$(NC)"
	@echo -n "Fichiers sources documentés : "
	@find ../src ../include -name "*.cpp" -o -name "*.hpp" | wc -l
	@echo -n "Lignes de documentation : "
	@grep -r "///" ../src ../include 2>/dev/null | wc -l || echo "0"
	@echo -n "Fichiers README : "
	@find .. -name "README*" -o -name "*.md" | wc -l

.DEFAULT_GOAL := help
