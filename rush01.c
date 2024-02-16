#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	prevent_leaks(char **tab) {
	int	i;

	i = -1;
	while (tab[++i] != 0)
		free(tab[i]);
	free(tab);
}

int	main(int ac, char **av) {
	char	**tab;
	int	row;
	int	col;

	if (ac == 2) {
		if (!(tab = (char**)malloc(sizeof(char*) * (4 + 1))))
		{
			write(1, "Error", 5);
			return (0);
		}
		row = 0;
		while (row < 4) {
			tab[row] = (char*)malloc(sizeof(char) * (4 + 1));
			row++;
		}
		tab[row] = 0;
		//printf("ici c'est bon1\n");
		row = 0;
		while (row < 4) {
			col = 0;
			while (col < 4) {
				tab[row][col] = '1';
				printf("row : %d, col: %d\n", row, col);
				col++;
				
			}
			tab[row][col] = '\0';
			row++;
		}
		//printf("ici c'est bon2\n");	
		row = 0;
		col = 0;
		while (tab[row] != 0) {
			while (tab[row][col] != '\0') {
				write(1, &tab[row][col], 1);
				write(1, " ", 1);
				col++;
			}
			write(1, "\n", 1);
			row++;
		}
	}
	prevent_leaks(tab);
	return (0);
}
