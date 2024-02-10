/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamayuel <xamayuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:54:21 by xamayuel          #+#    #+#             */
/*   Updated: 2024/02/10 12:16:05 by xamayuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

/**
 * NAME: ft_bzero()
 * 
 * DESCRIPTION:
 * 		Writes n zeroed bytes to the string s. If n is zero, does nothing.
 * 
 * PARAMETERS:
 * 		@param s: pointer to the string
 * 		@param n: number of bytes to be zeroed
 * 
 * RETURN:
 * 		VOID.
 * 
 * COMMENTS:
 * 		TIP: s[] is equal to (s)[]
 */

void	ft_bzero(void *s, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((unsigned char *)s)[count] = 0;
		count ++;
	}
}

/**
 * NAME: ft_calloc()
 * 
 * DESCRIPTION:
 * 		Contiguously allocates enough space for count objects that are size 
 * 		bytes each. Allocated memory is filled with zeros.
 * 
 * RETURN:
 * 		A pointer to allocated memory. If error occurs, NULL pointer is returned.
 * 
 * PARAMS:
 * 		@param count: number of objects
 * 		@param  size: size of the objects
 * 
 * TIPS:
 * 		1. - Use ft_bzero
 * 		2. - Protect null values.
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc (count * size);
	if (mem != NULL)
	{
		ft_bzero(mem, count * size);
		return (mem);
	}
	else
		return (NULL);
}
