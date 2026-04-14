#ifndef STEERING_H
#define STEERING_H

#include "config.h"
#include <SDL3/SDL.h>

#define PACKET_HEADER 0xAA

#pragma pack(push, 1)
typedef struct {
    u8 header;    // 0xAA
    i8 steering;  // -128 .. 127
    i8 throttle;  // -128 .. 127
    i8 brake;     // -128 .. 127
    u8 checksum;
} ControlPacket;
#pragma pack(pop)

Status steering_init(SDL_Joystick** joystick);
void get_pkt(ControlPacket* p, i16 s, i16 t, i16 b);

#endif /* STEERING_H */