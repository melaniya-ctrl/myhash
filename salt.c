#include "salt.h"
#include <glib.h>
#include <stdio.h>

// Генерация случайной соли (16 символов в hex-формате)
char* generate_salt() {
    // Два случайных числа
    guint32 r1 = g_random_int();
    guint32 r2 = g_random_int();

    // Преобразование в hex-строку (каждое число = 8 символов)
    char *salt = g_malloc(17 * sizeof(char));
    sprintf(salt, "%08x%08x", r1, r2);

    return salt;
}
