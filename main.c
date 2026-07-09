#include <stdio.h>
#include <string.h>
#include "admincontrols.c"
#include "booking.c"
#include "checkin.c"
#include "checkoutpay.c"
#include "register.c"
#include "viewbooking.c"
#include "viewreserveroom.c"

int main()
{
    // storage
    struct Room rooms[MAX_ROOMS];
    int total = 0;

    // customer information
    char CustomerName[100];
    char PhoneNumber[20];
    char CustomerEmail[100];

    // FIX: load previously saved hotel data if it exists, instead of
    // unconditionally resetting to defaults every single run. Only
    // fall back to init_rooms() if there's no file or it's empty.
    if (!load_rooms_from_file(rooms, &total) || total == 0)
    {
        printf("No hotel data found.\nLoading default hotel configuration...\n");
        init_rooms(rooms, &total);
        save_rooms_to_file(rooms, total);
    }

    char role[20];
    // FIX: the original "while (!role)" / "while (role != 2)" compared
    // a pointer (the decayed array) to an integer, which is always
    // false/true regardless of what the user typed - the loop either
    // never exited on real input or exited unconditionally after one
    // pass. Replaced with an explicit "done" flag and real handling for
    // admin / customer / exit.
    int done = 0;
    do
    {
        printf("\n===================================\n");
        printf("Are you logging in as an 'Admin' or 'Customer'?\nIf neither, type 'exit' to quit the program\n");
        printf("===================================\n");
        printf("Logging as: ");
        scanf("%19s", role); // FIX: width limit to prevent overflowing role[20]
        while (getchar() != '\n')
            ;

        if (strcasecmp(role, "admin") == 0)
        {
            char password[20];
            printf("Enter admin password: ");
            scanf("%19s", password); // FIX: width limit
            while (getchar() != '\n')
                ;

            if (strcmp(password, Admin_Password) == 0)
            {
                // function menu for admin
                // FIX: pass &total so room-count changes from
                // setup_hotel() (inside admin_menu) reach main().
                admin_menu(rooms, &total);
            }
            else
            {
                printf("Incorrect password. Access denied.\n");
            }
        }
        else if (strcasecmp(role, "customer") == 0)
        {
            done = 1;
        }
        else if (strcasecmp(role, "exit") == 0)
        {
            printf("Goodbye!\n");
            return 0;
        }
        else
        {
            printf("Invalid entry. Please type 'Admin', 'Customer', or 'exit'.\n");
        }
    } while (!done);

    // register the customer information
    registration(CustomerName, PhoneNumber, CustomerEmail);

    // Function Menu
    printf("\n==============================\n");
    printf("Welcome, %s \n", CustomerName);
    printf("How can we help you today?\n");

    // Menu
    int choice;
    do
    {
        // for user to pick an action that they want to do
        printf("1. View rooms\n2. Book rooms\n3. View Booking\n4. Check-in\n5. Check-out\n6. Exit");
        printf("\n==============================\n");
        printf("Please pick an action (1-6): ");
        scanf("%d", &choice);

        // flush leftover newline
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
            // FIX: view_booking now requires identity verification
            view_booking(rooms, total, CustomerName, PhoneNumber, CustomerEmail);
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