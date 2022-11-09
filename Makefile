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
				  $(addprefix Webserver/srcs/, $(WEBSERVER)) \
				  $(addprefix Server/srcs/, $(SERVER)) \
				  $(addprefix Error_page/srcs/, $(ERROR_PAGE)) \
				  $(addprefix Location/srcs/, $(LOCATION)) \
				  $(addprefix Request/srcs/, $(REQUEST)) \
				  $(addprefix Response/srcs/, $(RESPONSE)) \
				  $(addprefix Utils/srcs/, $(UTILS))

MAIN			= main.cpp

WEBSERVER		= accept_connexion.cpp \
				  add_to_interest_list.cpp \
				  client_connexion.cpp \
				  constructor.cpp \
				  create_epoll_socket.cpp \
				  destructor.cpp \
				  exit_webserv.cpp \
				  init_sockets.cpp \
				  launch.cpp \
				  parsing/parse.cpp \
				  parsing/parse_configuration_file.cpp \
				  parsing/parse_server.cpp \
				  get_server.cpp \
				  remove_client.cpp \
				  parsing/remove_commentaries.cpp \
				  parsing/replace_blank_characters.cpp \
				  parsing/separate_braces.cpp \
				  parsing/separate_semicolon.cpp \
				  signals.cpp \
				  parsing/split_strings.cpp \
				  parsing/usage.cpp \
				  wait_event.cpp

UTILS			= error.cpp \
				  invalid_directive_len.cpp \
				  set_ip_and_port.cpp

SERVER			= constructor.cpp \
				  parse.cpp \
				  set_listen.cpp \
				  set_server_names.cpp \
				  set_client_max_body_size.cpp \
				  set_error_page.cpp \
				  set_location.cpp \
				  getters.cpp \
				  create_server_socket.cpp \
				  bind_server_address.cpp \
				  listen_for_clients.cpp \
				  destructor.cpp

ERROR_PAGE		= constructor.cpp \
				  destructor.cpp \
				  getters.cpp

LOCATION		= constructor.cpp \
				  destructor.cpp \
				  getters.cpp \
				  set_allow_methods.cpp \
				  set_cgi.cpp \
				  set_directory_file.cpp \
				  set_directory_listing.cpp \
				  parse.cpp \
				  set_redirection.cpp \
				  set_root.cpp \
				  set_upload.cpp \
				  set_upload_path.cpp

REQUEST			= constructor.cpp \
				  get_client_request.cpp \
				  interpret.cpp \
				  destructor.cpp

RESPONSE		= constructor.cpp \
				  update.cpp \
				  Response.cpp \
				  destructor.cpp

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


GREEN		= \033[32;1m
RED			= \033[31;1m
YELLOW		= \033[33;1m
CYAN		= \033[36;1m
RESET		= \033[0m
WHITE 		= \033[0;m
CLEAR		= \033[2K\r



# **************************************************************************** #
#                               MAKEFILE'S RULES                               #
# **************************************************************************** #


.SILENT : 		all

all : 			header $(NAME) footer
				@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(CONFIG_FILE)

$(OBJ_ROOTDIR)%.o: $(SRC_ROOTDIR)%.cpp
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

#@printf "Compiling ⌛ $< \n"
#@printf "[$(CYAN)✓$(RESET)] $< \n"

$(NAME)	:		$(OBJS)
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
				@printf "[$(RESET)OK$(CYAN)]$(RESET) webserv generated.$(CYAN)\n"
				@printf "\nUSAGE :\n"
				@printf "$(RESET)"
				@printf "./$(NAME) [configuration file]\n"


-include $(DEPENDS)


.PHONY : 		all clean fclean bonus re
