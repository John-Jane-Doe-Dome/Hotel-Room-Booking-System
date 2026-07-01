#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "register.h"

// validate that the customer name on has letters, space, or hyphens

static int ValidateName(const char *name)
{
    if (strlen(name) == 0)
    {
        printf("Name must not be empty.");
        return 0;
    }
    for (int i = 0; name[i]; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-') // if all 3 are true its not valid
        {
            return 0;
        }
    }
    return 1; // meaning the name is valid
}

// validate that the email is in the correct email format

static int ValidateEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (!at || at == email) // if there is no @ or if @ is the start of email
    {
        return 0;
    }
    const char *dot = strchr(at, '.');
    if (!dot || dot == at + 1 || *(dot + 1) == '\0') // if there is no "." or if the "." is in the wrong place or if there is nothing after the  "."
    {
        return 0;
    }
    return 1; // meaning the email is valid
}

// validate the phone number

static int ValidatePhone(const char *phone)
{
    int i = 0;
    if (strlen(phone) < 9) // minimum of 9 numbers
    {
        return 0;
    }
    for (; phone[i]; i++)
    {
        if (!isdigit(phone[i])) // must be a number
        {
            return 0;
        }
    }
    return 1; // meaning the phone number is valid
}

// this functions is the validator for everything from name to phone to email.

static void ValidateInput(const char *prompt, const char *error_msg, char *buffer,
                          int size, int (*validator)(const char *))
{
    do
    {
        printf("%s", prompt);                 // print the message we want the user to see
        fgets(buffer, size, stdin);           // reads the input
        buffer[strcspn(buffer, "\n")] = '\0'; // allow space
        if (!validator(buffer))
        {
            printf("Invalid: %s\n", error_msg); // if input is invalid show error message
        }
    } while (!validator(buffer)); // loops this until it is valid
}

// main registration function

void registration(char CustomerName[100], char PhoneNumber[20], char CustomerEmail[100])
{
    printf("-----Registration Form-----\n");

    // ask user to input name
    ValidateInput(
        "Enter your name: ",
        "Names must contains only letters, space or hyphens.",
        CustomerName, 100, ValidateName);

    // ask user to input email
    ValidateInput(
        "Enter your email: ",
        "Enter a valid email, e.g: user@gmail.com",
        CustomerEmail, 100, ValidateEmail);

    // ask user to input phone number
    ValidateInput(
        "Enter your phone number: ",
        "Phone number must be atleast 9 digits.",
        PhoneNumber, 20, ValidatePhone);
}

