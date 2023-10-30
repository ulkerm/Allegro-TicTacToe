// file: src/utils.h

#pragma once
#include <stdbool.h>
#include <allegro5/allegro5.h>

void init_or_exit(bool is_initialized, const char *name);
void* assert_not_null(void *ptr, const char *name);
void assert_handler(const char *expr, const char *file, int line, const char *func);

