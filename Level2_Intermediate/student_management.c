#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"
#define NAME_LEN 50

typedef struct {
    int id;
    char name[NAME_LEN];
    float gpa;
    int age;
} Student;

Student students[MAX_STUDENTS];
int count = 0;

void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        perror("Error saving file");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
    printf("Records saved to %s\n", FILE_NAME);
}

void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No existing file found. Starting fresh.\n");
        return;
    }
    fread(&count, sizeof(int), 1, fp);
    fread(students, sizeof(Student), count, fp);
    fclose(fp);
    printf("Loaded %d records from file.\n", count);
}

void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("Database full!\n");
        return;
    }
    Student s;
    printf("Enter ID: "); scanf("%d", &s.id);
    while (getchar()!='\n');
    printf("Enter Name: "); fgets(s.name, NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Age: "); scanf("%d", &s.age);
    printf("Enter GPA: "); scanf("%f", &s.gpa);
    
    // check duplicate ID
    for (int i=0;i<count;i++) if (students[i].id==s.id){ printf("ID already exists!\n"); return; }
    
    students[count++] = s;
    saveToFile();
    printf("Student added successfully!\n");
}

void displayStudents() {
    if (count==0){ printf("No records.\n"); return; }
    printf("\n%-6s %-20s %-5s %-5s\n", "ID", "Name", "Age", "GPA");
    printf("-------------------------------------------\n");
    for (int i=0;i<count;i++) {
        printf("%-6d %-20s %-5d %-5.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

void deleteStudent() {
    int id; printf("Enter ID to delete: "); scanf("%d",&id);
    for (int i=0;i<count;i++) {
        if (students[i].id==id){
            for (int j=i;j<count-1;j++) students[j]=students[j+1];
            count--;
            saveToFile();
            printf("Deleted ID %d\n", id);
            return;
        }
    }
    printf("ID %d not found.\n", id);
}

void updateStudent() {
    int id; printf("Enter ID to update: "); scanf("%d",&id);
    for (int i=0;i<count;i++) {
        if (students[i].id==id){
            while(getchar()!='\n');
            printf("Enter new Name (current: %s): ", students[i].name);
            fgets(students[i].name, NAME_LEN, stdin);
            students[i].name[strcspn(students[i].name, "\n")]=0;
            printf("Enter new Age (current: %d): ", students[i].age);
            scanf("%d",&students[i].age);
            printf("Enter new GPA (current: %.2f): ", students[i].gpa);
            scanf("%f",&students[i].gpa);
            saveToFile();
            printf("Updated successfully.\n");
            return;
        }
    }
    printf("ID not found.\n");
}

void searchStudent() {
    int id; printf("Enter ID to search: "); scanf("%d",&id);
    for (int i=0;i<count;i++) {
        if (students[i].id==id){
            printf("Found: ID=%d Name=%s Age=%d GPA=%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
            return;
        }
    }
    printf("Not found.\n");
}

int main() {
    loadFromFile();
    int choice;
    printf("=== Simple Student Management System - Level 2 Task 1 ===\n");
    do {
        printf("\n1. Add Student (Create)\n2. Display All (Read)\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\nChoice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while(choice!=6);
    return 0;
}
