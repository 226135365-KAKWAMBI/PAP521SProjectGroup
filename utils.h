#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/* ---------- Input helpers (all validate and re-prompt) ---------- */
void   readLine(const char *prompt, char *buf, size_t size);
void   readNonEmptyString(const char *prompt, char *buf, size_t size);
void   readPersonName(const char *prompt, char *buf, size_t size);
void   readIdString(const char *prompt, char *buf, size_t size);
int    readIntInRange(const char *prompt, int min, int max);
double readDoubleInRange(const char *prompt, double min, double max);
int    readMenuChoice(const char *prompt, int max);

/* ---------- String helpers ---------- */
int containsIgnoreCase(const char *haystack, const char *needle);
int isValidEmail(const char *email);
int isValidPhone(const char *phone);

/* ---------- Display helpers ---------- */
void printLine(char c, int n);

#endif
