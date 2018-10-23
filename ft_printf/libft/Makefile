# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmeier <jmeier@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/18 21:04:05 by jmeier            #+#    #+#              #
#    Updated: 2018/10/22 16:26:28 by jmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIST = ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_strstr ft_strctrim \
		ft_isdigit ft_isprint ft_itoa ft_itoa_base ft_lstadd ft_lstdel \
		ft_lstdelone ft_lstiter ft_lstmap ft_lstnew ft_memalloc ft_memccpy \
		ft_memchr ft_memcmp ft_memcpy ft_memdel ft_memmove ft_memset \
		ft_putchar ft_putchar_fd ft_putendl ft_putendl_fd ft_putnbr ft_arrdup \
		ft_putnbr_fd ft_putstr ft_putstr_fd ft_strcat ft_strchr ft_strclr \
		ft_strcmp ft_strcpy ft_strdel ft_strdup ft_strequ ft_striter \
		ft_striteri ft_strjoin ft_strlcat ft_strlen ft_strmap ft_strmapi \
		ft_strncat ft_strncmp ft_strncpy ft_strnequ ft_strnew ft_strnstr \
		ft_strrchr ft_strsplit ft_strsub ft_strtrim ft_tolower ft_toupper \
		ft_isspace ft_sqrt ft_lstnodecheck get_next_line ft_free ft_realloc \
		ft_putnbr_base ft_putnbr_base_fd ft_putnbr_base_lc ft_putunbr_base \
		ft_putlonglong ft_putlonglong_lc ft_putulonglong ft_putunbr_base_fd \
		ft_putlong ft_putlong_lc ft_putulong ft_putunbr_base_lc ft_putwstr \
		ft_isvalue ft_numlen ft_putchars ft_putnbrf ft_unumlen ft_longlen \
		ft_ulonglen ft_ulonglonglen ft_longlonglen ft_putstrn ft_putull \
		ft_puthex ft_putlhex ft_putoct ft_ld ft_atoi_base ft_pow ft_strfjoin \
		get_file_contents ft_atoi_arr ft_ishex ft_strtolower ft_random_hex

C_LOC = src/
C_NAM = $(addsuffix .c, $(LIST))
C_SRC = $(addprefix $(C_LOC), $(C_NAM))

O_LOC = obj/
O_NAM = $(addsuffix .o, $(LIST))
O_SRC = $(addprefix $(O_LOC), $(O_NAM))

H_LOC = -I inc/

all: $(NAME)

$(NAME): $(O_SRC)
	@echo Building $@...
	@ar rcs $(NAME) $(O_SRC)

$(O_LOC)%.o: $(C_LOC)%.c
	@gcc -Wall -Werror -Wextra $(H_LOC) -o $@ -c $<

clean:
	@echo Cleaning .o files...
	@/bin/rm -f $(O_SRC) libft.h.gch
	@echo .o files removed.

fclean: clean
	@echo Cleaning $(NAME) ...
	@/bin/rm -f $(NAME)
	@echo $(NAME) removed

re: fclean all

.PHONY: all clean fclean re
