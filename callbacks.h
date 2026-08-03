#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

// Установка ссылок на глобальные виджеты
void set_login_entry(GtkWidget *widget);
void set_result_widgets(GtkWidget *login_label, GtkWidget *parol_label);

// Callback-функции
void toggle_visibility(GtkButton *button, GtkEntry *entry);
void hash_clicked(GtkButton *button, GtkEntry *entry);

#endif
