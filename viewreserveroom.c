#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "viewreserveroom.h"

/*
 this is the setup of the rooms
 each floors has 10 rooms
 the first 5 rooms will be single
 the next 3 rooms will be double
 the last 2 is fami
*/

void init_rooms(struct Room rooms[], int *total)
{
    int floors;
    int slot;
    *total = 0;

    // go through each floors
    for (floors = 1; floors <= FLOORS; floors++)
    {

        // go through each room in the floor
        for (slot = 1; slot <= ROOMS_PER_FLOORS; slot++)
        {
            rooms[*total].numbers = (floors * 100) + slot;
            rooms[*total].floors = floors;

            // rooms type
            // the . is for it to call the variables from the data structures
            if (slot <= 5)
            {
                strcpy(rooms[*total].type, "Single");
                rooms[*total].price = RATE_SINGLE;
            }
            else if (slot <= 8)
            {
                strcpy(rooms[*total].type, "Double");
                rooms[*total].price = RATE_DOUBLE;
            }
            else
            {
                strcpy(rooms[*total].type, "Family");
                rooms[*total].price = RATE_FAMILY;
            }
            rooms[*total].status = AVAILABLE;
            rooms[*total].guest[0] = '\0';
            rooms[*total].phone[0] = '\0';
            rooms[*total].email[0] = '\0';
            rooms[*total].nights = 0;

            (*total)++;
        }
    }
}

/*
    declaring the room status
*/

char *status_word(int status)
{
    if (status == AVAILABLE)
    {
        return "Available";
    }
    if (status == RESERVED)
    {
        return "Reserved";
    }
    if (status == OCCUPIED)
    {
        return "Occupied";
    }
    return "Unknown";
}

/*
    displaying all rooms in a simple table format
*/

void display_all_rooms(struct Room rooms[], int total)
{
    printf("---------------------------------------\n");
    printf("%-6s %-6s %-8s %-12s %-20s\n", "Room", "Floor", "Type", "Status", "Guest");
    printf("---------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("%-6d %-6d %-8s %-12s",
               rooms[i].numbers,
               rooms[i].floors,
               rooms[i].type,
               status_word(rooms[i].status));
        // only shows a name if the room is occupied
        if (rooms[i].status == AVAILABLE)
        {
            printf("-\n");
        }
        else
        {
            printf("%s\n", rooms[i].guest);
        }
    }
    printf("---------------------------------------\n\n");
}

/*
    print information of the room that match the type,
    and are available to book
*/

void display_available_room(struct Room rooms[], int total, char type[])
{
    int found = 0;
    printf("Available %s rooms: \n", type);
    printf("-----------------------\n");

    for (int i = 0; i < total; i++)
    {
        // skips the room if its the wrong type
        if (strcmp(rooms[i].type, type) != 0)
            continue;

        // skips the room if its not available
        if (rooms[i].status != AVAILABLE)
            continue;

        printf("Room %d\n", rooms[i].numbers);
        found++;
    }
    if (found == 0)
        printf("No %s rooms currently available.\n", type);

    printf("-----------------------\n\n");
}

/*
    search for the room by its number
*/
int find_room(struct Room rooms[], int total, int numbers)
{
    for (int i = 0; i < total; i++)
    {
        if (rooms[i].numbers == numbers)
            return i; // finds it and return its position
    }
    return -1; // doesn't find anything
}

void edit_room(struct Room rooms[], int total)
{
    int roomNum, idx;

    display_all_rooms(rooms, total);

    printf("Enter the room number to edit: ");
    scanf("%d", &roomNum);
    while (getchar() != '\n');

    idx = find_room(rooms, total, roomNum);   /* reuse your existing search function */

    if (idx == -1)
    {
        printf("Room number %d not found.\n", roomNum);
        return;
    }

    printf("Current floor: %d, Current price: %.2f\n", rooms[idx].floors, rooms[idx].price);

    printf("Enter new floor: ");
    scanf("%d", &rooms[idx].floors);
    while (getchar() != '\n');

    printf("Enter new price: ");
    scanf("%f", &rooms[idx].price);
    while (getchar() != '\n');

    printf("Room %d updated successfully.\n", rooms[idx].numbers);
}

void admin_menu(struct Room rooms[], int total)
{
    int choice;

    do
    {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. View rooms\n2. Edit room (floor/price)\n3. Exit to main menu\n");
        printf("=======================\n");
        printf("Please pick an action (1-3): ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            display_all_rooms(rooms, total);
            break;
        case 2:
            edit_room(rooms, total);
            break;
        case 3:
            printf("Exiting admin menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 3);
}