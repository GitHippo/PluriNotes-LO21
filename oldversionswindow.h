#ifndef OLDVERSIONSWINDOW_H
#define OLDVERSIONSWINDOW_H

#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include "fonction.h"


///Widget popup pour afficher les anciennes versions d'une note et les afficher sous forme de liste afin de pouvoir les restaurer si besoin
class OldVersionsWindow : public QWidget{
    Q_OBJECT
private:
    Note* note;
    QListWidget* list;
    QVBoxLayout* layer;
    QPushButton* close;
    QPushButton* restor;
    QScrollArea* scroller;
public:
    OldVersionsWindow(Note* n, QWidget* parent=0);

public slots :
    void restorNote();
    void updateNotesManager();
    void closeEditeur();
};

#endif // OLDVERSIONSWINDOW_H

