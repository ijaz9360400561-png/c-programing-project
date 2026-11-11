int main()
{
    int choice;
    int roll, marks[5];
    int total = 0;
    float average;
    char name[50];
    char grade[10];
    char result[10];

    do
    {
        printf("\nSTUDENT MARKS MANAGEMENT SYSTEM\n");
        printf("--------------------------------\n");
        printf("1. Enter Student Details\n");
        printf("2. Calculate Result\n");
        printf("3. Display Result\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &roll);

                printf("Enter Student Name: ");
                scanf("%49s", name);

                for(int i = 0; i < 5; i++)
                {
                    printf("Enter Subject %d Mark: ", i + 1);
                    scanf("%d", &marks[i]);
                }

                total = 0;
                for(int i = 0; i < 5; i++)
                {
                    total += marks[i];
                }

                average = total / 5.0;

                if(average >= 90)
                    grade[0] = 'A';
                else if(average >= 80)
                    grade[0] = 'B';
                else if(average >= 70)
                    grade[0] = 'C';
                else if(average >= 60)
                    grade[0] = 'D';
                else
                    grade[0] = 'F';

                grade[1] = '\0';

                if(average >= 40)
                    sprintf(result, "PASS");
                else
                    sprintf(result, "FAIL");

                break;

            case 2:
                total = 0;

                for(int i = 0; i < 5; i++)
                {
                    total += marks[i];
                }

                average = total / 5.0;

                printf("\nResult Calculated Successfully!\n");
                break;

            case 3:
                printf("\nSTUDENT RESULT\n");
                printf("--------------\n");
                printf("Roll Number : %d\n", roll);
                printf("Name        : %s\n", name);
                printf("Total       : %d\n", total);
                printf("Average     : %.2f\n", average);
                printf("Grade       : %s\n", grade);
                printf("Result      : %s\n", result);
                break;

            case 4:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 4);

    return 0;
}