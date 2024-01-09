//
// Created by shobhit on 7/1/24.
//

#ifndef INC_6502EMULATOR_UI_RENDER_HPP
#define INC_6502EMULATOR_UI_RENDER_HPP

#include <gtk-3.0/gtk/gtk.h>

static GtkWidget *window;
static GtkListStore *colList;

void onWindowDestroy(GtkWidget *widget, gpointer user_data);
GtkTreeViewColumn* retTreeCol(char *ColumnHeading, GtkCellRenderer* cell, GtkWidget* treeview);
void onLoadButtonClick(GtkButton *button, GtkTextBuffer* txtBuff);
void setupUI();
void mainUI(int *f_argc, char ***f_argv);

#endif //INC_6502EMULATOR_UI_RENDER_HPP
