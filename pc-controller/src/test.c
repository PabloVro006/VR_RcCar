#include "../inc/config.h"

#pragma pack(push, 1)
typedef struct {
    i8 throttle;
    i8 brake;
} ControlPacket;
#pragma pack(pop)

static i8 scale_axis(i16 value) {
    return (i8)(value / 256); // 0..32767 → 0..127
}

int main(void) {

    i16 startValue = 32767;
    printf("Start value: %d\n", startValue);
    i8 finalValue = scale_axis(startValue);
    printf("Final value: %d", finalValue);

    return 0;
}