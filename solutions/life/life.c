#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	// 1. Comprobacion y parseo
	if(ac != 4)
		return 1;
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iter = atoi(av[3]);

	// 2. Creacion de grid vacia
	char grid[height][width];
	int h = 0, w = 0;
	while(h < height){
		w = 0;
		while(w < width){
			grid[h][w] = ' ';
			w++;	
		}
		h++;
	}

	// 3. Rellenamos la grid inicial
	char c;
	int xp = 0, yp = 0;
	bool draw = false;
	while(read(0, &c, 1) > 0){
		if(c == 'w')
			yp--;
		else if(c == 's')
			yp++;
		else if(c == 'a')
			xp --;
		else if(c == 'd')
			xp ++;
		else if(c == 'x')
			draw = !draw;
		else if(c == '\n')
			break;
		else
			return 1;
		
		// Comprobamos que estemos en el grid
		if(yp < 0 || yp >= height || xp < 0 || xp >= width)
			return 1;
		if(draw)
			grid[yp][xp] = '0';
	}

	// 4. Iteraciones, height, width, y 2 iteraciones mas para revisar los vecinos.
	char new_grid[height][width];
	for(int i = 0; i < iter; i++){ // Iters
		for(int y = 0; y < height; y++){ // Height
			for(int x = 0; x < width; x++){ // Width
				int n_alive = 0;
				for(int dy = -1; dy < 2; dy++){
					for(int dx = -1; dx < 2; dx++){
						// 5. Buscamos vivos cerca
						int ny = y + dy;
						int nx = x + dx;
						if(ny != y || nx != x){ // Comprobamos que no sea la misma celula
							if(ny < height && nx < width && ny >= 0 && nx >= 0){
								if(grid[ny][nx] == '0')
									n_alive ++;
							}
						}
					}
				}
				// 6. Comprobamos si la celula esta viva o muerta
				if(n_alive == 3 || (grid[y][x] == '0' && n_alive == 2))
					new_grid[y][x] = '0';
				else
					new_grid[y][x] = ' ';
			}
		}
		// 7. Copiamos la grid nueva a la grid actual
		h = 0;
		w = 0;
		while(h < height){
			w = 0;
			while(w < width){
				grid[h][w] = new_grid[h][w];
				w++;
			}
			h++;
		}
	}

	// 8. Imprimimos la grid final
	h = 0;
	w = 0;
	while(h < height){
		w = 0;
		while(w < width){
			write(1, &grid[h][w], 1);
			w++;
		}
		write(1, "\n", 1);
		h++;
	}
	return 0;
}
