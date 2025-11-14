#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Struct: size, characters, and map
typedef struct {
    int lines, width;
    char empty, obstacle, full;
    char **map;
} Map;

// 2. Read map: Important things:
    // If we have filename, open. Else, stdin.
    // Scanf must be 4. If it's not 4, free, close, and null.
    // Remove \n
Map* read_map(char *filename) {
    FILE *file = filename ? fopen(filename, "r") : stdin;
    if (!file) return NULL;
    
    Map *map = malloc(sizeof(Map));
    if (fscanf(file, "%d %c %c %c\n", &map->lines, &map->empty, &map->obstacle, &map->full) != 4) {
        free(map);
        if (filename) fclose(file);
        return NULL;
    }
    
    map->map = malloc(map->lines * sizeof(char*));
    map->width = 0;
    
    for (int i = 0; i < map->lines; i++) {
        char *line = NULL;
        size_t len = 0;
        if (getline(&line, &len, file) == -1) {
            free(map);
            if (filename) fclose(file);
            return NULL;
        }
        
        // Remove newline
        int line_len = strlen(line);
        if (line[line_len - 1] == '\n') line[line_len - 1] = '\0';
        
        if (i == 0) map->width = strlen(line);
        else if (strlen(line) != map->width) {
            free(map);
            if (filename) fclose(file);
            return NULL;
        }
        
        map->map[i] = line;
    }
    
    if (filename) fclose(file);
    return map;
}

// 3. Validate: Boolean. Success: 1. Error: 0.
    // Checks if it haves content
    // Checks characters repeated
    // Checks character by caracter. It can only be empty or obstacle
int validate_map(Map *map) {
    if (!map || map->lines <= 0 || map->width <= 0) return 0;
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) return 0;
    
    for (int i = 0; i < map->lines; i++) {
        for (int j = 0; j < map->width; j++) {
            char c = map->map[i][j];
            if (c != map->empty && c != map->obstacle) return 0;
        }
    }
    return 1;
}

// Solve removed: i have my own algorytm

// 4. Print map. Easy. Just print it
void print_map(Map *map) {
    for (int i = 0; i < map->lines; i++) {
        printf("%s\n", map->map[i]);
    }
}

// 5. Free map: Free for every line, map box, and struct.
void free_map(Map *map) {
    if (!map) return;
    for (int i = 0; i < map->lines; i++) {
        free(map->map[i]);
    }
    free(map->map);
    free(map);
}

// 6. Process: Recives a file/stdin, and manage it: it calls all functions.
void process_file(char *filename) {
    Map *map = read_map(filename);
    if (!map || !validate_map(map)) {
        fprintf(stderr, "map error\n");
        if (map) free_map(map);
        return;
    }
    
    //solve_bsq(map);
    print_map(map);
    free_map(map);
}

// 7. Main: The if is important, bc the map can come by stdin or filename.
int main(int argc, char **argv) {
    if (argc == 1) {
        process_file(NULL);  // Read from stdin
    } else {
        for (int i = 1; i < argc; i++) { // Ithink it doesnt enter in the exam
            process_file(argv[i]);
        }
    }
    return 0;
}