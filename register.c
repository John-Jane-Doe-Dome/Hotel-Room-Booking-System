#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "register.h"

static int ValidateName(const char *name)
{
    // FIX: no longer prints its own message here - ValidateInput already
    // prints a message on failure, so this was producing a garbled
    // double message ("Name must not be empty.Invalid: Names must...").
    if (strlen(name) == 0)
    {
        return 0;
    }
    for (int i = 0; name[i]; i++)
    {
        // FIX: cast to unsigned char before isalpha - passing a plain
        // (possibly negative) char is undefined behavior per the C
        // standard for values outside unsigned char / EOF range.
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ' && name[i] != '-')
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
    size_t len = strlen(phone);
    // FIX: added an upper bound too (E.164 max is 15 digits), previously
    // only a lower bound was enforced.
    if (len < 9 || len > 15)
    {
        return 0;
    }
    for (; phone[i]; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
    }
    return 1;
}

static void ValidateInput(const char *prompt, const char *error_msg, char *buffer,
                          int size, int (*validator)(const char *))
{
    // FIX: validator is now called once per iteration and the result is
    // reused, instead of being called twice (once in the if check, once
    // in the while condition).
    int ok;
    do
    {
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        ok = validator(buffer);
        if (!ok)
        {
            printf("Invalid: %s\n", error_msg);
        }
    } while (!ok);
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
        "Phone number must be 9 to 15 digits.",
        PhoneNumber, 20, ValidatePhone);
}