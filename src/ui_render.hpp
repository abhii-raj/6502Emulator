//
// Created by shobhit on 7/1/24.
//

#ifndef INC_6502EMULATOR_UI_RENDER_HPP
#define INC_6502EMULATOR_UI_RENDER_HPP

#include <gtk-3.0/gtk/gtk.h>

#include "instructionCycle.hpp"
#include "memory.hpp"
#include "processor.hpp"
#include "codeLoad.hpp"

static GtkWidget *window;
static GtkListStore *colList;

static int firstPress = 1;

static InstructionCycle IC;
static Memory *local_memRef = IC.retMemoryObj();
static Processor *local_procRef = IC.retProcessorObj();
static CodeLoad cl;

void onWindowDestroy(GtkWidget *widget, gpointer user_data);
void load_css(void);
GtkTreeViewColumn* retTreeCol(char *ColumnHeading, GtkCellRenderer* cell, GtkWidget* treeview);
void addRow(gpointer user_data);
gpointer cont_rowUpdateThread(gpointer user_data);
gpointer step_rowUpdateThread(gpointer user_data);
void onLoadButtonClick(GtkButton *button, GtkTextBuffer* txtBuff);
void onContinuousRunButtonClick(GtkButton *button,GtkTextBuffer* txtBuff);
void onStepRunButtonClick(GtkButton *button,GtkTextBuffer* txtBuff);
void onClearButtonClick(GtkButton *button,GtkTextBuffer* txtBuff);
void onMemDumpButtonClick(GtkButton *button);
void GUI_Binding_contRun_InstrCycle(gpointer user_data);
void GUI_Binding_stepRun_InstrCycle(gpointer user_data);
std::string decToBin(std::string decNum);
void setupMemDumpWindow();
void setupUI();
void mainUI(int *f_argc, char ***f_argv);

#endif //INC_6502EMULATOR_UI_RENDER_HPP
