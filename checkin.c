#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"
void check_in(struct Room rooms[], int total)
{
    int numbers;
    int position;
    printf("Enter the number of the room you have booked: ");
    scanf("%d", &numbers);
    while (getchar() != '\n')
        ;

    position = find_room(rooms, total, numbers);

    if (position == -1)
    {
        printf("Room %d does not exist.\n", numbers);
        return;
    }

    if (rooms[position].status != RESERVED)
    {
        printf("Room %d has not been booked.\n", numbers);
        return;
    }

    rooms[position].status = OCCUPIED;

    printf("==============================\n");
    printf("   Check-in successful!\n");
    printf("==============================\n");
    printf("Guest: %s\n", rooms[position].guest);
    printf("Tel: %s\n", rooms[position].phone);
    printf("Email: %s\n", rooms[position].email);
    printf("Floor: %d\n", rooms[position].floors);
    printf("Room: %d (%s)\n", rooms[position].numbers, rooms[position].type);
    printf("Night: %d\n", rooms[position].nights);
    printf("==============================\n");
    printf("Please enjoy your stay!\n\n");
}