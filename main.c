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
#include "register.h"
#include "viewreserveroom.h"
int main()
{
    // storage

    struct Room rooms[MAX_ROOMS];
    int total = 0;

    // customer information

    char CustomerName[100];
    char PhoneNumber[20];
    char CustomerEmail[100];

    // creates the room
    init_rooms(rooms, &total);

    // register the customer information
    registration(CustomerName, PhoneNumber, CustomerEmail);

    // Function Menu
    printf("\n==============================\n");
    printf("Welcome, %s \n", CustomerName);
    printf("How can we help you today?\n");

    // Menu
    int choice;
    char type[15];
    do
    {
        // for user to pick an action that they want to do
        printf("1. View rooms\n2. Book rooms\n3. View Booking\n4. Check-in\n5. Check-out\n6. Exit");
        printf("\n==============================\n");
        printf("Please pick an action (1-6): ");
        scanf("%d", &choice);

        // ← flush leftover newline
        while (getchar() != '\n')
            ;
        switch (choice)
        {
        case 1:
            display_all_rooms(rooms, total);
            break;
        case 2:
            book_room(rooms, total, CustomerName, PhoneNumber, CustomerEmail);
            break;
        case 3:
            view_booking(rooms, total);
            break;
        case 4:
            check_in(rooms, total);
            break;
        case 5:
            check_out(rooms, total);
            break;
        case 6:
            printf("Thank you %s!", CustomerName);
            break;
        default:
            printf("Invalid choice.\n");
            printf("1. View rooms\n2. Book rooms\n3. View Booking\n4. Check-in\n5. Check-out\n6. Exit");
            break;
        }
    } while (choice != 6);
    return 0;
}