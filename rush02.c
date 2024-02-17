#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    print_error()
{
	write(1, "Error", 5);
	write(1, "\n", 1);
}

void	free_tab(int **tab, int size) {
	while (--size >= 0)
		free(tab[size]);
	free(tab);
}

void	free_sides(int *clup, int *cldown, int *rwleft, int *rwright)
{
	free(clup);
	free(cldown);
	free(rwleft);
	free(rwright);
}

int	is_arg_valid(char *str) {
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	if (i != 31)
		return (0);
	i = 0;
	while (*str != '\0')
	{
		if (*str != '\0' && *str == ' ')
			str++;
		count++;
		if (*str != '\0' && *str >= '1' && *str <= '4')
			str++;
		if (*str != '\0' && *str != ' ')
			return (0);
	}
	if (count == 16)
		return (1);
	return (0);
}

int	check_occurencies(int *occur)
{
	int	i;

        i = 0;
        while (i < 4) {
                if ((i == 0 || i == 3) && occur[i] > 1)
                        return (0);
                if (i == 2 && occur[i] > 2)
                        return (0);
                if (i == 1 && occur[i] > 3)
                        return (0);
                i++;
        }
	return (1);
}

void	fill_with_four(int **tab, int *side1, int *side2, int flip)
{
	int	col;
	
	col = 0;
	while (col < 4)
	{
		if (side1[col] == 1)
		{
			if (flip)
				tab[col][0] = 4;
			else
				tab[0][col] = 4;
		}
		col++;
	}
        col = 0;
        while (col < 4)
        {
                if (side2[col] == 1)
		{
                        if (flip)
                                tab[col][3] = 4;
                        else
                                tab[3][col] = 4;
		}
		col++;
        }

}

int	is_parse_valid(int *side1, int *side2)
{
	int	i;
	int	cumul;
	int	occur1[4];
	int	occur2[4];

	/* in tab1 and tab2 index 0 represent the 1 value inside the real tab*/
	i = 0;
	cumul = 0;
	while(i < 4){
		occur1[i] = 0;
		occur2[i] = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cumul = side1[i] + side2[i];
		if (!(cumul >= 3 && cumul <= 5))
			return (0);
		occur1[side1[i] - 1]++;
		occur2[side2[i] - 1]++;
		i++;
	}
	if (!check_occurencies(occur1) || !check_occurencies(occur2))
		return (0);
	return (1);
}

void	parse_arg(char *s, int *side1, int *side2) {
	int	i;
	int	index;
	
	i = 0;
	index = 0;
	while (s[i] != '\0' ) {
                while (s[i] != '\0' && s[i] == ' ')
                        i++;
		if (i < 7)
			side1[index] = s[i] - 48;
		else if (i < 15)
			side2[index] = s[i] - 48;

                while (s[i] != '\0' && s[i] >= '1' && s[i] <= '4')
                        i++;
		index++;
		if (i == 7 || i == 15)
			index = 0;
	}
}

void	show_tab(int **tab)
{
	int	row;
	int	col;
	char	_char;

	row = 0;
	while (row < 4) {
		col = 0;
		while (col < 4) {
			_char = tab[row][col] + 48;
			write(1, &_char, 1);
			write(1, " ", 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

void	init_tab(int **tab)
{
	int	row;
	int	col;

        row = 0;
        while (row < 4) {
		col = 0;
		while (col < 4) {
			tab[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	fill_tab(int **tab, int *side1, int *side2, int flip)
{
	int	col;
	int	row;

	col = 0;
	while (col < 4)
	{
		if (side1[col] == 4)
		{
			row = -1;
			while (++row < 4)
			{
				if (flip)
					tab[col][row] = row + 1;	
				else
					tab[row][col] = row + 1;
			}
		}
			
		col++;
	}
        while (col >= 0)
        {
                if (side2[col] == 4)
                {
                        row = 4;
                        while (--row >= 0)
			{
				if (flip)
                                        tab[col][row] = 4 - row;
                                else
                                        tab[row][col] = 4 - row;
			}
                }

                col--;
        }
}

int	main(int ac, char **av) {
	(void)av;
	if (ac == 2) {
        	int	**tab;
        	int	row;
        	//int	col;
		int	*colup;
		int	*coldown;
		int	*rowleft;
		int	*rowright;

		if (!is_arg_valid(av[1]))
		{
			print_error();
			return (0);
		}
		colup = (int*)malloc(sizeof(int) * 4);
		coldown = (int*)malloc(sizeof(int) * 4);
		rowleft = (int*)malloc(sizeof(int) * 4);
		rowright = (int*)malloc(sizeof(int) * 4);

		parse_arg(av[1], colup, coldown);
		parse_arg(av[1] + 16, rowleft, rowright);
		if (!is_parse_valid(colup, coldown)
				|| !is_parse_valid(rowleft, rowright))
		{
			free_sides(colup, coldown, rowleft, rowright);
                        print_error();
                        return (0);
		}
		if (!(tab = (int**)malloc(sizeof(int) * (4 * 4))))
		{
			free_sides(colup, coldown, rowleft, rowright);
			print_error();
			return (0);
		}
		row = 0;
		while (row < 4){
			if (!(tab[row] = (int*)malloc(sizeof(int) * 4)))
			{
				free_sides(colup, coldown, rowleft, rowright);
				free_tab(tab, row + 1);
			}
			row++;
		}

		init_tab(tab);
		fill_tab(tab, colup, coldown, 0);
		fill_tab(tab, rowleft, rowright, 1);
		fill_with_four(tab, colup, coldown, 0);
		fill_with_four(tab, rowleft, rowright, 1);

		show_tab(tab);
		free_tab(tab, 4);	
		free_sides(colup, coldown, rowleft, rowright);
	}
	else
		print_error();

	return (0);
}
