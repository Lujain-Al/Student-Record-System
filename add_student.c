#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float grade;
};

void addStudent(FILE *fp) {
    struct Student s;
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    printf("Enter student name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter student grade: ");
    scanf("%f", &s.grade);
    
    fwrite(&s, sizeof(struct Student), 1, fp);
    printf("Student added successfully!\n");
}

void displayStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("ID: %d | Name: %s | Grade: %.2f\n", s.id, s.name, s.grade);
    }
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("students.dat", "ab+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    do {
        printf("\n--- Student Record Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent(fp);
                break;
            case 2:
                displayStudents(fp);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 3);

    fclose(fp);
    return 0;
}
