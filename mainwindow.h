#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QApplication"
#include "QWidget"
#include "QCoreApplication"
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListView>
#include <QFormLayout>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QFontComboBox>
#include <QMessageBox>
#include <QKeySequence>
#include <QTimer>
#include <QScrollArea>
#include <QItemSelectionModel>


#include"fonction.h"
#include "corbeille.h"
#include "corbeilleediteur.h"
#include"noteediteur.h"
#include"notefactory.h"
#include "notemanager.h"
#include "oldversions.h"
#include "relation.h"

class MainWindow : public QMainWindow {
private:
    QWidget* centralArea;
    QGridLayout* centralLayout;
    NoteEditeur* mainEditeur;
    CorbeilleEditeur *dustBin;
    QWidget* pageEdition;
    QVBoxLayout* layerEdition;
public:
    explicit MainWindow();
    void createTab();
    void clearWindow();
    void connectEditeur();
    void openEditeur(NoteEditeur* ne);

signals :
    public slots :
       void newArticle();
       void newTask();
       void newAudio();
       void newImage();
       void newVideo();
       void showDustbin();
       NoteEditeur* getNewEditeur(Note* n, QString& type);
};



#endif // MAINWINDOW_H

