#include "notesmanagerwindow.h"
#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"


NotesManagerWindow::NotesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item = new QListWidgetItem((*it)->getTitle(),listNotes);
    }
    QWidget* multiWidget = new QWidget();
    QPushButton* afficherNote = new QPushButton("Afficher la note");
    QPushButton* afficherRelations = new QPushButton("Afficher les relations");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(afficherNote);
    layout->addWidget(afficherRelations);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(afficherNote,SIGNAL(clicked()),this,SLOT(afficherNote()));
    QObject::connect(afficherRelations,SIGNAL(clicked()),this,SLOT(afficherAscendDescend()));
}

void NotesManagerWindow::afficherNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    else {throw NotesException("Couldn't show the note..");}
}

void NotesManagerWindow::afficherAscendDescend(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        MainWindow::getInstance().showRelationsAscendDescend(n);
       }
    else {throw NotesException("Couldn't show ascend descend for the note..");}
}


TaskManagerWindow::TaskManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listTask = new QListWidget();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        if((*it)->getClassName() == "task"){
            Task* t = dynamic_cast<Task*>(*it);
            unsigned int p = t->getPriority();
            QString title = t->getTitle();
            QString showedText = QString::number(p) + " " + title;
            item = new QListWidgetItem(showedText,listTask);
        }
    }
    QWidget* multiWidget = new QWidget;
    QPushButton* showTask = new QPushButton("Afficher la tâche");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listTask);
    layout->addWidget(showTask);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(showTask,SIGNAL(clicked()),this,SLOT(afficherTache()));
}

void TaskManagerWindow::afficherTache(){
    if(!listTask->currentItem() == 0){
        QListWidgetItem* selectedItem = listTask->currentItem();
        QString title = selectedItem->text();
        Note* t = NotesManager::getInstance().getNoteWithTitle(title);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(t,t->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    else {throw NotesException("Couldn't show the note..");}
}
