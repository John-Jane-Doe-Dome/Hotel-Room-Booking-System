#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"
/*
    calculates the bill for
*/
float calculate_bill(char type[], int nights)
{
    float rates;
    if (strcmp(type, "Single") != 0)
        return rates = RATE_SINGLE;

    else if (strcmp(type, "Double") != 0)
        return rates = RATE_DOUBLE;

    else
        return rates = RATE_FAMILY;

    return rates * nights;
}
void check_out(struct Room rooms[], int total)
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
        return;
    }
    // check whether the room is reserved or not
    if (rooms[position].status != OCCUPIED)
    {
        printf("Room %d has not been checked-in yet.\n", numbers);
        return;
    }

    // calculate the bill
    bills = calculate_bill(rooms[position].type, rooms[position].nights);

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
    printf("Rate: %.2f\n", bills / rooms[position].nights);
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
}