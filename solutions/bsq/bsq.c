#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int lines, width;
    char empty, obstacle, full;
    char **map;
    int sq_dimension;
    int sq_x_start;
    int sq_y_start;
} Map;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

// Rellenar y imprimir mapa resuelto
void print_filled_map(Map *map)
{
    int x, y = 0;
    while (y < map->lines)
    {
        x = 0;
        while (x < map->width)
        {
            if (x >= map->sq_x_start && x < map->sq_x_start + map->sq_dimension &&
                y >= map->sq_y_start && y < map->sq_y_start + map->sq_dimension)
                fprintf(stdout, "%c", map->full);
            else
                fprintf(stdout, "%c", map->map[y][x]);
            x++;
        }
        y++;
        fprintf(stdout, "\n");
    }
}

// Verificar si un cuadrado es válido
int check_square(Map *map, int x_start, int y_start, int dimension)
{
    int y, x;
    y = 0;
    while (y < dimension)
    {
        x = 0;
        while (x < dimension)
        {
            if (map->map[y_start + y][x_start + x] == map->obstacle)
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

// Encontrar el cuadrado más grande
void find_bsq(Map *map)
{
    int square_len_size = map->width;
    int square_height_size = map->lines;
    int dimension = square_len_size > square_height_size ? square_height_size : square_len_size;
    int y, x;
    while (dimension > 0)
    {
        y = 0;
        while(y + dimension <= square_height_size)
        {
            x = 0;
            while(x + dimension <= square_len_size)
            {
                if(check_square(map, x, y, dimension) == 1)
                {
                    map->sq_dimension = dimension;
                    map->sq_x_start = x;
                    map->sq_y_start = y;
                    return ;
                }
                x++;
            }
            y++;
        }
        dimension--;
    }
    // Si no se encuentra ningún cuadrado, establecer valores por defecto
    map->sq_dimension = 0;
    map->sq_x_start = 0;
    map->sq_y_start = 0;
}

// Leer mapa + check 1a linea + guardar mapa + remove newline(s)
Map* read_map(char *filename) {
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if (!file)
        return NULL;
    // Leemos la primera linea y guardamos los valores correspondientes
    Map *map = malloc(sizeof(Map));
    if (fscanf(file, "%d %c %c %c\n", &map->lines, &map->empty, &map->obstacle, &map->full) != 4) {
        free(map);
        if (filename)
            fclose(file);
        return NULL;
    }
    map->map = malloc(map->lines * sizeof(char*));
    map->width = 0;
    int i = 0;
    // Recorremos linea por linea, guardandola en el mapa.
    while (i < map->lines) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, file) == -1) {
            free(map);
            if (filename)
                fclose(file);
            return NULL;
        }
        // Remove newline
        int line_len = ft_strlen(line);
        if (line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';
        if (i == 0)
            map->width = ft_strlen(line);
        else if (ft_strlen(line) != map->width) {
            free(map);
            if (filename)
                fclose(file);
            return NULL;
        }
        map->map[i] = line;
        i++;
    }
    if (filename)
        fclose(file);
    return map;
}

int validate_map(Map *map)
{
    int i = 0;
    // Comprobamos si hay map (estrucura mapa, proteccion) y si el mapa tiene contenido
    if (!map || map->lines <= 0 || map->width <= 0)
        return 0;
    // Comprobamos que los caracteres no sean duplicados
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
        return 0;
    // Check de que no haya caracteres diferentes a 'empty' y 'obst'
    while (i < map->lines) {
        int j = 0;
        while (j < map->width) {
            char c = map->map[i][j];
            if (c != map->empty && c != map->obstacle)
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

void free_map(Map *map) {
    int i = 0;
    if (!map)
        return;
    while (i < map->lines) {
        free(map->map[i]);
        i++;
    }
    free(map->map);
    free(map);
}

void process_file(char *filename) {
    Map *map = read_map(filename);
    if (!map || !validate_map(map)) {
        fprintf(stderr, "map error\n");
        if (map)
            free_map(map);
        return;
    }
    find_bsq(map);
    print_filled_map(map);
    free_map(map);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        process_file(NULL);  // stdin
    } else {
        int i = 1;
        while (i < argc) {
            process_file(argv[i]);
            i++;
        }
    }
    return 0;
}