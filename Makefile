# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amsenhaj <amsenhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 22:15:17 by amsenhaj          #+#    #+#              #
#    Updated: 2022/03/05 22:18:54 by amsenhaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM =	check_and_fill.c\
		exec_file.c\
		list_manipulation.c\
		pipex.c\
		split_file.c\
		utils.c\
		utils2.c

SRCB =	bonus/check_and_fill_b.c\
		bonus/exec_file_b.c\
		bonus/here_doc.c\
		bonus/list_manipulation_b.c\
		bonus/pipex_bonus.c\
		bonus/split_file.c\
		bonus/utils2_b.c\
		bonus/utils_b.c

NAME = pipex
NAMEB = pipex_bonus

CFLAGS = -Wall -Wextra -Werror

$(NAME) : ${SRCM} pipex.h
	$(CC) $(CFLAGS) ${SRCM} -o ${NAME}



all : $(NAME)

$(NAMEB) : ${SRCB} pipex.h
	$(CC) $(CFLAGS) ${SRCB} -o ${NAMEB}
	
bonus : $(NAMEB)

clean : 
	rm -rf ${NAME}
	rm -rf ${NAMEB}

fclean : clean

re : fclean all

