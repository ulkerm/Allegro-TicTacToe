// file: src/main.c

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "resources.h"
#include "game.h"
#include "utils.h"

static void system_init(void) {
  init_or_exit(al_init(), "allegro");
  init_or_exit(al_install_keyboard(), "keyboard");
  init_or_exit(al_init_font_addon(), "font");
  init_or_exit(al_init_ttf_addon(), "ttf");
  init_or_exit(al_install_mouse(), "mouse");
  init_or_exit(al_init_primitives_addon(), "primitives add-on");
}

static void main_event_loop(void) {
  ALLEGRO_EVENT event;
  al_start_timer(timer);
  while (true) {
    al_wait_for_event(queue, &event);   
    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      redraw = true;
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: mouse_down(event.mouse); break;
    case ALLEGRO_EVENT_KEY_DOWN: key_down(event.keyboard); break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE: done = true; break;
    }
    if (done) break;
    if (redraw && al_is_event_queue_empty(queue)) {
      game_redraw();
      redraw = false;
    }
  }
}


int main(void) {
  system_init();
  init_assets();
  register_events();
  main_event_loop();
  unregister_events();
  destroy_assets();
  return 0;
}

// file: main.c

