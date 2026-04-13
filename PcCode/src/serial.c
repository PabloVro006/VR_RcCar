#include "../inc/serial.h"

static Status set_params(DCB* params) {
    if (params == NULL) {
        LOG_ERR("Parameters are NULL");
        return STATUS_ERROR;
    }
    params->BaudRate = CBR_9600;
    params->ByteSize = 8;
    params->StopBits = ONESTOPBIT;
    params->Parity   = NOPARITY;
    return STATUS_OK;
}

static Status set_timeouts(COMMTIMEOUTS* t) {
    if (t == NULL) {
        LOG_ERR("Timeouts are NULL");
        return STATUS_ERROR;
    }
    t->ReadIntervalTimeout         = 50;
    t->ReadTotalTimeoutConstant    = 50;
    t->ReadTotalTimeoutMultiplier  = 10;
    t->WriteTotalTimeoutConstant   = 50;
    t->WriteTotalTimeoutMultiplier = 10;
    return STATUS_OK;
}

static Status serial_configure(SerialPort* sp) {
    if (!sp || sp->handle == INVALID_HANDLE_VALUE) {
        LOG_ERR("Serial is invalid");
        return STATUS_ERROR;
    }
    DCB dcb = {0};
    COMMTIMEOUTS timeouts = {0};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(sp->handle, &dcb)) {
        LOG_ERR("Getting devide state (error: %lu)", GetLastError());
        serial_close(sp->handle);
        return STATUS_ERROR;
    }
    //LOG_INFO("Got device state");

    if(set_params(&dcb) != STATUS_OK || !(SetCommState(sp->handle, &dcb))) {
        LOG_ERR("Setting device parameters (error: %lu)", GetLastError());
        serial_close(sp->handle);
        return STATUS_ERROR;
    }
    //LOG_INFO("Set device parameters");

    if(set_timeouts(&timeouts) != STATUS_OK || !(SetCommTimeouts(sp->handle, &timeouts))) {
        LOG_ERR("Setting timeouts (error: %lu)", GetLastError());
        serial_close(sp->handle);
        return STATUS_ERROR;
    }
    //LOG_INFO("Setted timeouts");
    LOG_INFO("Everything ok with serial");
    return STATUS_OK;
}

Status serial_init(SerialPort* sp, const char* port) {
    LOG_INFO("Opening serial port...");
    if (!sp || !port) {
        LOG_ERR("Serial or port is NULL");
        return STATUS_ERROR;
    }
    sp->handle = INVALID_HANDLE_VALUE;
    sp->handle = CreateFile(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (sp->handle == INVALID_HANDLE_VALUE) {
        LOG_ERR("Serial is invalid");
        return STATUS_ERROR;
    }
    LOG_INFO("Serial port opened");
    return serial_configure(sp);
}

Status serial_write(SerialPort* sp, const u8* buffer, DWORD size) {
    DWORD written = 0;
    if (!sp || sp->handle == INVALID_HANDLE_VALUE || !buffer) {
        LOG_ERR("Buffer or bytesWritten are NULL");
        return STATUS_ERROR;
    }
    if (!WriteFile(sp->handle, buffer, size, &written, NULL)) return STATUS_ERROR;
    LOG_INFO("(%lu) Bytes written", written);
    return STATUS_OK;
}

void serial_close(SerialPort* sp) {
    LOG_INFO("Closing serial port...");
    if (!sp || sp->handle == INVALID_HANDLE_VALUE) return;

    if (!CloseHandle(sp->handle)) {
        LOG_ERR("Closing serial port");
        return;
    }

    sp->handle = INVALID_HANDLE_VALUE;
    LOG_INFO("Serial port closed");
}