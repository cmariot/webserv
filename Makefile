# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2022/11/03 14:01:33 by cmariot          ###   ########.fr        #
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

INCLUDES		+= -I srcs/Webserver/includes
INCLUDES		+= -I srcs/Server/includes
INCLUDES		+= -I srcs/Server/srcs/Error_page/includes
INCLUDES		+= -I srcs/Server/srcs/Location/includes



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
				  $(addprefix Server/srcs/, $(SERVER)) \
				  $(addprefix Webserver/srcs/, $(WEBSERVER)) \
				  $(addprefix Server/srcs/Error_page/srcs/, $(DIRECTIVE_ERROR)) \
				  $(addprefix Server/srcs/Location/srcs/, $(LOCATION))

MAIN			= main.cpp

WEBSERVER		= accept_connexion.cpp \
				  add_client.cpp \
				  add_to_interest_list.cpp \
				  client_connexion.cpp \
				  constructor.cpp \
				  create_epoll_socket.cpp \
				  destructor.cpp \
				  error.cpp \
				  exit_webserv.cpp \
				  init_sockets.cpp \
				  server_response.cpp \
				  launch.cpp \
				  parse.cpp \
				  parse_configuration_file.cpp \
				  parse_server.cpp \
				  remove_client.cpp \
				  remove_commentaries.cpp \
				  replace_blank_characters.cpp \
				  separate_braces.cpp \
				  separate_semicolon.cpp \
				  signals.cpp \
				  split_strings.cpp \
				  usage.cpp \
				  wait_event.cpp 

SERVER			= bind_server_address.cpp \
				  constructor.cpp \
				  create_server_socket.cpp \
				  destructor.cpp \
				  error.cpp \
				  listen_for_clients.cpp \
				  parse_listen_directive.cpp \
				  parse_client_max_body_size_directive.cpp \
				  parse_error_page_directive.cpp \
				  parse_location_context.cpp \
				  parse_server_names_directive.cpp \
				  set_server_arguments.cpp

DIRECTIVE_ERROR	= constructor.cpp \
				  destructor.cpp \
				  getters.cpp \
				  setters.cpp

LOCATION		= constructor.cpp \
				  destructor.cpp \
				  error.cpp \
				  parse_allow_methods.cpp \
				  parse_cgi.cpp \
				  parse_directory_file.cpp \
				  parse_directory_listing.cpp \
				  parse_location.cpp \
				  parse_redirection.cpp \
				  parse_root.cpp \
				  parse_upload.cpp \
				  parse_upload_path.cpp

SRCS			= $(addprefix $(SRC_ROOTDIR), $(SRC_SUBDIR))



# **************************************************************************** #
#                                 OBJECT FILES                                 #
# **************************************************************************** #


OBJ_ROOTDIR		= objs/

OBJ_SUBDIR		= $(SRC_SUBDIR:.cpp=.o)

OBJ_DIR 		= $(shell find ./srcs -type d | sed s/srcs/objs/)

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

#@printf "[$(CYAN)✓$(RESET)] $< \n"

$(NAME)	: 		$(OBJS)
				@printf "\n"
				$(CC) $(LFLAGS) $(OBJS) -o $(NAME)
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
				@printf "__        _______ ____ ____  _____ ______     __\n"
				@printf "\ \      / / ____| __ ) ___|| ____|  _ \ \   / /\n"
				@printf " \ \ /\ / /|  _| |  _ \___ \|  _| | |_) \ \ / / \n"
				@printf "  \ V  V / | |___| |_) |__) | |___|  _ < \ V /  \n"
				@printf "   \_/\_/  |_____|____/____/|_____|_| \_\ \_/   \n"
				@printf "$(RESET)\n"

footer :
				@printf "$(CYAN)"
				@printf "➤ COMPILATION SUCCESS\n"
				@printf "\nUSAGE :\n"
				@printf "$(RESET)"
				@printf "./$(NAME) [configuration file]\n"


-include $(DEPENDS)


.PHONY : 		all clean fclean bonus re
