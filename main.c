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
    load_rooms_from_file(rooms, &total);

    // creates the room
    if(total == 0){
        printf("No hotel data found.\nLoading default hotel configuration...\n");
        init_rooms(rooms, &total);
        save_rooms_to_file(rooms, total);
    }

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
            printf("Incorrect password. Access denied.\n");
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