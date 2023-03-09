#ifndef DNA_H
#define DNA_H

#include <QString>
#include <QFile>
#include <QChar>
#include <QDebug>
#include <iostream>
using namespace std;
class DNA
{
public:

    QString* dna =new QString("AGTCTGCCCTAG");
    //DNA();

  void Translation () {

      QString* dna_temp;
      dna_temp=this->dna;
     // *dna_temp->appemthis->dna;


      std::vector<std::pair<QString, QString>> replacements {
          { "A", "_" },
          { "G", "-"  },
          { "C", "G"  },
          { "T", "A"  },
          { "_", "T"  },
          // ...
          { "-", "C" }
      };

      for ( auto const &r : replacements) {
          dna_temp->replace(r.first, r.second);
             this->dna=dna_temp;
      }
       //this->dna->replace((first.), *second);
                //str_replace(array("A","G","C","T","_","-"), array("_","-","G","A","T","C"), $dna);

    this->dna=dna_temp;
  }

    void ShowDNA() {

       qDebug()<< this->dna;
        cout<< this->dna;
        qDebug()<< &this->dna;
         cout<<&this->dna;

    cout << this->dna->constData();

        qDebug() << this->dna->constData();
    }


};

#endif // DNA_H
