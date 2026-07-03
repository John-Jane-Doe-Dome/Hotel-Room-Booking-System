#include <stdio.h>
#include <string.h>
#include "register.c"
#include "viewreserveroom.c"
#include "viewbooking.c"
#include "checkin.c"
#include "checkoutpay.c"
#include "booking.c"

#define Admin_Password "1234"

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

    int role;
    do {
        printf("\n===================================\n");
        printf("Are you logging is as: \n1. Admin\n2. Customer\n");
        printf("===================================\n");
        printf("please pick (1-2): \n");
        scanf("%d",&role);
        while(getchar() != '\n');
        switch (role) 
        {
            case 1:{
            char password[20];
                printf("Enter admin password: ");
                scanf("%s", password);
                while(getchar() != '\n');
                
                if (strcmp(password, Admin_Password) == 0) {
                    admin_menu(rooms, total);
                }
                else
                {
                    printf("Incorrect password. Access denied.\n");
                }
            }
                break;
            case 2:
                break;
            default:
                printf("Invalid choice. Please select 1 or 2.\n");
                break;
        }
    } while (role != 2);
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