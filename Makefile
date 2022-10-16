# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/10/16 18:07:56 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                              EXECUTABLE'S NAME                               #
# **************************************************************************** #


NAME			 = webserv

CONFIG_FILE		 = configuration_files/main.conf



# **************************************************************************** #
#                                 COMPILATION                                  #
# **************************************************************************** #


CC				 = c++

CFLAGS			 = -Wall -Wextra -Werror -std=c++98

LFLAGS			 = -Wall -Wextra -Werror -std=c++98

INCLUDES		 = -I includes

INCLUDES		+= -I srcs/Webserver



# **************************************************************************** #
#                                    DEBUG                                     #
# **************************************************************************** #


DEBUG			 = true

ifeq ($(DEBUG), true)

	CFLAGS		+= -g3

	LFLAGS		+= -g3

endif

VALGRIND_FLAGS	 = --leak-check=full --show-leak-kinds=all --track-fds=yes



# **************************************************************************** #
#                                 SOURCE FILES                                 #
# **************************************************************************** #


SRC_ROOTDIR		= srcs/

SRC_SUBDIR	    = $(MAIN) \
				  $(addprefix Webserver/, $(WEBSERVER))

MAIN			= main.cpp

WEBSERVER		= Webserver.cpp

SRCS			= $(addprefix $(SRC_ROOTDIR), $(SRC_SUBDIR))



# **************************************************************************** #
#                                 OBJECT FILES                                 #
# **************************************************************************** #


OBJ_ROOTDIR		= objs/

OBJ_SUBDIR		= $(SRC_SUBDIR:.cpp=.o)

OBJ_DIR 		= $(shell find ./srcs -type d | sed s/".\/srcs"/".\/objs"/g)

OBJS			= $(addprefix $(OBJ_ROOTDIR), $(OBJ_SUBDIR))

DEPENDS			:= $(OBJS:.o=.d)



# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #


RED				= \033[31;1m

CYAN			= \033[36;1m

RESET			= \033[0m



# **************************************************************************** #
#                               MAKEFILE'S RULES                               #
# **************************************************************************** #


.SILENT : 		all

all : 			header $(NAME) footer

$(OBJ_ROOTDIR)%.o: $(SRC_ROOTDIR)%.cpp
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(NAME)	: 		$(OBJS)
				$(CC) $(LFLAGS) $(OBJS) $(LIBRARY) -o $(NAME)
				@printf "\n"

leaks :			$(NAME)
				@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(CONFIG_FILE)

test :			$(NAME)
				@./$(NAME) $(CONFIG_FILE)

clean :
				@rm -rf $(OBJ_ROOTDIR) $(DEPENDS)
				@printf "$(RED)"
				@printf "Object files removed\n"
				@printf "$(RESET)"

fclean :
				@-rm -f $(NAME)
				@-rm -rf $(OBJ_ROOTDIR) $(DEPENDS)
				@printf "$(RED)"
				@printf "Binary and object files removed\n"
				@printf "$(RESET)"

re :			fclean all

header :
				@printf "$(CYAN)"
				@printf "WEBSERV COMPILATION\n"
				@printf "$(RESET)"

footer :
				@printf "$(CYAN)"
				@printf "➤     SUCCESS\n"
				@printf "\nUSAGE\n"
				@printf "$(RESET)"
				@printf "./$(NAME) [configuration file]\n"


-include $(DEPENDS)


.PHONY : 		all clean fclean bonus re
