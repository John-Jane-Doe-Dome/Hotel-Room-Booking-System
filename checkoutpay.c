#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"

void check_out(struct Room rooms[], int total, char name[], char phone[], char email[])
{
    float bills;
    int numbers;
    int position;
    printf("Enter your room number: ");
    scanf("%d", &numbers);
    while (getchar() != '\n')
        ;

    // finds the room
    position = find_room(rooms, total, numbers);

    // check whether the room actually exist
    if (position == -1)
    {
        printf("Room %d does not exist.\n", numbers);
        printf("==============================\n");
        return;
    }
    // check whether the room is checked-in, reserved, or not
    if (rooms[position].status != OCCUPIED)
    {
        if (rooms[position].status != RESERVED)
        {
            printf("Room %d has not been reserved yet.\n", numbers);
            printf("==============================\n");
            return;
        }
        else
        {
            printf("Room %d has not been checked-in yet.\n", numbers);
            printf("==============================\n");
            return;
        }
    }

    // verify that the person checking out matches the registered booking
    if (strcasecmp(name, rooms[position].guest) != 0 ||
        strcmp(phone, rooms[position].phone) != 0 ||
        strcasecmp(email, rooms[position].email) != 0)
    {
        printf("\nVerification failed. Your registered details do not match this booking.\n");
        printf("==============================\n");
        return;
    }

    // calculate the bill
    bills = rooms[position].price * rooms[position].nights;

    // printf the final bills
    printf("==============================\n");
    printf("   Final Bill\n");
    printf("==============================\n");
    printf("Guest: %s\n", rooms[position].guest);
    printf("Tel: %s\n", rooms[position].phone);
    printf("Email: %s\n", rooms[position].email);
    printf("Floor: %d\n", rooms[position].floors);
    printf("Room: %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Night: %d\n", rooms[position].nights);
    // FIX: print the stored per-night price directly instead of
    // dividing bills back by nights - avoids a needless float
    // round-trip and a possible division-by-zero if nights were ever 0.
    printf("Price per Night: %.2f\n", rooms[position].price);
    printf("Total: %.2f\n", bills);
    printf("==============================\n");
    printf("Thank you for staying with us!\n");
    printf("==============================\n\n");

    // then clears the rooms for future booking
    rooms[position].status = AVAILABLE;
    rooms[position].guest[0] = '\0';
    rooms[position].phone[0] = '\0';
    rooms[position].email[0] = '\0';
    rooms[position].nights = 0;
    // persist the updated room data to file
    save_rooms_to_file(rooms, total);
}