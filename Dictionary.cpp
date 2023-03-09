#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <fstream>



#include <cassert>

//#include "train.cpp"
#include <cctype>



#include <algorithm>

#include <iterator>
#include <set>
#include <map>
#include <cstring>
#include <list>
//#include "Random.hpp"
#include <locale>

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include <vector>
//#include "Ngram.cpp"


using namespace std;
struct anyStruct
{
short sVal;
float fVal;
double dVal;
short Empty;
char array[8];
};

class Dictionary {
public:
    friend QDataStream& operator<<(QDataStream &out, const anyStruct &any) {

            out << any.sVal;
            out << any.fVal;
            out << any.dVal;
            out << any.Empty;
            out.writeRawData(any.array,sizeof(any.array));
        return out;

    }
//friend std::ostream& operator<<(std::ostream& out, const Drob &d1);
    float** matrix;
    vector <char> tokens;
    vector <string> strings;
    vector<double> data;

    void fromFileToString(const string filename) {
        ifstream file(filename);
        string line;
        string myString;
        //string MyString;
        ofstream writefile("outtrain.txt", ios::out | ios::app);
        while (getline(file, line))
        {
            stringstream linestream(line);
            string item;
            while (getline(linestream, item, ' '))
            {
                //std::cout << item << endl;
                writefile << item << endl;
            }


        }
        file.close();
        writefile.close();

    }
    void makePreset (const string filename) {

         ofstream writefile(filename, ios::out | ios::app);
      //  writefile << "topology: 2 4 1" << endl;
  // buffer="topology: 2 4 1" << endl;
          writefile << "topology: 2 4 1" << endl;
        for(int i = 2000; i >= 0; --i)
            {
                char character= 'x';
                char character2= 'y';
                int n1 =  character - '0';
                int n2 =character - '0';
                int t = n1 + n2; // should be 0 or 1
                writefile<< "in: " <<n1 << ".0 " << n2 << ".0 " << endl;

                writefile << "out: " << t << ".0" << endl;
            }
//writefile.write(buffer);
writefile.close();
    }
    void makePreset2 (const string filename) {

         ofstream writefile(filename, ios::out | ios::app);
      //  writefile << "topology: 2 4 1" << endl;
  // buffer="topology: 2 4 1" << endl;
          writefile << "topology: 2 4 1" << endl;
        for(int i = 2000; i >= 0; --i)
            {
                char character= 'x';
                char character2= 'y';
                int n1 =  character - '0';
                int n2 =character - '0';
                int t = character+character2; // should be 0 or 1

                writefile<< "in: " <<n1 << ".0 " << n2 << ".0 " << endl;

                writefile << "out: " << t << ".0" << endl;
            }
//writefile.write(buffer);
writefile.close();
    }

    int array_search (QString word, char* arr, int size) {
    for(int i=0; i < size; i++) {
        if ((arr[i])==(word)) {
            return i;
        }
    }
return 0;
    }
    int array_search (QString word, QString* arr, int size) {
    for(int i=0; i < size; i++) {
        if ((arr[i])==(word)) {
            return i;
        }
    }
return 0;
    }
int fromWordtoIntEng (QString word) {
    char* arr_en = new char[27] {'\0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    //arr_en[10];//word = "win";
    int sum = 0;
    for (int i = 0; i < word.size(); i++) {
     // $sum += array_search($word[strlen($word)-$i-1], $arr_en)*pow(count($arr_en), $i);

        sum += array_search((QString) word[word.size()-i-1], arr_en, 27)*pow(26, i);
    }


return sum;
}
int fromWordtoIntRu (QString word) {
    QString *arr_en = new QString[32] {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ь", "ы", "ъ", "э", "ю"};

    //arr_en[10];//word = "win";
    int sum = 0;
    for (int i = 0; i < word.size(); i++) {
     // $sum += array_search($word[strlen($word)-$i-1], $arr_en)*pow(count($arr_en), $i);

        sum += array_search((QString) word[word.size()-i-1], arr_en, 32)*pow(26, i);
    }


return sum;
}

    void fromAssocition (const string filename) {

        ifstream file(filename);
        string line;
        string myString;
        //string MyString;
        ofstream writefile("/home/h1p3m/LSTM/assoc.txt", ios::out | ios::app);
        int a;
        string b,c;
        double d;
        std::vector<int> array;

          std::vector<string> barray;
          std::vector<string> carray;
           std::vector<double> darray;

        std::istringstream lin;
        string line0;
        getline(file, line0);
        for (string line; getline(file, line, '\t'); ) {
            lin.clear();
            lin.str(line);
            if (lin >> a >>b >> c>> d) {
                array.push_back(a);
                barray.push_back(b);
                carray.push_back(c);
                darray.push_back(d);
             //   darray.push_back(d);
                locale("ru_Ru.UTF8");
               //setlocale(LC_ALL, "RUSSIAN");
            writefile << a << " " << b << " " << c << " " << d<< endl;
            }
            else {
                std::cout << "WARNING: failed to decode line '" << line << "'\n";
            }
        }



        file.close();
        writefile.close();

//read?

        for (int a=0; a< array.size(); a++) {

            for (int b=0; b < barray.size(); b++) {

                for (int c=0; c < carray.size(); c++) {



            //cout <<array[a] << " " << barray[b] << " " <<carray[c] << endl;
        }
}
}
}


    int damerau_levenshtein_distance(std::string p_string1, std::string p_string2)
    {
        int l_string_length1 = p_string1.length();
        int l_string_length2 = p_string2.length();
        int d[l_string_length1+1][l_string_length2+1];

        int i;
        int j;
        int l_cost;

        for (i = 0;i <= l_string_length1;i++)
        {
            d[i][0] = i;
        }
        for(j = 0; j<= l_string_length2; j++)
        {
            d[0][j] = j;
        }
        for (i = 1;i <= l_string_length1;i++)
        {
            for(j = 1; j<= l_string_length2; j++)
            {
                if( p_string1[i-1] == p_string2[j-1] )
                {
                    l_cost = 0;
                }
                else
                {
                    l_cost = 1;
                }
                d[i][j] = std::min(
                d[i-1][j] + 1,                  // delete
                std::min(d[i][j-1] + 1,         // insert
                d[i-1][j-1] + l_cost)           // substitution
                );
                if( (i > 1) &&
                (j > 1) &&
                (p_string1[i-1] == p_string2[j-2]) &&
                (p_string1[i-2] == p_string2[j-1])
                )
                {
                d[i][j] = std::min(
                d[i][j],
                 d[i-2][j-2] + l_cost   // transposition
                );
                }
            }
        }
        return d[l_string_length1][l_string_length2];
    }

    void genAssociationSetWords(QString filename) {

        QStringList wordList;

              QFile f(filename);
              QFile writefile("/home/h1p3m/Adonai/wordsrate.txt");

              writefile.open(QIODevice::Append);
               //writefile << "topology: 2 4 1" << endl;
               writefile.write("topology: 1 9 1\n");
              if (f.open(QIODevice::ReadOnly))
              {
                  int qq=0;
      //            while(!f.atEnd())
                 while(!f.atEnd())
                  {
                      qq++;
                      //if(qq%3==0)
                          //qDebug()<<qq/3;
                      QString data;
                      data = f.readLine();

                      wordList = data.split('\t');
                      QString str = wordList.at(0);
                          QString second = wordList.at(1);
                          QString third= wordList.at(2);
    qDebug()<<str<< endl;
      qDebug()<<second<< endl;
      third.remove('\n');
      qDebug()<<third<< endl;
qDebug() << fromWordtoIntRu(second)<< endl;
qDebug() << fromWordtoIntRu(str) << endl;
qDebug () << str.toDouble();
qDebug () << third.toDouble();
 QTextStream out(&writefile);

//out<< "in: " << QVariant(fromWordtoInt(str)).toString()<< " " <<  QStringLiteral("%1").arg(str.toDouble())<< " " << third.toDouble() << endl;

//out << "out: " << (double) (1.*str.toDouble()/1.*second.toDouble()) << " " << (double)(1.*str.length()/1.*second.length())<< endl;


 out<< "in: " << fromWordtoIntRu(str) << ".0 "<< endl;

 out << "out: " << fromWordtoIntRu(str) << ".0 "<< endl;
 out<< "in: " << fromWordtoIntRu(second) << ".0 "<< endl;

 out << "out: " << fromWordtoIntRu(second) << ".0 "<< endl;




                  }

                  f.close();
              }
          writefile.close();

    }

    void genAssociationSet(QString filename) {

        QStringList wordList;

              QFile f(filename);
              QFile writefile("/home/h1p3m/Adonai/wordsrate.txt");

              writefile.open(QIODevice::Append);
               //writefile << "topology: 2 4 1" << endl;
               writefile.write("topology: 2 9 2\n");
              if (f.open(QIODevice::ReadOnly))
              {
                  int qq=0;
      //            while(!f.atEnd())
                 while(!f.atEnd())
                  {
                      qq++;
                      //if(qq%3==0)
                          //qDebug()<<qq/3;
                      QString data;
                      data = f.readLine();

                      wordList = data.split('\t');
                      QString str = wordList.at(0);
                          QString second = wordList.at(1);
                          QString third= wordList.at(2);
    qDebug()<<str<< endl;
      qDebug()<<second<< endl;
      third.remove('\n');
      qDebug()<<third<< endl;
qDebug() << fromWordtoIntRu(second)<< endl;
qDebug() << fromWordtoIntRu(str) << endl;
qDebug () << str.toDouble();
qDebug () << third.toDouble();
 QTextStream out(&writefile);

//out<< "in: " << QVariant(fromWordtoInt(str)).toString()<< " " <<  QStringLiteral("%1").arg(str.toDouble())<< " " << third.toDouble() << endl;

//out << "out: " << (double) (1.*str.toDouble()/1.*second.toDouble()) << " " << (double)(1.*str.length()/1.*second.length())<< endl;


 out<< "in: " << damerau_levenshtein_distance(str.toStdString(),second.toStdString()) << " " << third.toDouble() << endl;

 out << "out: " << damerau_levenshtein_distance(str.toStdString(),second.toStdString()) << " " << third.toDouble() << endl;


                  }

                  f.close();
              }
          writefile.close();

    }



    void genAssociationSetFromWords(QString filename, QString output) {

        QStringList wordList;

              QFile f(filename);
              QFile writefile(output);

              writefile.open(QIODevice::ReadWrite | QIODevice::Text);
               //writefile << "topology: 2 4 1" << endl;
               writefile.write("topology: 1 9 1\n");
              if (f.open(QIODevice::ReadOnly))
              {
                  int qq=0;
      //            while(!f.atEnd())
                 while(!f.atEnd())
                  {
                      qq++;
                      //if(qq%3==0)
                          //qDebug()<<qq/3;
                      QString data=f.readAll();
//                      QByteArray data2 = f.readAll();
//data=data2.fromHex(data2);
                      wordList = data.split(" ");;

                      QTextStream out(&writefile);
int place=0;

//QString * str;
while(place < (wordList.size()-1)) {
 QString str = wordList.at(place);
 if(wordList.at(place+1)!=0) {
    QString second = wordList.at(place+1);
    out<< "in: " << damerau_levenshtein_distance(str.toStdString(),second.toStdString()) << " " << endl;

    out << "out: " << damerau_levenshtein_distance(str.toStdString(),second.toStdString()) << " "<< endl;
                     place+=2;
 }


}





                  }

                  f.close();
              }
          writefile.close();

    }



    void genAssociationSetFromWordsRNN(QString filename, QString output, int topology) {

        QStringList wordList;

              QFile f(filename);
              QFile writefile(output);

              writefile.open(QIODevice::WriteOnly | QIODevice::Text);
               //writefile << "topology: 2 4 1" << endl;

              QString data;
              if (f.open(QIODevice::ReadOnly|QIODevice::Text))
              {

                       data=f.readAll();
                       f.close();

               }
//                      QByteArray data2 = f.readAll();
//data=data2.fromHex(data2);
                      wordList = data.split(" ");;

                      QTextStream out(&writefile);


                      out
                   //   <<"#include \"lstm.h\""<<endl
                      <<topology<<endl;
                    //  <<"{"<<endl;





int place=0;

//QString * str;
while(place < wordList.length()-1) {
 QString str = wordList.at(place);
 if((place+1)< wordList.length()-1) {
    QString second = wordList.at(place+1);

int i=place%2;
int j=place%26;


                             out<<"\tW_I["<<i<<"]["<<j<<"] = "<< damerau_levenshtein_distance(str.toStdString(),second.toStdString()) <<endl;
                             out<<"\tW_F["<<i<<"]["<<j<<"] = "<< damerau_levenshtein_distance(str.toStdString(),second.toStdString()) <<endl;
                             out<<"\tW_O["<<i<<"]["<<j<<"] = "<< damerau_levenshtein_distance(str.toStdString(),second.toStdString()) <<endl;
                             out<<"\tW_G["<<i<<"]["<<j<<"] = "<< damerau_levenshtein_distance(str.toStdString(),second.toStdString()) <<endl;



                            // i=place%26;
                             //j=place%26;

                             out<<"\tW_out["<<i<<"]["<<j<<"] = "<<damerau_levenshtein_distance(str.toStdString(),second.toStdString()) <<";"<<endl;




 //if (place < wordList.length()-1) return;


 } else {
    // f(wordList.at(place)==0) {
    // writefile.close();
  //f.close();

  return;

 }
place++;






 } //while data list end

 writefile.close();


 } //gen end







 void genAssociationSet2(QString filename) {

        QStringList wordList;

              QFile f(filename);
              QFile writefile("/home/h1p3m/Adonai/wordsrates.txt");

              writefile.open(QIODevice::Append);
               //writefile << "topology: 2 4 1" << endl;
               writefile.write("topology: 3 9 2\n");
              if (f.open(QIODevice::ReadOnly))
              {
                  int qq=0;
      //            while(!f.atEnd())
                 while(!f.atEnd())
                  {
                      qq++;
                      //if(qq%3==0)
                          //qDebug()<<qq/3;
                      QString data;
                      data = f.readLine();

                      wordList = data.split('\t');
                      QString str = wordList.at(0);
                          QString second = wordList.at(1);
                          QString third= wordList.at(2);
    qDebug()<<str<< endl;
      qDebug()<<second<< endl;
      third.remove('\n');
      qDebug()<<third<< endl;
qDebug() << fromWordtoIntRu(second)<< endl;
qDebug() << fromWordtoIntRu(str) << endl;
qDebug () << str.toDouble();
qDebug () << third.toDouble();
 QTextStream out(&writefile);

//out<< "in: " << QVariant(fromWordtoInt(str)).toString()<< " " <<  QStringLiteral("%1").arg(str.toDouble())<< " " << third.toDouble() << endl;

//out << "out: " << (double) (1.*str.toDouble()/1.*second.toDouble()) << " " << (double)(1.*str.length()/1.*second.length())<< endl;


 out<< "in: " << fromWordtoIntRu(str.toUtf8()) << ".0 " <<  fromWordtoIntRu(second.toUtf8())<< ".0 " << third.toUtf8().toDouble() << endl;

 out << "out: " << damerau_levenshtein_distance(str.toUtf8().toStdString(),second.toStdString()) << " " << (double)(1.*str.toUtf8().length()/1.*second.toUtf8().length())<< endl;


                  }


                  f.close();
              }
          writefile.close();

    }


};
