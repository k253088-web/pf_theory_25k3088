#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int last_used;   
};

int findBook(struct Book *shelf, int capacity, int id) {
    for (int i = 0; i < capacity; i++) {
        if (shelf[i].id == id)
            return i;   
    }
    return -1; 
}

int findLRU(struct Book *shelf, int capacity) {
    int index = 0;
    for (int i = 1; i < capacity; i++) {
        if (shelf[i].last_used < shelf[index].last_used)
            index = i;
    }
    return index;  
}

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];

    
    for (int i = 0; i < capacity; i++) {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].last_used = 0;
    }

    int time_counter = 1;  

    while (Q--) {
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            int id, pop;
            scanf("%d %d", &id, &pop);

            int pos = findBook(shelf, capacity, id);

            if (pos != -1) {  
               
                shelf[pos].popularity = pop;
                shelf[pos].last_used = time_counter++;
            }
            else { 
               
                int emptyIndex = -1;
                for (int i = 0; i < capacity; i++) {
                    if (shelf[i].id == -1) {
                        emptyIndex = i;
                        break;
                    }
                }

                if (emptyIndex != -1) {
                    
                    shelf[emptyIndex].id = id;
                    shelf[emptyIndex].popularity = pop;
                    shelf[emptyIndex].last_used = time_counter++;
                }
                else {
                    
                    int removeIndex = findLRU(shelf, capacity);
                    shelf[removeIndex].id = id;
                    shelf[removeIndex].popularity = pop;
                    shelf[removeIndex].last_used = time_counter++;
                }
            }
        }
        else if (strcmp(op, "ACCESS") == 0) {
            int id;
            scanf("%d", &id);

            int pos = findBook(shelf, capacity, id);

            if (pos == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", shelf[pos].popularity);
                shelf[pos].last_used = time_counter++;
            }
        }
    }

    return 0;
}
