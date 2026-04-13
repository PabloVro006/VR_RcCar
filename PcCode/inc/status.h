#ifndef STATUS_H
#define STATUS_H

#define COLOR_RED    "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RESET  "\x1b[0m"

#define LOG_INFO(fmt, ...) fprintf(stderr, COLOR_GREEN "[INFO] " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) fprintf(stderr, COLOR_YELLOW "[WARN] " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) fprintf(stderr, COLOR_RED "[ERROR] " fmt COLOR_RESET "\n", ##__VA_ARGS__)

typedef enum Status {
    STATUS_OK,
    STATUS_ERROR
} Status;

#endif /* STATUS_H */