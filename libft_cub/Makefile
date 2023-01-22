# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 21:11:52 by ibenmain          #+#    #+#              #
#    Updated: 2023/01/10 14:37:20 by ibenmain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = libft.h
SRCS = ft_atoi.c\
	   ft_bzero.c\
	   ft_calloc.c\
	   ft_isalnum.c\
	   ft_isalpha.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprint.c\
	   ft_itoa.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_memcpy.c\
	   ft_memmove.c\
	   ft_memset.c\
	   ft_split.c\
	   ft_strchr.c\
	   ft_strdup.c\
	   ft_strjoin.c\
	   ft_strlcat.c\
	   ft_strlcpy.c\
	   ft_strcpy.c\
	   ft_strlen.c\
	   ft_strncmp.c\
	   ft_strcmp.c\
	   ft_strnstr.c\
	   ft_strrchr.c\
	   ft_strtrim.c\
	   ft_substr.c\
	   ft_tolower.c\
	   ft_toupper.c\
	   ft_strmapi.c\
	   ft_striteri.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c

B_SRCS = ft_lstnew.c\
		 ft_lstadd_front.c\
	   	ft_lstsize.c\
		ft_lstlast.c\
	   	ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
RM = rm -f
AR = @ar -rcs

all : $(NAME)

$(NAME):$(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o:%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(B_OBJS) $(OBJS)
	$(AR) $(NAME) $(OBJS) $(B_OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean:clean
	$(RM) $(NAME)

re:fclean all