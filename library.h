#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QDebug>


class Book {

public:
    QString * author;
    QString * title;

    Book(QString * title_in, QString *author_in) {
        this->author = author_in;
        this->title  = title_in;
    }

    QString * getAuthor() {
        return this->author;
    }

    QString * getTitle() {
        return this->title;
    }

  QString *getAuthorAndTitle() {
      QString* temp;
      temp->append(this->getTitle());

      temp->append(" by ");
         temp->append(this->getAuthor());
        return temp;
    }
};

class Publication {
 // определяем правило, что все публикации должны печататься, т.е. иметь метод do_print()
public:

    virtual void do_print();
};

class News : public Publication {
 // переопределяем абстрактный метод печати
 public:
    void do_print() {
  qDebug()<< "\tНовость\n";
  //...
 }
};
class Announcement:public Publication {
 // переопределяем абстрактный метод печати

    public:
       void do_print() {
     qDebug()<<  "\tОбъявление\n";
     //...
    }
   };






class StrategyInterface {
public:
    QString* showTitle( Book* book_in);
};

class StrategyCaps: public StrategyInterface {
public:
    QString* showTitle(Book* book_in) {
        QString * title = book_in->getTitle();

        //this->titleCount++;
        *title=title->append(title->toUpper());

        //title->toUppper(title);
        return title;
    }
};

class StrategyExclaim: public StrategyInterface {
public:
    QString* showTitle(Book * book_in) {
        QString * title = book_in->getTitle();
        //this->titleCount++;
        *title=title->replace(' ','!');

        return title;
    }

};

class StrategyStars: public StrategyInterface {
public:
    QString* showTitle(Book * book_in) {
        QString * title = book_in->getTitle();
        //this->titleCount++;
        *title=title->replace(' ','*');

        return title;
    }
};


class StrategyContext {

private:

    StrategyInterface* strategy = nullptr;
    // list is not instantiated at construct time
public:

    StrategyContext(QString strategy_ind_id) {
        if( strategy_ind_id == "C" )
        {
            this->strategy = new StrategyCaps();


        }
        else if( strategy_ind_id== "E" )
        {
            this->strategy = new StrategyExclaim();

        }
        else if( strategy_ind_id== "S" )
        {
           this->strategy = new StrategyStars();
        }

        }

 /**
    public function showBookTitle($book) {
      return @$this->strategy->showTitle($book);
    }
    */
};


class Context {
public:
    template<typename F>
    explicit Context(F strategy) : strategy(std::move(strategy)) { }

    void run() { strategy(); }

private:
    std::function<void()> strategy;
};










class Library
{
public:
    Library();
};

#endif // LIBRARY_H
