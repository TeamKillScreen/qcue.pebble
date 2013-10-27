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


void handle_init(AppContextRef ctx) {
  const bool animated = true;

  window_init(&window, "Qcue");
  window_stack_push(&window, animated);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };

  app_event_loop(params, &handlers);
}
