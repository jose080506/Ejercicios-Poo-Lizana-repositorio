#include <QApplication>
#include "kanban.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    KanbanWidget kanban;
    kanban.setWindowTitle("Tablero Kanban - POO 2026");
    kanban.resize(1200, 720);
    kanban.show();

    return a.exec();
}
