#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define MY_UUID { \
  0x1D, 0x86, 0x6D, 0xDA, 0xE8, 0x22, 0x43, 0x28, 0xA9, 0x00, 0x5F, 0x4E, 0x4B, 0x31, 0x16, 0xDA }

PBL_APP_INFO(MY_UUID,
             "Qcue", "Team Kill Screen",
             1, 0,
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;

TextLayer text_layer_logo;
TextLayer text_layer_position;

AppSync app_sync;
uint8_t app_sync_buffer[32];

enum {
    POSITION_KEY = ((uint8_t)0x0), // TUPLE_INT
};

void sync_error_callback(
    DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {

    // vibes_double_pulse();
}

void sync_tuple_changed_callback(
    const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {

    /*
    if (!strcmp("bye", new_tuple->value->cstring)) {
      return;
    }
    */

    text_layer_set_text(&text_layer_position, new_tuple->value->cstring);
    text_layer_set_text(&text_layer_logo, "qcue");

    vibes_double_pulse();
}

void init_app_sync() {
    Tuplet initial_values[] = {
        TupletCString(POSITION_KEY, "?")
    };
    
    app_sync_init(
      &app_sync,
      app_sync_buffer,
      sizeof(app_sync_buffer),
      initial_values,
      ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback,
      sync_error_callback,
      NULL);
}

void init_text_layers() {
    GRect layer_rect_logo = GRect(0, 0, 144, 72); // x, y, w, h
    GRect layer_rect_position = GRect(0, 80, 144, 168 - 82);

    // Qcue.
    text_layer_init(&text_layer_logo, layer_rect_logo);

    text_layer_set_font(&text_layer_logo,
      fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));

    text_layer_set_text_alignment(&text_layer_logo, GTextAlignmentCenter);
    text_layer_set_text(&text_layer_logo, "Q");

    // Position.
    text_layer_init(&text_layer_position, layer_rect_position);

    text_layer_set_font(&text_layer_position,
      fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));

    text_layer_set_text_alignment(&text_layer_position, GTextAlignmentCenter);
    text_layer_set_text(&text_layer_position, "?");
}

void handle_init(AppContextRef ctx) {
  const bool animated = true;

  window_init(&window, "qcue");
  window_stack_push(&window, animated);

  init_text_layers();

  layer_add_child(&window.layer, &text_layer_logo.layer);
  layer_add_child(&window.layer, &text_layer_position.layer);

  init_app_sync();
}

void handle_deinit(AppContextRef context) {
    app_sync_deinit(&app_sync);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,

    .messaging_info = {
      .buffer_sizes = {
        .inbound = 124, // inbound buffer size in bytes
        .outbound = 16, // outbound buffer size in bytes
      }
    }
  };

  app_event_loop(params, &handlers);
}
