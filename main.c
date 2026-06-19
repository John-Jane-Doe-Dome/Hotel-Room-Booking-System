#include <stdio.h>
#include "register.h"
int main()
{
    char CustomerName[100];
    char PhoneNumber[20];
    char CustomerEmail[100];

    // register the customer information
    registration(CustomerName, PhoneNumber, CustomerEmail);

    // Function Menu
    printf("\n==============================\n");
    printf("How can we help you today?\n");
    printf("1. View rooms\n2. Check-in\n3. Check-out\n4. View Booking\n5. Exit");
    printf("\n==============================\n");

    // each function task
    int choice;
    do
    {
        // for user to pick an action that they want to do
        printf("Please pick an action (1-5): ");
        scanf("%d", &choice);

        // ← flush leftover newline
        while (getchar() != '\n');
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("Thank you!");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 5);
    return 0;
}