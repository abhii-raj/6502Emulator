//
// Created by shobhit on 7/1/24.
//

#include "ui_render.hpp"
#include "instructionCycle.hpp"

#include <gtk-3.0/gtk/gtk.h>

#include <iostream>
#include <algorithm>

void onWindowDestroy(GtkWidget *widget, gpointer user_data) {
    window = NULL;
    gtk_widget_destroy(widget);
    gtk_main_quit();
    printf("closing\n");
}

GtkTreeViewColumn* retTreeCol(char *ColumnHeading, GtkCellRenderer* cell, GtkWidget* treeview, int col_atr) {
    GtkTreeViewColumn* col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title( col, ColumnHeading);
    gtk_tree_view_column_pack_start (col, cell, TRUE);
    gtk_tree_view_column_add_attribute (col, cell, "text", col_atr);
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), col);
}

void addRow(gpointer user_data) {
    GtkTreeIter iter;
    gtk_list_store_append(colList, &iter);

    std::string PC_str = std::to_string(local_procRef->PC);
    const char *PC_cstr = PC_str.c_str();
    std::string A_str = std::to_string(local_procRef->A);
    const char *A_cstr = A_str.c_str();
    std::string X_str = std::to_string(local_procRef->X);
    const char *X_cstr = X_str.c_str();
    std::string Y_str = std::to_string(local_procRef->Y);
    const char *Y_cstr = Y_str.c_str();
    std::string SP_str = std::to_string(local_procRef->SP);
    const char *SP_cstr = SP_str.c_str();
    std::string FR_str = std::to_string(local_procRef->FR);
    std::string FR_str_bin = decToBin(FR_str);
    const char *FR_cstr_bin = FR_str_bin.c_str();

    gtk_list_store_set(colList, &iter,
                       0, PC_cstr,
                       1, A_cstr,
                       2, X_cstr,
                       3, Y_cstr,
                       4, SP_cstr,
                       5, FR_cstr_bin,
                       -1);
    std::cout << FR_cstr_bin << std::endl;
}

gpointer rowUpdateThread(gpointer user_data) {
    g_idle_add (G_SOURCE_FUNC(GUI_Binding_InstrCycle), NULL);
    //g_usleep(10000);
}

void onLoadButtonClick(GtkButton *button,GtkTextBuffer* txtBuff) {
    GtkTextIter s_iter, e_iter;
    gtk_text_buffer_get_start_iter(txtBuff, &s_iter);
    gtk_text_buffer_get_end_iter(txtBuff, &e_iter);
    char *str = gtk_text_buffer_get_text(txtBuff, &s_iter, &e_iter, FALSE);
    std::string OpcodeBuffer(str);
    cl.CodeLoadFromStrBuffer(OpcodeBuffer, 0x0400, local_memRef);
    //local_procRef->VMInit(local_memRef);
    //printf("%s\n", str);
    local_memRef->readMem(0x400);
    local_memRef->readMem(0x401);
    local_memRef->readMem(0x402);
    local_memRef->readMem(0x403);
    local_memRef->readMem(0x404);
    local_memRef->readMem(0x405);
}

void onContinuousRunButtonClick(GtkButton *button,GtkTextBuffer* txtBuff) {
    g_thread_new("RowUpdate", rowUpdateThread, NULL);
}

void GUI_Binding_InstrCycle(gpointer user_data) {
    Processor *proc = local_procRef;
    Memory *mem = local_memRef;
    proc->VMInit(mem);
    uint8_t opcode;

    while( (opcode = IC.IFetch()) != 0x00 ) {
        IC.Execute(opcode);
        addRow(NULL);
    }
}

std::string decToBin(std::string decNum) {
    std::string temp = "";
    temp.clear();
    int num = std::stoi(decNum, 0, 10);
    int rem = 0;
    int n = num;
    while(n > 0) {
        rem = n%2;
        n = n/2;
        char t;
        if(rem == 0) t = '0';
        else t = '1';
        temp += t;
        temp += ' ';
    }
    //temp.append(" 0 0");
    // pad string if the contents of flag register is less than 8
    while(temp.length() < 15) {
        temp.append("0 ");
    }
    reverse(temp.begin(), temp.end());
    //temp[3] = ' ';
    temp[5] = '-';
    //temp[5] = ' ';
    /***
    // pad string if the length of register is less than 8
    if(temp.length() < 8) {
        for(int i=0;i<(8-temp.length());) {
            temp.append("o");
        }
    }***/
    return temp;
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

    GtkTreeViewColumn* PC_col = retTreeCol("Program Counter", cellRenderer, treeview, 0);
    GtkTreeViewColumn* A_col = retTreeCol("A", cellRenderer, treeview, 1);
    GtkTreeViewColumn* X_col = retTreeCol("X", cellRenderer, treeview, 2);
    GtkTreeViewColumn* Y_col = retTreeCol("Y", cellRenderer, treeview, 3);
    GtkTreeViewColumn* SP_col = retTreeCol("SP", cellRenderer, treeview, 4);
    GtkTreeViewColumn* FR_col = retTreeCol("N V - B D I Z C", cellRenderer, treeview, 5);

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

    // button to load opcode into memory
    GtkWidget *loadButton = gtk_button_new_with_label("Load");

    // button to execute all instruction in one step
    GtkWidget *continuousRunButton = gtk_button_new_with_label("Continuous Run");


    // put widgets inside GtkFixed
    gtk_fixed_put(GTK_FIXED(fix), treeview, 50, 60);
    gtk_fixed_put(GTK_FIXED(fix), scr_window_textview, 800, 60);
    gtk_fixed_put(GTK_FIXED(fix), loadButton, 800, 400);
    gtk_fixed_put(GTK_FIXED(fix), continuousRunButton, 900, 400);

    // for closing application
    g_signal_connect(window, "destroy", G_CALLBACK(onWindowDestroy), NULL);
    // on clicking Load button
    g_signal_connect(loadButton, "clicked", G_CALLBACK(onLoadButtonClick), txtBuff);
    // on clicking Continuous Run button
    g_signal_connect(continuousRunButton, "clicked", G_CALLBACK(onContinuousRunButtonClick), txtBuff);
}

void mainUI(int *f_argc, char ***f_argv) {
    gtk_init(f_argc, f_argv);
    setupUI();
    gtk_widget_show_all(window);
    gtk_main();
}
