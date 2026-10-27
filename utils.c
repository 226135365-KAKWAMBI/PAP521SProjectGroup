#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"

/* Remove leading and trailing white space from s (in place). */
static void trim(char *s) {
    size_t len = strlen(s);
    size_t start = 0;

    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }
    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
}

/* Read one line safely. Over-long lines are cut and the rest discarded.
   If input ends (EOF) the program exits cleanly instead of looping forever. */
void readLine(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, (int)size, stdin) == NULL) {
        printf("\n[Input closed] Exiting system.\n");
        exit(0);
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { /* discard rest of line */ }
    }
    trim(buf);
}

void readNonEmptyString(const char *prompt, char *buf, size_t size) {
    for (;;) {
        readLine(prompt, buf, size);
        if (strlen(buf) == 0) {
            printf("[Error] This field cannot be empty.\n");
            continue;
        }
        return;
    }
}

/* A person name: letters, spaces, hyphens, apostrophes and full stops only. */
void readPersonName(const char *prompt, char *buf, size_t size) {
    for (;;) {
        readNonEmptyString(prompt, buf, size);
        int ok = 1, hasLetter = 0;
        for (size_t i = 0; i < strlen(buf); i++) {
            unsigned char ch = (unsigned char)buf[i];
            if (isalpha(ch)) {
                hasLetter = 1;
            } else if (ch != ' ' && ch != '-' && ch != '\'' && ch != '.') {
                ok = 0;
                break;
            }
        }
        if (!ok || !hasLetter) {
            printf("[Error] Name may only contain letters, spaces, - ' and .\n");
            continue;
        }
        return;
    }
}

/* An ID: not empty and no spaces inside. */
void readIdString(const char *prompt, char *buf, size_t size) {
    for (;;) {
        readNonEmptyString(prompt, buf, size);
        if (strchr(buf, ' ') != NULL) {
            printf("[Error] ID must not contain spaces.\n");
            continue;
        }
        return;
    }
}

int readIntInRange(const char *prompt, int min, int max) {
    char buf[64];
    char *end;

    for (;;) {
        readLine(prompt, buf, sizeof buf);
        if (strlen(buf) == 0) {
            printf("[Error] Input cannot be empty.\n");
            continue;
        }
        long v = strtol(buf, &end, 10);
        if (*end != '\0') {
            printf("[Error] '%s' is not a valid whole number.\n", buf);
            continue;
        }
        if (v < min || v > max) {
            printf("[Error] Enter a number between %d and %d.\n", min, max);
            continue;
        }
        return (int)v;
    }
}

double readDoubleInRange(const char *prompt, double min, double max) {
    char buf[64];
    char *end;

    for (;;) {
        readLine(prompt, buf, sizeof buf);
        if (strlen(buf) == 0) {
            printf("[Error] Input cannot be empty.\n");
            continue;
        }
        double v = strtod(buf, &end);
        if (*end != '\0' || !isfinite(v)) {
            printf("[Error] '%s' is not a valid number.\n", buf);
            continue;
        }
        if (v < min || v > max) {
            printf("[Error] Value must be between %.2f and %.2f.\n", min, max);
            continue;
        }
        return v;
    }
}

int readMenuChoice(const char *prompt, int max) {
    return readIntInRange(prompt, 1, max);
}

/* Case-insensitive "does haystack contain needle?" */
int containsIgnoreCase(const char *haystack, const char *needle) {
    size_t hl = strlen(haystack);
    size_t nl = strlen(needle);

    if (nl == 0) return 1;
    if (nl > hl) return 0;

    for (size_t i = 0; i + nl <= hl; i++) {
        size_t j = 0;
        while (j < nl &&
               tolower((unsigned char)haystack[i + j]) == tolower((unsigned char)needle[j])) {
            j++;
        }
        if (j == nl) return 1;
    }
    return 0;
}

/* Basic e-mail check: one '@', text before it, a '.' inside the domain. */
int isValidEmail(const char *email) {
    size_t len = strlen(email);
    const char *at = strchr(email, '@');

    if (len < 5 || strchr(email, ' ') != NULL) return 0;
    if (at == NULL || at == email) return 0;
    if (strchr(at + 1, '@') != NULL) return 0;

    const char *dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || dot[1] == '\0') return 0;
    return 1;
}

/* Phone: optional leading '+', then 7 to 15 digits only. */
int isValidPhone(const char *phone) {
    size_t len = strlen(phone);
    size_t start = (phone[0] == '+') ? 1 : 0;

    if (len - start < 7 || len - start > 15) return 0;
    for (size_t i = start; i < len; i++) {
        if (!isdigit((unsigned char)phone[i])) return 0;
    }
    return 1;
}

void printLine(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}
