#include <stdio.h>

void HotelRooms(int rooms[3][10]) {
    int temp[3][10] = {
        {1, 2, 3, 4, 5, 11, 12, 13, 21, 22},
        {1, 2, 3, 4, 5, 11, 12, 13, 21, 22},
        {1, 2, 3, 4, 5, 11, 12, 13, 21, 22}
    };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 10; j++)
            rooms[i][j] = temp[i][j];
}

void displayRoom(int rooms[3][10]) {
    int DisRoom[3][10] = {
        {101, 102, 103, 104, 105, 106, 107, 108, 109, 110},
        {201, 202, 203, 204, 205, 206, 207, 208, 209, 210},
        {301, 302, 303, 304, 305, 306, 307, 308, 309, 310}
    };

    printf("Room No. \n");
    printf("-----------------------------\n");

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            printf("%d\t", DisRoom[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rooms[3][10];

    HotelRooms(rooms);   // Fill in the background values
    displayRoom(rooms);  // Display room numbers with those values

    return 0;
}