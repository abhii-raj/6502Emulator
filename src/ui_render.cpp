//
// Created by shobhit on 7/1/24.
//

#include "ui_render.hpp"

#include <gtk-3.0/gtk/gtk.h>

void setupUI(int *f_argc, char ***f_argv) {
    gtk_init(f_argc, f_argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_window_set_title(GTK_WINDOW(window), "6502 Emulator");

    gtk_widget_show_all(window);
    gtk_main();
}
