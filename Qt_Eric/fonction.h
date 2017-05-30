#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <QString>
#include <QDebug>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include "oldversions.h"
using namespace std;

///Structure Date
struct date {
 date(int j = 0, int m = 0, int a = 0);
 int jour;
 int mois;
 int annee;
 void print() const;
};

///Class NotesException
class NotesException{
private:
    QString info;
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

///Class Note
class Note { //class abstraite
protected:
    QString id;
    QString title;
	date creation;
	date last_modif;
	OldVersions versions_anterieurs;

public:
    Note(const QString& id, const QString& titre) : id(id), title(titre) {}
    virtual ~Note();
    virtual QString getId() const { return id; }
    virtual QString getTitle() const { return title; }
	virtual OldVersions getVersionsAnt() const {return versions_anterieurs;}
    virtual void setTitle(const QString& t) {title=t;}
	virtual void setVersionsAnt(OldVersions va){versions_anterieurs = va;}
	virtual void addOldVersion (){ versions_anterieurs.addNote((*this).clone());} //Cela permet d'archiver une note dans l'attribut versions_anterieurs de la classe Note
	virtual void printOldVersion(){ versions_anterieurs.printVersions();} //Cette fonction permets d'afficher les versions anterieurs
	virtual void print() const = 0; //fonction virtuelle pure
	virtual Note* clone() const = 0;
    virtual QString getClassName() const = 0;
    virtual void save() = 0;
};

///Class Article
class Article : public Note {
private:
    QString text;
    Article & operator=(const Article & a);
    //Article(const Article & a); On l'enleve pour implementer le factory method
public:
    Article(const QString& id, const QString& titre, const QString& text);
    //Article(const Note& N1, const QString& text);
    QString getClassName() const {return "Article";}
	//Accesseurs:
    QString getText() const { return text; }
    void setText(const QString& t) {text=t;}
    void print() const;
    void save(){/*..*/};
    Article* clone() const;
    ~Article();
};

///Class Action
class Action {
    QString text;
public:
    //Action(const QString& s) : text(s) {}
    QString getClassName() const {return "Action";}
    QString getText() const {return text;}
    void setText(const QString& newText) {text = newText;}
    void print() const { qDebug() << " - " << text; }
};

///Class Task
class Task : public Note {
private:
    vector<Action> actions; //text qui definie les actions de la tache
    unsigned int priority;
    date deadline;
    QString status;
    //Task(const Task& t); On l'enleve pour implementer le factory method
    Task& operator=(const Task& t); //on met le operateur d'affection en prive pour empecher recopie par affectation

public:
    Task(const QString& id, const QString& title, const QString& s, const date& d, const unsigned int& p=0);
    void getActions() const;
    unsigned int getPriority() const {return priority;}
    date getDeadline() const {return deadline;}
    QString getStatus() const {return status;}
    //void setAction(const QString& act) {action = act;}
    void addAction(const QString& s);
    void setPriority(const unsigned int& p) {priority = p;}
    void setDeadline(const date& d) {deadline = d;}
    void setStatus(const QString& s) {status = s;}
    void print() const;
    Task* clone() const;
    void save(){/*..*/};
    ~Task();
    QString getClassName() const {return "Task";}
};




///Classe Multimedia (classe abstraite)
class Multimedia : public Note {
protected:
    QString description;
    QString imageFilename; //Pour l'instant je mets juste un nom de fichier
    Multimedia& operator=(const Multimedia& m);
    //Multimedia(const Multimedia& m);

public:
    Multimedia(const QString& id, const QString& title, const QString& desc, const QString& imgF);
    QString getDescription() const {return description;}
    QString getImageFilename() const {return imageFilename;}
    void setDescription(const QString& desc) {description = desc;}
    void setImageFilename(const QString& imgF) {imageFilename = imgF;}
    void print() const = 0; //methode virtuelle pure
    Multimedia* clone() const = 0;
    virtual void save() = 0;
    virtual ~Multimedia();
    virtual QString getClassName() const = 0;
};

///Classe Image
class Image : public Multimedia {
public:
    QString getClassName() const {return "Image";}
    Image(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    Image* clone() const;
    void save(){/*..*/};
    ~Image();

};

///Classe Audio
class Audio : public Multimedia {
public:
    QString getClassName() const {return "Audio";}
    Audio(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    Audio* clone() const;
    void save(){/*..*/};
    ~Audio();
};

///Classe Video
class Video : public Multimedia {
public:
    QString getClassName() const {return "Video";}
    Video(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    Video* clone() const;
    void save(){/*..*/};
    ~Video();
};





///Surchage d'operateurs
ostream& operator<<(ostream& f, const Note& n);

bool operator==(const Note& n1, const Note& n2);




#endif // FONCTION_H_INCLUDED
