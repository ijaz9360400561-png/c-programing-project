#include <stdio.h>

struct Student {
    int rollno;
    char name[50];
    float cutoff;
    char city[50];
    char dream[100];
};

int main() {
    struct Student s[100];
    int n, i;

    printf("STUDENT DETAILS MANAGEMENT SYSTEM\n");

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid student count!\n");
        return 0;
    }

    // Collect student details
    for (i = 0; i < n; i++) {
        printf("\nEnter details of Student %d\n", i + 1);

        printf("Enter Roll Number: ");
        scanf("%d", &s[i].rollno);

        printf("Enter Name: ");
        scanf(" %49[^\n]", s[i].name);

        printf("Enter Cut-off Mark: ");
        scanf("%f", &s[i].cutoff);

        printf("Enter City: ");
        scanf(" %49[^\n]", s[i].city);

        printf("Enter Dream: ");
        scanf(" %99[^\n]", s[i].dream);
    }

    // Display student details
    printf("\n===== STUDENT DETAILS =====\n");

    for (i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Roll Number : %d\n", s[i].rollno);
        printf("Name        : %s\n", s[i].name);
        printf("Cut-off Mark: %.2f\n", s[i].cutoff);
        printf("City        : %s\n", s[i].city);
        printf("Dream       : %s\n", s[i].dream);
    }

    return 0;
}