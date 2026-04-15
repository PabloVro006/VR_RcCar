#include <SDL3/SDL.h>
#include "../inc/config.h"
#include "../inc/serial.h"
#include "../inc/steering.h"


/* STATIC VARIABLES */
static bool isJoystickConnected = 0;
static SDL_Joystick *joystick = NULL;
static ControlPacket pkt;
static SerialPort sp;
static int retries = 3;

/* ENTRY POINT */
int main(void) {
    while (retries--) {
        if (run_program() == STATUS_OK) {
            LOG_INFO("Completed successfully");
            return 0;
        }
        LOG_WARN("Retrying... (%d left)", retries);
        SDL_Delay(1000);
    }

    LOG_ERR("Fatal: too many retries");
    printf("\n");
    if(isJoystickConnected) {
        LOG_INFO("Closing joystick...");
        SDL_CloseJoystick(joystick);
        SDL_Quit();
    }
    isJoystickConnected = 0;
    serial_close(&sp);
    return 0;
}

/* MAIN PROGRAM */
Status run_program(void) {
    printf("\n");

    /* PERIPHERAL INITIALIZATION */
    if(!isJoystickConnected) {
        joystick = NULL;
        if (steering_init(&joystick) != STATUS_OK) {
            LOG_ERR("Steering init failed");
            return STATUS_ERROR;
        }
        isJoystickConnected = 1;
    }

    if (serial_init(&sp, SERIAL_PORT) != STATUS_OK) {
        LOG_ERR("Serial init failed (error: %lu)", GetLastError());
        return STATUS_ERROR;
    }

    /* TURN LED OFF */
    if (serial_write(&sp, &(u8){LED_OFF_CODE}, 1) != STATUS_OK) {
        LOG_ERR("Turning LED OFF failed");
        return STATUS_ERROR;
    }

    /* MAIN LOOP */
    printf("\n");
    while (1) {
        SDL_PumpEvents(); // gathers all the pending input information from devices and places it in the event queue

        i16 steering = SDL_GetJoystickAxis(joystick, 0);
        i16 throttle = SDL_GetJoystickAxis(joystick, 1);
        i16 brake    = SDL_GetJoystickAxis(joystick, 2);

        get_pkt(&pkt, steering, throttle, brake); // get control packet from joystick input

        // sends data to stm32 via serial port
        if (serial_write(&sp, (uint8_t*)&pkt, sizeof(pkt)) != STATUS_OK) {
            LOG_ERR("Serial write failed");
            retries = 2;
            return STATUS_ERROR;
        }

        SDL_Delay(1000); // 10
    }
    return STATUS_OK;
}