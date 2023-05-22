#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include<stdlib.h>
# include<unistd.h>
#include <stdarg.h>
# include "Libft/libft.h"
# include<stdio.h>

typedef struct s_data
{
	int			dash;
	int			zero;
	int			space;
	int			hash;
	int 		plus;
	int			counter;
	va_list		*args;
	const char	*fmt;
} t_data;

t_data	ft_datainit(va_list *args, const char *fmt);

int	ft_printf(const char *fmt, ...);

#endif