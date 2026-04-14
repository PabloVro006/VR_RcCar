#include "../inc/steering.h"

static i8 scale_axis(i16 value) {
    return (i8)(value / 256); // 0..32767 → 0..127
}

static u8 crc8(const u8 *data, u8 len) {
    u8 crc = 0x00;
    for (u8 i = 0; i < len; i++) {
        crc ^= data[i];
        for (u8 j = 0; j < 8; j++) {
            if (crc & 0x80) crc = (crc << 1) ^ 0x07;
            else crc <<= 1;
        }
    }
    return crc;
}


void get_pkt(ControlPacket* p, i16 s, i16 t, i16 b) {
    p->header   = PACKET_HEADER;
    p->steering = scale_axis(s);
    p->throttle = scale_axis(t);
    p->brake    = scale_axis(b);
    p->checksum = crc8((uint8_t*)p, sizeof(ControlPacket) - 1);
}


Status steering_init(SDL_Joystick** joystick) {
    SDL_PumpEvents();
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS)) {
        LOG_ERR("SDL init failed: (error: %s)", SDL_GetError());
        return STATUS_ERROR;
    }
    int count;
    SDL_JoystickID *ids = SDL_GetJoysticks(&count);
    if (ids == NULL || count <= 0) {
        LOG_ERR("Failed to get ids");
        SDL_free(ids);
        return STATUS_ERROR;
    }
    *joystick = SDL_OpenJoystick(ids[0]);
    SDL_free(ids);
    if (!*joystick) {
        LOG_ERR("Failed to open joystick (error: %s)", SDL_GetError());
        return STATUS_ERROR;
    }
    LOG_INFO("Controller connected");
    return STATUS_OK;
}