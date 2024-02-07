# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 10:14:23 by xamayuel          #+#    #+#              #
#    Updated: 2024/02/07 19:29:39 by xamayuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_DIR = src
OBJ_DIR = .objs

# COLOR DEFINITION
RESET			= 	\033[0m
GREEN 			= 	\033[38;5;46m
WHITE 			= 	\033[38;5;15m
GREY 			= 	\033[38;5;8m
ORANGE 			= 	\033[38;5;202m
RED 			= 	\033[38;5;160m
PINK			=   \033[38;5;162m
LIGHT_PINK      =   \033[38;5;200m
BLUE			= 	\033[38;5;39m
DARK_BLUE		=   \033[38;5;57m
# SOURCE FILES
SRC =	$(SRC_DIR)/philo.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/timestamps.c \
		$(SRC_DIR)/errors_show.c \
		$(SRC_DIR)/game_data_checks.c \
		$(SRC_DIR)/game_data.c \
		$(SRC_DIR)/game_free.c \
		$(SRC_DIR)/game_start.c \
		$(SRC_DIR)/npc_doctor.c \
		$(SRC_DIR)/npc_life.c \
		$(SRC_DIR)/npc_print.c \

		
SRC2 =	$(SRC_DIR)/philo.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/showerror.c \
		$(SRC_DIR)/game.c \
		$(SRC_DIR)/checks.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/report.c \
		$(SRC_DIR)/time.c
# OBJECTS
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# COMPILER
CC = gcc
HEAD = -I./includes 
CFLAGS = -Wall -Werror -Wextra 
LFLAGS = -lpthread
RM = /bin/rm -rf

# RULES
all: $(NAME)

$(NAME): $(OBJ) 
		$(CC) $(OBJ) $(HEAD) $(CFLAGS) $(LFLAGS) -o $(NAME)
		sleep .5
		clear
		@echo "$(PINK)╔═══════════════════════════════════════╗"
		@echo "$(PINK)║ ${RESET}🙈🙉🙊 ${BLUE} PHILOSOPHER COMPLETE ${RESET}🙈🙉🙊   $(PINK)║"
		@echo "$(PINK)╚═══════════════════════════════════════╝ $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@echo "$(GREY)Compiling.............................$(ORANGE)$(<F)"
		@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
		@echo "$(GREEN)DONE!$(GREY)"
		@sleep .2


clean:
		@$(RM) $(OBJ_DIR)
		sleep .1
		clear

fclean: clean
		@$(RM) $(NAME)
		sleep .1
		clear
		@echo "$(BLUE)╔════════════════════════════════════╗"
		@echo "$(BLUE)║          ${DARK_BLUE} 🗑️  ALL CLEAN 🗑️ ${BLUE}          ║"
		@echo "$(BLUE)╚════════════════════════════════════╝ $(RESET)"

re: fclean all

test1: all
	@echo "TEST 1 ./philo_bonus 1 800 200 200 --> philosopher should not eat and shoud die!"
	@while [ -z "$$CONTINUE" ]; do \
        read -r -p "Type Y/y to start [y/N]: " CONTINUE; \
    done ; \
    [ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	
	@./philo 1 800 200 200

test2:
	@echo "TEST 2 ./philo 5 800 200 200 7 --> No one should die an simulation ends when all the philosphers has eaten at least 7 times each"
	@while [ -z "$$CONTINUE" ]; do \
        read -r -p "Type Y/y to start [y/N]: " CONTINUE; \
    done ; \
    [ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	@echo "running in background"
	@./philo 5 800 200 200 7 | tee test2.txt
	@echo "PHILO 1 eats:"
	@cat test2.txt | grep "  1" | grep "is eating" | wc -l
	@echo "PHILO 2 eats:"
	@cat test2.txt | grep "  2" | grep "is eating" | wc -l
	@echo "PHILO 3 eats:"
	@cat test2.txt | grep "  3" | grep "is eating" | wc -l
	@echo "PHILO 4 eats:"
	@cat test2.txt | grep "  4" | grep "is eating" | wc -l
	@echo "PHILO 5 eats:"
	@cat test2.txt | grep "  5" | grep "is eating" | wc -l


test3:
	@echo "TEST 3 ./philo 4 410 200 200 --> No one should die!"
	@while [ -z "$$CONTINUE" ]; do \
        read -r -p "Type Y/y to start [y/N]: " CONTINUE; \
    done ; \
    [ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	@./philo 4 410 200 200

test4:
	@echo "TEST 4 ./philo 4 310 200 100 --> A philosopher shoud die!"
	@while [ -z "$$CONTINUE" ]; do \
        read -r -p "Type Y/y to start [y/N]: " CONTINUE; \
    done ; \
    [ $$CONTINUE = "y" ] || [ $$CONTINUE = "Y" ] || (echo "Exiting."; exit 1;)
	@./philo 4 310 200 100

	
.PHONY: all clean fclean re test1 test2 test3 test4