#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 4


char* createLine(const char* text) {
    char* line = malloc(strlen(text) + 1);
    if (!line) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    strcpy(line, text);
    return line;
}


void insertLine(char*** lines, int* size, int* capacity, int index, const char* text) {
    if (index < 0 || index > *size) {
        printf("Invalid index for insertion.\n");
        return;
    }

   
    if (*size >= *capacity) {
        *capacity *= 2;
        char** temp = realloc(*lines, (*capacity) * sizeof(char*));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        *lines = temp;
    }

   
    memmove(&(*lines)[index + 1], &(*lines)[index], (*size - index) * sizeof(char*));

    (*lines)[index] = createLine(text);
    (*size)++;
}


void deleteLine(char** lines, int* size, int index) {
    if (index < 0 || index >= *size) {
        printf("Invalid index for deletion.\n");
        return;
    }

    free(lines[index]);

    memmove(&lines[index], &lines[index + 1], (*size - index - 1) * sizeof(char*));
    (*size)--;
}


void printAllLines(char** lines, int size) {
    if (size == 0) {
        printf("[Buffer is empty]\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}


void freeAll(char** lines, int size) {
    for (int i = 0; i < size; i++) {
        free(lines[i]);
    }
    free(lines);
}


char** shrinkToFit(char** lines, int size) {
    if (size == 0) return NULL;
    char** temp = realloc(lines, size * sizeof(char*));
    if (!temp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return temp;
}


void saveToFile(char** lines, int size, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        perror("File open error");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
    printf("Saved %d lines to %s\n", size, filename);
}


void loadFromFile(char*** linesPtr, int* size, int* capacity, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("File open error");
        return;
    }

    char buffer[1024];
    *size = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';

       
        if (*size >= *capacity) {
            *capacity *= 2;
            char** temp = realloc(*linesPtr, (*capacity) * sizeof(char*));
            if (!temp) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            *linesPtr = temp;
        }

        (*linesPtr)[*size] = createLine(buffer);
        (*size)++;
    }

    fclose(fp);
}

int main() {
    int size = 0;
    int capacity = INITIAL_CAPACITY;

    char** lines = malloc(capacity * sizeof(char*));
    if (!lines) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char input[1024];
    int choice;

    while (1) {
        printf("\nText Editor Menu:\n");
        printf("1. Insert line\n2. Delete line\n3. Print all lines\n4. Shrink to fit\n");
        printf("5. Save to file\n6. Load from file\n7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();  

        int index;
        char filename[256];

        switch (choice) {
            case 1:
                printf("Enter index to insert: ");
                scanf("%d", &index);
                getchar();
                printf("Enter line text: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                insertLine(&lines, &size, &capacity, index, input);
                break;
            case 2:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                getchar();
                deleteLine(lines, &size, index);
                break;
            case 3:
                printAllLines(lines, size);
                break;
            case 4:
                lines = shrinkToFit(lines, size);
                capacity = size > 0 ? size : INITIAL_CAPACITY;
                printf("Buffer shrunk to %d lines.\n", size);
                break;
            case 5:
                printf("Enter filename to save: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveToFile(lines, size, filename);
                break;
            case 6:
                printf("Enter filename to load: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';

                freeAll(lines, size);  
                lines = malloc(INITIAL_CAPACITY * sizeof(char*));
                if (!lines) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                size = 0;
                capacity = INITIAL_CAPACITY;

                loadFromFile(&lines, &size, &capacity, filename);
                break;
            case 7:
                freeAll(lines, size);
                printf("Exiting editor.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
