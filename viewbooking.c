#include <stdio.h>
#include <string.h>
#include "viewreserveroom.h"

/*
    this function will show the booking
    details of a room
    so that the customer can check their booking after they have book
*/

void view_booking(struct Room rooms[], int total)
{
    int numbers;
    int position;
    float rate;
    float total_bill;

    // ask the user for the room number that they have booked
    printf("Enter your room number: ");
    scanf("%d", &numbers);
    while (getchar() != '\n')
        ;

    // find the position of the rooms
    position = find_room(rooms, total, numbers);

    // check whether the room actually exist or not
    if (position == -1)
    {
        printf("The room doesn't exist.");
        return;
    }

    // check whether the room have an active booking or not
    if (rooms[position].status == AVAILABLE)
    {
        // FIX #4: "&d" was a literal typo instead of the "%d" format specifier
        printf("The room %d has no active booking.\n", numbers);
        return;
    }
    /* ── calculate rate and total bill ── */
    if (strcmp(rooms[position].type, "Single") == 0)
        rate = RATE_SINGLE;
    else if (strcmp(rooms[position].type, "Double") == 0)
        rate = RATE_DOUBLE;
    else
        rate = RATE_FAMILY;

    total_bill = rate * rooms[position].nights;

    /* ── print the booking details ── */
    printf("\n==============================\n");
    printf("       Booking Details\n");
    printf("==============================\n");
    printf("Guest  : %s\n", rooms[position].guest);
    printf("Phone  : %s\n", rooms[position].phone);
    printf("Email  : %s\n", rooms[position].email);
    printf("------------------------------\n");
    printf("Floor  : %d\n", rooms[position].floors);
    printf("Room   : %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Nights : %d\n", rooms[position].nights);
    printf("Rate   : $%.2f / night\n", rate);
    printf("Total  : $%.2f\n", total_bill);
    printf("------------------------------\n");

    /* print status */
    if (rooms[position].status == RESERVED)
        printf("Status : Reserved (not yet checked in)\n");
    else
        printf("Status : Occupied (currently checked in)\n");

    printf("==============================\n\n");
}