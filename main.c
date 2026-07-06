#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
#include "register.h"
#include "viewreserveroom.h"

#define Admin_Password "1234"

=======
#include "admincontrols.c"
#include "booking.c"
#include "checkin.c"
#include "checkoutpay.c"
#include "register.c"
#include "viewbooking.c"
#include "viewreserveroom.c"

>>>>>>> Bot
int main()
{
    // storage

    struct Room rooms[MAX_ROOMS];
    int total = 0;

    // customer information

    char CustomerName[100];
    char PhoneNumber[20];
    char CustomerEmail[100];
    load_rooms_from_file(rooms, &total);

    // creates the room
<<<<<<< HEAD
    if (!load_rooms_from_file(rooms, &total))
    {
        printf("No custom hotel setup found. Loading default hotel configuration...\n");
=======
    if(total == 0){
        printf("No hotel data found.\nLoading default hotel configuration...\n");
>>>>>>> Bot
        init_rooms(rooms, &total);
        save_rooms_to_file(rooms, total);
    }

<<<<<<< HEAD
    int role;
    do
    {
        printf("\n===================================\n");
        printf("Are you logging in as (1. Admin 2. Customer 3. Exit) \n");
        printf("===================================\n");
        printf("logging as: ");
        scanf("%d", &role);
        while (getchar() != '\n')
            ;
        switch (role)
        {
        case 1:
        {
            char password[20];
            printf("Enter admin password: ");
            scanf("%s", password);
            while (getchar() != '\n')
                ;

            if (strcmp(password, Admin_Password) == 0)
            {
                // FIX #8: pass total by reference so a hotel resize
                // inside admin_menu/setup_hotel is reflected here too
                admin_menu(rooms, &total);
            }
            else
            {
                printf("Incorrect password. Access denied.\n");
            }
        }
        break;
        case 2:
            break;
        case 3:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Please select 1, 2, or 3.\n");
            break;
=======
    char role[20];
do{
    printf("\n===================================\n");
    printf("Are you logging in as an 'Admin' or 'Customer'?\nIf niether, type 'exit' to quit the program\n");
    printf("===================================\n");
    printf("Logging as: ");
    scanf("%s", role);
    while (getchar() != '\n');

    if (strcasecmp(role, "admin") == 0) {
        char password[20];
        printf("Enter admin password: ");
        scanf("%s", password);
        while (getchar() != '\n');

        if (strcmp(password, Admin_Password) == 0) {
            // function menu for admin
            admin_menu(rooms, total);
        } else {
<<<<<<< HEAD
            printf("Incorrect password. Access denied.\n");
>>>>>>> Bot
=======
            printf("Incorrect password. Access denied.\n"); // goes back to ask who we're logging in as
>>>>>>> Vichea's-Draft
        }
    }
    else if (strcasecmp(role, "customer") == 0) {
        break; // exit the loop and proceed to customer registration
    }
    else if (strcasecmp(role, "exit") == 0) {
        printf("Exiting the program.\n");
        return 0;
    }
    else {
        printf("Invalid choice. Please type admin, customer, or exit.\n");
    }

} while (strcasecmp(role, "exit") != 0);

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
        while (getchar() != '\n');
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
            check_in(rooms, total, CustomerName, PhoneNumber, CustomerEmail);
            break;
        case 5:
            check_out(rooms, total, CustomerName, PhoneNumber, CustomerEmail);
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
