#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIN_FILE "students.dat"
#define TEXT_FILE "students.txt"

struct Student {
    int roll;
    char name[50];
    char department[30];
    int year;
    float marks;
    char grade[5];
};

static int operationCount = 0;

// Calculate grade
void calculateGrade(struct Student *s) {
    if (s->marks >= 90)
        strcpy(s->grade, "A+");
    else if (s->marks >= 80)
        strcpy(s->grade, "A");
    else if (s->marks >= 70)
        strcpy(s->grade, "B");
    else if (s->marks >= 60)
        strcpy(s->grade, "C");
    else if (s->marks >= 50)
        strcpy(s->grade, "D");
    else
        strcpy(s->grade, "F");
}

// Increase memory capacity
int increaseCapacity(struct Student **s, int *capacity) {
    int newCapacity = (*capacity) * 2;

    struct Student *temp =
        realloc(*s, newCapacity * sizeof(struct Student));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }

    *s = temp;
    *capacity = newCapacity;
    return 1;
}

// Load records from binary file
int loadRecords(struct Student **s, int *capacity) {
    FILE *fp = fopen(BIN_FILE, "rb");
    int count = 0;

    if (fp == NULL)
        return 0;

    struct Student temp;

    while (fread(&temp, sizeof(struct Student), 1, fp) == 1) {
        if (count == *capacity) {
            if (!increaseCapacity(s, capacity)) {
                fclose(fp);
                return count;
            }
        }

        (*s)[count++] = temp;
    }

    fclose(fp);
    return count;
}

// Save records to binary and text files
void saveRecords(struct Student s[], int count) {
    FILE *fp = fopen("students.tmp", "wb");

    if (fp == NULL) {
        printf("Unable to save binary file!\n");
        return;
    }

    if (fwrite(s, sizeof(struct Student), count, fp) != (size_t)count) {
        printf("Error writing binary file!\n");
        fclose(fp);
        remove("students.tmp");
        return;
    }

    fclose(fp);

    remove(BIN_FILE);

    if (rename("students.tmp", BIN_FILE) != 0) {
        printf("Error replacing binary file!\n");
        return;
    }

    // Save records in text format
    fp = fopen(TEXT_FILE, "w");

    if (fp == NULL) {
        printf("Unable to create text file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d|%s|%s|%d|%.2f|%s\n",
                s[i].roll, s[i].name,
                s[i].department, s[i].year,
                s[i].marks, s[i].grade);
    }

    fclose(fp);
}

// Add student
void addStudent(struct Student **s, int *count, int *capacity) {
    if (*count == *capacity) {
        if (!increaseCapacity(s, capacity))
            return;
    }

    struct Student *p = &(*s)[*count];

    printf("\nEnter Roll Number: ");
    scanf("%d", &p->roll);

    for (int i = 0; i < *count; i++) {
        if ((*s)[i].roll == p->roll) {
            printf("Roll number already exists!\n");
            return;
        }
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", p->name);

    printf("Enter Department: ");
    scanf(" %29[^\n]", p->department);

    printf("Enter Year: ");
    scanf("%d", &p->year);

    printf("Enter Marks: ");
    scanf("%f", &p->marks);

    if (p->marks < 0 || p->marks > 100) {
        printf("Invalid marks!\n");
        return;
    }

    calculateGrade(p);

    (*count)++;
    saveRecords(*s, *count);

    operationCount++;
    printf("\nStudent added successfully!\n");
}

// Display all students
void displayStudents(struct Student s[], int count) {
    if (count == 0) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n------ STUDENT RECORDS ------\n");

    for (int i = 0; i < count; i++) {
        printf("\nRoll Number : %d", s[i].roll);
        printf("\nName        : %s", s[i].name);
        printf("\nDepartment  : %s", s[i].department);
        printf("\nYear        : %d", s[i].year);
        printf("\nMarks       : %.2f", s[i].marks);
        printf("\nGrade       : %s\n", s[i].grade);
    }
}

// Search student
void searchStudent(struct Student s[], int count) {
    int roll, found = 0;

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", s[i].name);
            printf("Department: %s\n", s[i].department);
            printf("Year: %d\n", s[i].year);
            printf("Marks: %.2f\n", s[i].marks);
            printf("Grade: %s\n", s[i].grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Update student
void updateStudent(struct Student s[], int count) {
    int roll, found = 0;

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (s[i].roll == roll) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", s[i].name);

            printf("Enter New Department: ");
            scanf(" %29[^\n]", s[i].department);

            printf("Enter New Year: ");
            scanf("%d", &s[i].year);

            printf("Enter New Marks: ");
            scanf("%f", &s[i].marks);

            if (s[i].marks < 0 || s[i].marks > 100) {
                printf("Invalid marks! Update cancelled.\n");
                return;
            }

            calculateGrade(&s[i]);
            found = 1;
            saveRecords(s, count);

            printf("\nRecord updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Delete student
void deleteStudent(struct Student s[], int *count) {
    int roll, found = 0;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < *count; i++) {
        if (s[i].roll == roll) {
            for (int j = i; j < *count - 1; j++) {
                s[j] = s[j + 1];
            }

            (*count)--;
            found = 1;
            saveRecords(s, *count);

            printf("\nRecord deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Count students
void countStudents(int count) {
    printf("\nTotal Number of Students: %d\n", count);
}

// Filter students by marks
void filterStudents(struct Student s[], int count) {
    float limit;
    int found = 0;

    printf("\nEnter Marks Limit: ");
    scanf("%f", &limit);

    printf("\nStudents scoring above %.2f:\n", limit);

    for (int i = 0; i < count; i++) {
        if (s[i].marks > limit) {
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
                   s[i].roll, s[i].name, s[i].marks);
            found = 1;
        }
    }

    if (!found)
        printf("No matching students found!\n");
}

// Read and display text file using fscanf
void displayTextFile(void) {
    FILE *fp = fopen(TEXT_FILE, "r");

    if (fp == NULL) {
        printf("\nText file not found!\n");
        return;
    }

    struct Student temp;
    int found = 0;

    printf("\n------ TEXT FILE RECORDS ------\n");

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%d|%f|%4s\n",
                  &temp.roll, temp.name, temp.department,
                  &temp.year, &temp.marks, temp.grade) == 6) {

        printf("%d | %s | %s | %d | %.2f | %s\n",
               temp.roll, temp.name, temp.department,
               temp.year, temp.marks, temp.grade);

        found = 1;
    }

    if (!found)
        printf("No records in text file.\n");

    fclose(fp);
}

// Main function
int main() {
    int choice;
    int count = 0;
    int capacity = 2;

    // Allocate memory using calloc
    struct Student *students =
        calloc(capacity, sizeof(struct Student));

    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    count = loadRecords(&students, &capacity);

    do {
        printf("\n\n================================");
        printf("\n STUDENT RECORD MANAGEMENT");
        printf("\n================================");
        printf("\n1. Add Student");
        printf("\n2. Display All Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Count Total Students");
        printf("\n7. Filter Students by Marks");
        printf("\n8. Display Text File");
        printf("\n9. Exit");
        printf("\n================================");

        printf("\nEnter Your Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addStudent(&students, &count, &capacity);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                updateStudent(students, count);
                break;

            case 5:
                deleteStudent(students, &count);
                break;

            case 6:
                countStudents(count);
                break;

            case 7:
                filterStudents(students, count);
                break;

            case 8:
                displayTextFile();
                break;

            case 9:
                saveRecords(students, count);
                printf("\nThank You! Program Closed.\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 9);

    // Release dynamically allocated memory
    free(students);

    printf("Memory released successfully!\n");

    return 0;
}