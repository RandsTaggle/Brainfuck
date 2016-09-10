/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainfuck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 13:29:35 by exam              #+#    #+#             */
/*   Updated: 2016/08/26 14:39:24 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

typedef void		(*function)(char **, char **);

typedef struct {
    char			name;
    function		command;
}					instruction;

void	ft_putchar(char **memory_ptr, char **instruction_ptr)
{
	write(1, *memory_ptr, 1);
}

void	ft_readchar(char **memory_ptr, char **instruction_ptr)
{
	read(0, *memory_ptr, 1);
}

void	ft_add(char **memory_ptr, char **instruction_ptr)
{
	(**memory_ptr)++;
}

void	ft_sub(char **memory_ptr, char **instruction_ptr)
{
	(**memory_ptr)--;
}

void	ft_increment(char **memory_ptr, char **instruction_ptr)
{
	(*memory_ptr)++;
}

void	ft_decrement(char **memory_ptr, char **instruction_ptr)
{
	(*memory_ptr)--;
}

void	ft_find_matching_closing_bracket(char **memory_ptr,
									  char **instruction_ptr)
{
    int    bracket_couples;

	if ((**memory_ptr) == '\0')
	{
		bracket_couples = 1;
		while (bracket_couples != 0)
		{
			(*instruction_ptr) += sizeof(char);
			if ((**instruction_ptr) == ']')
				bracket_couples--;
			else if ((**instruction_ptr) == '[')
				bracket_couples++;
		}
	}
}

void	ft_find_matching_opening_bracket(char **memory_ptr,
									  char **instruction_ptr)
{
    int    bracket_couples;

	if ((**memory_ptr) != '\0')
	{
		bracket_couples = 1;
		while (bracket_couples != 0)
		{
			(*instruction_ptr) -= sizeof(char);
			if ((**instruction_ptr) == '[')
				bracket_couples--;
			else if ((**instruction_ptr) == ']')
				bracket_couples++;
		}
	}
}

int		main(int argc, char **argv)
{
	const int		MEMORY_SIZE = 2048;
	const int		NB_INSTRUCTIONS = 8;
	char			memory[MEMORY_SIZE];
	char			*memory_ptr;
	char			*instruction_ptr;
	int				i;
	instruction		instructions_list[NB_INSTRUCTIONS];

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	instructions_list[0].name = '+';
	instructions_list[0].command = ft_add;
	instructions_list[1].name = '-';
	instructions_list[1].command = ft_sub;
	instructions_list[2].name = '>';
	instructions_list[2].command = ft_increment;
	instructions_list[3].name = '<';
	instructions_list[3].command = ft_decrement;
	instructions_list[4].name = '[';
	instructions_list[4].command = ft_find_matching_closing_bracket;
	instructions_list[5].name = ']';
	instructions_list[5].command = ft_find_matching_opening_bracket;
	instructions_list[6].name = '.';
	instructions_list[6].command = ft_putchar;
	instructions_list[7].name = ',';
	instructions_list[7].command = ft_readchar;
	i = 0;
	while (i < MEMORY_SIZE)
		memory[i++] = 0;
	instruction_ptr = argv[1];
	memory_ptr = memory;
	while (*instruction_ptr != '\0')
	{
		i = 0;
		while (i < NB_INSTRUCTIONS)
		{
			if ((*instruction_ptr) == instructions_list[i].name)
			{
				instructions_list[i].command(&memory_ptr, &instruction_ptr);
				break;
			}
			i++;
		}
		instruction_ptr += sizeof(char);
	}
	return (0);
}
