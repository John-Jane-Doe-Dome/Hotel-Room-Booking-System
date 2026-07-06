#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "register.h"

static int ValidateName(const char *name)
{
    if (strlen(name) == 0)
    {
        printf("Name must not be empty.");
        return 0;
    }
    for (int i = 0; name[i]; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-')
        {
            return 0;
        }
    }
    return 1;
}

static int ValidateEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (!at || at == email)
    {
        return 0;
    }
    const char *dot = strchr(at, '.');
    if (!dot || dot == at + 1 || *(dot + 1) == '\0')
    {
        return 0;
    }
    return 1;
}

static int ValidatePhone(const char *phone)
{
    int i = 0;
    if (strlen(phone) < 9)
    {
        return 0;
    }
    for (; phone[i]; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }
    return 1;
}

static void ValidateInput(const char *prompt, const char *error_msg, char *buffer,
                          int size, int (*validator)(const char *))
{
    do
    {
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (!validator(buffer))
        {
            printf("Invalid: %s\n", error_msg);
        }
    } while (!validator(buffer));
}

void registration(char CustomerName[100], char PhoneNumber[20], char CustomerEmail[100])
{
    printf("-----Registration Form-----\n");

    ValidateInput(
        "Enter your name: ",
        "Names must contains only letters, space or hyphens.",
        CustomerName, 100, ValidateName);

    ValidateInput(
        "Enter your email: ",
        "Enter a valid email, e.g: user@gmail.com",
        CustomerEmail, 100, ValidateEmail);

    ValidateInput(
        "Enter your phone number: ",
        "Phone number must be atleast 9 digits.",
        PhoneNumber, 20, ValidatePhone);
}