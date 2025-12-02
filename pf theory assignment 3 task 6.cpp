#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 10
#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];          
    char membershipType[10]; 
    char registrationDate[11]; 
    char dob[11];              
    char interest[10];         
} Student;


Student* students = NULL;
int size = 0;
int capacity = INITIAL_CAPACITY;


void loadDatabase(const char* filename);
void saveDatabase(const char* filename);
int findStudentByID(int studentID);
void addStudent();
void updateStudent();
void deleteStudent();
void viewAllStudents();
void batchWiseReport();
void ensureCapacity();

int main() {
    students = malloc(capacity * sizeof(Student));
    if (!students) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    loadDatabase(FILENAME);

    int choice;
    while (1) {
        printf("\n IEEE/ACM Membership Manager \n");
        printf("1. Register a new student\n");
        printf("2. Update student membership/batch\n");
        printf("3. Delete a student\n");
        printf("4. View all students\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: viewAllStudents(); break;
            case 5: batchWiseReport(); break;
            case 6:
                saveDatabase(FILENAME);
                free(students);
                printf("Exiting program. Database saved.\n");
                exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}


void ensureCapacity() {
    if (size >= capacity) {
        capacity *= 2;
        Student* temp = realloc(students, capacity * sizeof(Student));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        students = temp;
    }
}


void loadDatabase(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        if (errno == ENOENT) return; 
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp) == 1) {
        ensureCapacity();
        students[size++] = temp;
    }

    fclose(fp);
}


void saveDatabase(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(students, sizeof(Student), size, fp);
    fclose(fp);
}


int findStudentByID(int studentID) {
    for (int i = 0; i < size; i++) {
        if (students[i].studentID == studentID) return i;
    }
    return -1;
}


void addStudent() {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    getchar();

    if (findStudentByID(s.studentID) != -1) {
        printf("Student ID already exists!\n");
        return;
    }

    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(s.batch, sizeof(s.batch), stdin);
    s.batch[strcspn(s.batch, "\n")] = '\0';

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, sizeof(s.membershipType), stdin);
    s.membershipType[strcspn(s.membershipType, "\n")] = '\0';

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
    s.registrationDate[strcspn(s.registrationDate, "\n")] = '\0';

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dob, sizeof(s.dob), stdin);
    s.dob[strcspn(s.dob, "\n")] = '\0';

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, sizeof(s.interest), stdin);
    s.interest[strcspn(s.interest, "\n")] = '\0';

    ensureCapacity();
    students[size++] = s;

    saveDatabase(FILENAME);
    printf("Student added successfully!\n");
}


void updateStudent() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    getchar();

    int index = findStudentByID(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Current Batch: %s, Membership Type: %s\n", students[index].batch, students[index].membershipType);

    printf("Enter new Batch (leave blank to keep current): ");
    char input[50];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) strcpy(students[index].batch, input);

    printf("Enter new Membership Type (leave blank to keep current): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) strcpy(students[index].membershipType, input);

    saveDatabase(FILENAME);
    printf("Student updated successfully!\n");
}


void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    getchar();

    int index = findStudentByID(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    size--;

    saveDatabase(FILENAME);
    printf("Student deleted successfully!\n");
}

// View all students
void viewAllStudents() {
    if (size == 0) {
        printf("No student records available.\n");
        return;
    }

    printf("\n All Student Records \n");
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Name: %s, Batch: %s, Membership: %s, Reg Date: %s, DOB: %s, Interest: %s\n",
               students[i].studentID, students[i].fullName, students[i].batch,
               students[i].membershipType, students[i].registrationDate,
               students[i].dob, students[i].interest);
    }
}


void batchWiseReport() {
    char batch[50];
    char interest[10];

    printf("Enter Batch to report (CS/SE/Cyber Security/AI): ");
    fgets(batch, sizeof(batch), stdin);
    batch[strcspn(batch, "\n")] = '\0';

    printf("Enter Interest to filter (IEEE/ACM/Both): ");
    fgets(interest, sizeof(interest), stdin);
    interest[strcspn(interest, "\n")] = '\0';

    printf("\n Batch-wise Report \n");
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(students[i].batch, batch) == 0 && strcmp(students[i].interest, interest) == 0) {
            printf("ID: %d, Name: %s, Membership: %s\n",
                   students[i].studentID, students[i].fullName, students[i].membershipType);
            found = 1;
        }
    }
    if (!found) printf("No records found for this filter.\n");
}
