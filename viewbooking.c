#include <stdio.h>
#include <string.h>
#include "viewreserveroom.h"

/*
    this function will show the booking
    details of a room
    so that the customer can check their booking after they have book
*/

// FIX: now takes the customer's registered name/phone/email and verifies
// them against the room record, matching check_in/check_out. Previously
// any customer could look up any room number and see another guest's
// name, phone number, and email.
void view_booking(struct Room rooms[], int total, char name[], char phone[], char email[])
{
    int numbers;
    int position;
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
        printf("Room %d doesn't exist.\n", numbers);
        printf("==============================\n");
        return;
    }

    // check whether the room have an active booking or not
    if (rooms[position].status == AVAILABLE)
    {
        printf("The room %d has no active booking.\n", numbers);
        printf("==============================\n");
        return;
    }

    // verify that the person viewing matches the registered booking
    if (strcasecmp(name, rooms[position].guest) != 0 ||
        strcmp(phone, rooms[position].phone) != 0 ||
        strcasecmp(email, rooms[position].email) != 0)
    {
        printf("\nVerification failed. Your registered details do not match this booking.\n");
        printf("==============================\n");
        return;
    }

    total_bill = rooms[position].price * rooms[position].nights;

    /* ── print the booking details ── */
    printf("\n==============================\n");
    printf("       Booking Details\n");
    printf("==============================\n");
    printf("Guest  : %s\n", rooms[position].guest);
    printf("------------------------------\n");
    printf("Floor  : %d\n", rooms[position].floors);
    printf("Room   : %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Nights : %d\n", rooms[position].nights);
    printf("Rate   : $%.2f / night\n", rooms[position].price);
    printf("Total  : $%.2f\n", total_bill);
    printf("------------------------------\n");

    /* print status */
    if (rooms[position].status == RESERVED)
        printf("Status : Reserved (not yet checked in)\n");
    else
        printf("Status : Occupied (currently checked in)\n");

    printf("==============================\n\n");
}