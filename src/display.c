#include "../include/display.h"

void initializeFontData(Chip8_t* pChip8)
{
    unsigned char fontData[80] =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // Draw 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // Draw 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // Draw 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // Draw 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // Draw 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // Draw 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // Draw 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // Draw 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // Draw 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // Draw 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // Draw A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // Draw B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // Draw C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // Draw D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // Draw E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // Draw F
            };

    memcpy((pChip8->memory + 0x50), fontData, sizeof(fontData));
}
