#include <gtk/gtk.h>
#include "ui.h"
#include "db.h"

int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("com.example.md5",
                                              G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int res = g_application_run(G_APPLICATION(app), argc, argv);

    close_database();
    g_object_unref(app);

    return res;
}
