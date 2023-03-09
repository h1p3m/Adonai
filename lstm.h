#ifndef LSTM_H
#define LSTM_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
//#include "train.cpp"
#include <QtGlobal>

#include <string>

#include <algorithm>
#include <map>


//test funct
//#include "Ngram.cpp"

//#include "node.hpp"
//#include "chain.hpp"

//#include "train.cpp"

//#include "ngram.cpp"
#include "Random.hpp"
#include <clocale>
#include <locale>
#include <QtMath>
#include <cstdio>
#include <cstdlib>
#include <QDebug>

//#include "include.h"

//new

#include <cstdlib>


#include <QTime>
#include <unordered_map>

#define alpha  0.1      //Learning rate
#define innode  2       //Enter the number of nodes, and 2 addends will be entered
#define hidenode  26    //Hide the number of nodes, store "carrying bits"
#define outnode  1      //Output the number of nodes, a predicted number will be output

#define binary_dim 8    //Maximum length of binary number

#define YDataRate 0.7
#define XDataRate 2
#define showLog 0
 #define writeFlag 1 // whether to update the parameters

#define randval(high) ( (double)Random::randomNumber() / 1000000 * high )
 #define uniform_plus_minus_one ((double) (2.0 * Random::randomNumber()) / ((double) 1000000 + 1.0) - 1.0) // uniform random distribution
#define nan uniform_plus_minus_one
using namespace std;
struct SeqNode
{
    int word;
    int pos;
    /*int type;
    int head;
    bool punc;*/
};
class RNN
{
public:

      double * predict;
      double* getPredict() {
          return this->predict;
      }

    std::vector<std::string> words_;
    std::unordered_map<std::string, std::vector<std::string>> markovChain_;
    vector<std::string> word_of_text;   // can be deleted after full cycle of learning
    void int2binary(int n, int *arr)
    {
        int i = 0;
        while(n)
        {
            arr[i++] = n % 2;
            n /= 2;
        }
        while(i < binary_dim)
            arr[i++] = 0;
    }
    QString filepath;
void setFilepath(QString fp) {
    this->filepath=fp;
}
     RNN();
    RNN(int flavor_num, int timestep); // flavor - number of weights?
    RNN(int flavor_num, int timestep, QString *filepath);

      //new file train

      void Split(const string &input, const char spliter, vector<string> *out);


      int ReadWordEmbedding(const string &file_name,
          map<string, int> *word_dict,
          vector<string>* id_to_word,
          vector<vector<double> > *word_embedding,
          int count=-1);





    virtual ~RNN();
      void backProp(double alphain, int j, int i, int k, int p, double e, int epoch, double *predict, double *x_batch_one, vector<double *> I_vector, vector<double *> O_vector, vector<double *> F_vector, vector<double *> G_vector, vector<double *> S_vector, vector<double *> h_vector, vector<double> y_delta);

      void train();
    void train(int loop_time, double alphain);


        //void train(int loop_time, double alphain, QString filepath);

    void reshape(int timestep, int flavor_num);
    int rnn_predict(int timelength);
    void writeData(int num);
    void intWeight1();
    void intWeight2();
    void intWeight3();
    void intWeight4();
    void intWeight5();
    void intWeight6();
    void intWeight7();
    void intWeight8();
    void intWeight9();
    void intWeight10();
    void intWeight11();
    void intWeight12();
    void intWeight13();
    void intWeight14();
    void intWeight15();
    void chooseVMtoInt(int num);




    void deleteLast();
    void loadData(int num, QString filepath);
    void train(int loop_time, double alphain, QString filepath, int topology);

        void createMarkovChain();
    bool filetoChain(QString filepath);

    string generateIdea(int numberOfWords, int weight);
private:
         double W_I [innode] [hidenode]; // weights connecting the input to the hidden layer units in the input gate value matrix
         double U_I [hidenode] [hidenode]; // a hidden layer connection weights the output of the input gate and the hidden layer units present value matrix
         double W_F [innode] [hidenode]; // weights connecting the input to the hidden layer unit forgotten door value matrix
         double U_F [hidenode] [hidenode]; // connecting the hidden layer and a hidden layer units present forgotten door weight matrix
         double W_O [innode] [hidenode]; // weights connecting the input to the hidden layer unit forgotten door value matrix
         double U_O [hidenode] [hidenode]; // a hidden layer connection weights and the current time value of the hidden layer matrix
         // the weight matrix for generating new memories;
         double W_G [innode] [hidenode];

    double U_G [hidenode] [hidenode]; // for generating a new weight matrix memories
         double W_out [hidenode] [outnode]; // weight matrix connecting the hidden layer to the output layer

         double * x; // layer 0 output values ​​directly from the set of input vectors
         //
         double * layer_1; // layer 1 output value
         double * y; // layer 2 output value

         int time_step; // current data bit with how many bits of data before training about how many columns of data
         int batch_size; // how many rows of training data
    int data_start;
    int thisFlavorNUM;


         double ** matX; // deformation of training data
    double **matY;

    //double VM_dwz[innode][outnode]; //new ellement test [][] numbers

    double maxY;
    double minY;

    double maxX;
    double minX;
};



#endif // LSTM
