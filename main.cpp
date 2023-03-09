
#include <QCoreApplication>

typedef unsigned char BYTE;



#include <QDebug>
#include <QTime>
//#include "myneuro.h"
#include <QFile>
#include <QTextStream>
#include <lstm.h>

#include "Dictionary.cpp"
//#include"Ngram.cpp"
#include "Learn.h"
#include "lstm.h"
#include "subject.h"
#include <string>
#include <tuple>
//using namespace std;

#include <iterator>
#include <map>

#include <QProcess>
#include "library.h"
#include "dna.h"
using namespace std;


void Split(const string &input, const char spliter, vector<string> *out)
{
    int len = input.size();

    if (len == 0)
        return;
    if (out == NULL)
        return;

    string tmp;
    for (int i = 0; i < len; ++i)
    {
        if (input[i] != spliter)
        {
            // Append one char to the end of the string
            tmp.append(1, input[i]);
        }
        else
        {
            out->push_back(tmp);
            tmp.clear();
        }
    }

    if (tmp.size() != 0)
        out->push_back(tmp);
}

int ReadWordEmbedding(const string &file_name,
    map<string, int> *word_dict,
    vector<string>* id_to_word,
    vector<vector<double> > *word_embedding,
    int count)
{
    //ifstream fin(file_name.c_str());
QFile fin(file_name.c_str());


if (fin.open(QIODevice::ReadOnly))
{

        string buf;
//            while(!f.atEnd())
   while(!fin.atEnd())
    {
      // QString data;
       buf = fin.readLine().toStdString();

            vector<double> vec;
            vector<string> field;

            // get rid of \n
            if (buf.size() != 0 && (buf[buf.size() - 1] == '\n' || buf[buf.size() - 1] == '\r'))
            {
                buf = buf.substr(0, buf.size() - 1);
            }

            Split(buf, ' ', &field);
            if (word_dict->find(field[0]) == word_dict->end())
            {
                int id = word_dict->size();
                (*word_dict)[field[0]] = id;
                id_to_word->push_back(field[0]);
            }
            int embed_size = field.size() - 1;

            for (int i = 0; i < embed_size; i++)
              //  vec.push_back(atof(field[i + 1].c_str()));
                vec.push_back(QString::fromStdString(field[i + 1].c_str()).toDouble());
            word_embedding->push_back(vec);
            if (count != -1)
                if (word_embedding->size() > count)
                    break;
        }
    }
    else
        return -1;
    return 0;
}


void AddSpecialPOS(const string &POS,
    map<string, int>* pos_dict,
    vector<string>* id_to_pos)
{
    int cur_size = pos_dict->size();
    (*pos_dict)[POS] = cur_size;
    id_to_pos->push_back(POS);
}
bool IsChinese(const string &input)
{
    int len = input.size();

    for (int i = 0; i < len; i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
            return false;
        if (input[i] >= 'A' && input[i] <= 'Z')
            return false;
    }

    return true;
}
// Judge whether a string is a number
// number examples: 100; 100,000; 1/2; 1.25

bool IsDigit(const string &input, const string &POS, bool chinese)
{
    int len = input.size();
    bool digit_appear = false;

    if (len == 0)
        return false;

    if (chinese && POS == "CD")
        return true;

    for (int i = 0; i < len; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
            digit_appear = true;
        else if (input[i] == '.' || input[i] == ',' || input[i] == '-' || input[i] == '/')
            continue;
        else
            return false;
    }

    return digit_appear;
}

bool IsPunc(const string &POS)
{
    if (POS == "." || POS == "," || POS == ":" || POS == "``" || POS == "''" || POS == "PU")
        return true;
    return false;
}



// Read the dependency data and encode them
// return the encoded data and updated pos && edge type dict
int ReadDepData(QString file_name,
    map<string, int> &word_dict,
    map<string, int> *pos_dict,
    vector<string>* id_to_pos,
    //map<string, int> *edge_type_dict,
    //vector<string>* id_to_edge_type,
    vector<vector<SeqNode> > *out)
{
    vector<SeqNode> seq;
    SeqNode root;
    bool chinese = false;
    bool first = true;
    map<string, int>::iterator iter;



    QFile fin(file_name);


    // First Add <BOS> and <EOS> to the POS dict
    // So <BOS> id is always 0 and <EOS> 1
    if (pos_dict->find("<BOS>") == pos_dict->end())
        AddSpecialPOS("<BOS>", pos_dict, id_to_pos);
    if (pos_dict->find("<EOS>") == pos_dict->end())
        AddSpecialPOS("<EOS>", pos_dict, id_to_pos);

    // The ROOT node
    if (pos_dict->find("<ROOT>") == pos_dict->end())
        AddSpecialPOS("<ROOT>", pos_dict, id_to_pos);
    root.word = word_dict["<ROOT>"];
    root.pos = 2; // The ID for root
    //root.punc = false; // it's not punc
    //root.head = -1; // The head for root is meaningless
    //root.type = -1; // The head for root is meaningless
    //				//Add ROOT node
    seq.push_back(root);

    if (fin.open(QIODevice::ReadOnly))
    {
       // int qq=0;
            string buf;
    //            while(!f.atEnd())
       while(!fin.atEnd())
        {
          // QString data;
           buf = fin.readLine().toStdString();

            if (buf.size() != 0 && (buf[buf.size() - 1] == '\n' || buf[buf.size() - 1] == '\r'))
            {
                buf = buf.substr(0, buf.size() - 1);
            }

            if (buf.size() == 0) // end of sen
            {
                out->push_back(seq);
                seq.clear();
                // Add ROOT
                seq.push_back(root);
            }
            else
            {
                vector<string> field;
                SeqNode tmp;

                Split(buf, '\t', &field);

                if (first)
                {
                    chinese = IsChinese(field[0]);
                    first = false;
                }
                // encode word
                string word(field[0]);
                if (IsDigit(field[0], field[1], chinese))
                    word = "<NUM>";
                iter = word_dict.find(word);
                if (iter != word_dict.end())
                    tmp.word = iter->second;
                else
                    tmp.word = word_dict["<OOV>"];
                // encode pos
                iter = pos_dict->find(field[1]);
                if (iter != pos_dict->end())
                    tmp.pos = iter->second;
                else
                {
                    tmp.pos = pos_dict->size();
                    (*pos_dict)[field[1]] = tmp.pos;
                    id_to_pos->push_back(field[1]);
                }
                //// whether this is punc
                //tmp.punc = IsPunc(field[1]);
                //// save head
                //tmp.head = atoi(field[2].c_str());
                // encode edge type
                /*iter = edge_type_dict->find(field[3]);
                if (iter != edge_type_dict->end())
                    tmp.type = iter->second;
                else
                {
                    tmp.type = edge_type_dict->size();
                    (*edge_type_dict)[field[3]] = tmp.type;
                    id_to_edge_type->push_back(field[3]);
                }
                */
                seq.push_back(tmp);
            }
        }

        fin.close();
    }
    else
    {
        return -1;
    }

    return 0;
}

template <class AnyRange>class RangeIterator {
 public:
   // int curr_range=0;
 AnyRange* curr_range;
    RangeIterator() : curr_range_index(0) {}

  template <typename Container>
  void AddAnyRange(Container& c) {
    AnyRange any_range = { c.begin(), c.begin(), c.end() };
    ranges.push_back(any_range);
  }

  // Here's what the operator++() looks like, everything else omitted.
  int operator++() {

     while (true) {
       if (curr_range_index > ranges.size()) {
        // assert(false, "iterated too far");
         return 0;
       }
       AnyRange* any_range = ranges[curr_range_index];
       if (curr_range->curr != curr_range->end()) {
         ++(curr_range->curr);
         return *(curr_range->curr);
       }
       ++curr_range_index;
     }
  }


 private:
  std::vector<AnyRange> ranges;
  int curr_range_index;
};
BYTE GetAvailableMemory(){
    if ( QSysInfo::productType()=="ubuntu") {
                   QProcess p;
                   p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
                   p.waitForFinished();
                   QString memory = p.readAllStandardOutput();
                   QString system_info;
                   system_info.append(QString("%1").arg(memory.toLong() / 1024));

                   p.close();
                   qDebug()<< system_info;

                   bool ok;

                      unsigned long long int MaxMemory =system_info.toLong(&ok, 10)/1024;

                      unsigned long long int defMemory =system_info.toLong(&ok, 10)/1024;




                      std::vector<BYTE> tester;

                      while (true){
                          try {
                              tester.resize(MaxMemory*1073741824);
                          } catch (std::bad_alloc& e) {
                              tester.clear();
                              MaxMemory--;
                              return ((MaxMemory) >= defMemory) ? MaxMemory : 0;
                          }
                          MaxMemory++;
                      }
                      return MaxMemory;

    } else {
        return 0;
    }


    //


             //Settings::defaultmemory; // Gb

 }


class CTest
{
public:

    QString *string=new QString("YHVH");
    void FunTest()
    {
        qDebug()<<"this:"<<this<<endl;
    }


};
void FunTest()
{
    CTest* pt = NULL;
    pt->FunTest();
}



struct Base {}; // non-polymorphic
struct Derived : Base {};

struct Base2 { virtual void foo() {} }; // polymorphic
struct Derived2 : Base2 {};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //$kids=new Kids();
    //$preg_n_an_t=var_dump($kids);
    //$sev=7;
    // $father=new ParentClass();
    // $mother=new Child();
     //$free=new Kids("171727");
     //var_dump($free);


  //
        //
       // longTerm->genAssociationSet("/home/h1p3m/Adonai/sociation.tsv");
    //do not close

    //    longTerm->genAssociationSetWords("/home/h1p3m/Adonai/sociation.tsv");




       // ngram->getNgrams((string)"meow");
       // ngram->print();


 Dictionary *longTerm=new Dictionary;
        longTerm->genAssociationSetFromWordsRNN("/home/h1p3m/Adonai/alice0.txt", "/home/h1p3m/Adonai/alice0rate2.txt", 1);



QString *fp=new QString ("/home/h1p3m/Adonai/alice0rate2.txt");
                   //  RNN  lstm(2,1, fp);
RNN * lstm=new RNN(2,10, fp);


lstm->filetoChain("/home/h1p3m/Adonai/alice0.txt");
lstm->createMarkovChain();











          lstm->train(2, 0.25, "/home/h1p3m/Adonai/alice0rate2.txt", 2);


//int weight= lstm->rnn_predict(QDateTime::currentMSecsSinceEpoch()); // add error or coeff
      cout << endl<<"Start DNA"<< endl;
          DNA  dna;
          dna.Translation();
          dna.ShowDNA();

          cout << dna.dna;
 cout << dna.dna->toStdString() << endl;
 cout << dna.dna->toUtf8().constData() << endl;

 qDebug() << dna.dna->toLatin1() << endl;
  qDebug() << dna.dna->toLatin1().constData() << endl;
 qDebug() << dna.dna->toUtf8().constData() << endl;
 cout << endl<<"end"<< endl;
          double* weigth=lstm->getPredict();
          cout << weigth;
          qDebug()<<endl<< weigth<<endl;

         // void *p;
          auto i = reinterpret_cast<std::uintptr_t>(weigth);
                  qDebug()<<endl<< i<<endl;

string response= lstm->generateIdea(25, i);

qDebug() <<endl<<  QString::fromStdString(response).constData()<< endl;

qDebug() <<endl<<  QString::fromStdString(response)<< endl;


cout << response << endl;




Context ctx([] { std::cout << "Hello, world!\n";




    qDebug() <<endl<< 10;

});
ctx.run();



Context ctx2([i, lstm] { std::cout << "Hello, world!\n";




    qDebug() <<endl<< i;



    string response= lstm->generateIdea(25, i);

    qDebug() <<endl<<  QString::fromStdString(response).constData()<< endl;

    qDebug() <<endl<<  QString::fromStdString(response)<< endl;


    cout << response << endl;



    DNA * dna2;
    dna2->Translation();
    dna2->ShowDNA();



});
ctx2.run();

///ngram->createMarkovChain();


//qDebug() <<endl<<  QString::fromStdString(response).constData()<< endl;

//qDebug() <<endl<<  QString::fromStdString(response)<< endl;






//for(auto it = word_dict.cbegin(); it != word_dict.cend(); ++it){
   // std::cout << it->first << " " << it->second << "\n";
//}
//for(auto it = pos_dict->cbegin(); it != pos_dict->cend(); ++it){
  //  std::cout << it->first << " " << it->second << "\n";
//}
   // get<0>(tuple);

     // auto tuple=std::make_tuple(father->getChaintest());
       //     get<0>(tuple);

       //=new Kids<str;
      //QString str= QString("child_core");
       //free->create(10);

    //srand(time(NULL));
  // RNN rnn(10, 100);
    //RNN rnn();
    //rnn.train(10, 0.25);
  //  RNN* LSTM=new RNN(2, 1);
 //   cout << typeid(*LSTM).name() << endl;
        //cout << "Classname "<< << endl;
  //  p = &ob1;
    // LSTM->train(1,0.1);



   //  cout <<endl << "predict " << LSTM->rnn_predict(100) << endl;
//rnn->train();

    //rnn->train(10,0.1);




    return a.exec();
}
