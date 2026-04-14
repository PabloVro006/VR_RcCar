#ifndef SERIAL_H
#define SERIAL_H

#include "config.h"

#define SERIAL_PORT "\\\\.\\COM4"

typedef struct {
    HANDLE handle;
} SerialPort;

Status serial_init(SerialPort* sp, const char* port);
Status serial_write(SerialPort* sp, const u8* buffer, DWORD size);
void serial_close(SerialPort* sp);

#endif