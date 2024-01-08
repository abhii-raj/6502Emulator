//
// Created by shobhit on 7/1/24.
//

#include "ui_render.hpp"

#include <gtk-3.0/gtk/gtk.h>

void onWindowDestroy(GtkWidget *widget, gpointer user_data) {
    window = NULL;
    gtk_widget_destroy(widget);
    gtk_main_quit();
    printf("closing\n");
}

GtkTreeViewColumn* retTreeCol(char *ColumnHeading, GtkCellRenderer* cell, GtkWidget* treeview) {
    GtkTreeViewColumn* col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title( col, ColumnHeading);
    gtk_tree_view_column_pack_start (col, cell, TRUE);
    gtk_tree_view_column_add_attribute (col, cell, "text", 1);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), col);
}

void setupUI() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_window_set_title(GTK_WINDOW(window), "6502 Emulator");

    // to add multiple widgets to the window
    GtkWidget *fix = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fix);

    /**** ROWS AND COLUMNS TO OUTPUT VALUE OF REGISTERS ****/
    // GTK ListStore
    // used inside GTK TreeView
    colList = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                              G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    // GTK TreeView
    GtkWidget *treeview = gtk_tree_view_new();
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(colList));

    GtkCellRenderer *cellRenderer = gtk_cell_renderer_text_new();

    GtkTreeViewColumn* PC_col = retTreeCol("Program Counter", cellRenderer, treeview);
    GtkTreeViewColumn* A_col = retTreeCol("A", cellRenderer, treeview);
    GtkTreeViewColumn* X_col = retTreeCol("X", cellRenderer, treeview);
    GtkTreeViewColumn* Y_col = retTreeCol("Y", cellRenderer, treeview);
    GtkTreeViewColumn* SP_col = retTreeCol("SP", cellRenderer, treeview);
    GtkTreeViewColumn* FR_col = retTreeCol("N V - B D I Z C", cellRenderer, treeview);

    /**** FOR TEXT BUFFER AND TEXTVIEW ****/
    // GTK textview
    GtkWidget *textview = gtk_text_view_new();
    // GTK text buffer
    GtkTextBuffer *txtBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));

    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(textview), GTK_WRAP_CHAR);


    /*** GTK SCROLLED WINDOW FOR TEXT VIEW ****/
    GtkWidget *scr_window_textview = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scr_window_textview),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scr_window_textview), 300);
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scr_window_textview), 400);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(scr_window_textview), GTK_SHADOW_IN);

    // adding textview widget to scrollable window
    gtk_container_add(GTK_CONTAINER(GTK_SCROLLED_WINDOW(scr_window_textview)), textview);


    // put widgets inside GtkFixed
    gtk_fixed_put(GTK_FIXED(fix), treeview, 50, 60);
    gtk_fixed_put(GTK_FIXED(fix), scr_window_textview, 800, 60);

    // for closing application
    g_signal_connect(window, "destroy", G_CALLBACK(onWindowDestroy), NULL);
}

void mainUI(int *f_argc, char ***f_argv) {
    gtk_init(f_argc, f_argv);
    setupUI();
    gtk_widget_show_all(window);
    gtk_main();
}
