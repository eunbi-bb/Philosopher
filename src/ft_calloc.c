/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:03:14 by eucho         #+#    #+#                 */
/*   Updated: 2023/09/04 10:54:03 by eunbi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
		Calloc allocates 'size' variable to 'count' memory space.
		The allocated memeory is filled with 0 to allocated memeory address.
		In void*, returning 0 is sams as NULL. 
		Because NULL is a pointer and address of 0.
		Malloc returns NULL when it failed to allocate memory.
	PARAMETERS
		count : The count of objects to allocate.
		size  : The size of bytes in each object.
*/
#include <stdlib.h>

static void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(count * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}
