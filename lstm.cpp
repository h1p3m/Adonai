
#include "lstm.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <QFile>
#include <memory>
#include <memory_resource>
#include <QSharedMemory>
using namespace std;

#define Day_Num 6

 // activation function
double sigmoid(double x)
{
    return 1.0 / (1.0 + qExp(-x));
}

 // derivative activation function, y is the value of the activation function
double dsigmoid(double y)
{
    return y * (1.0 - y);
}

 // tanh derivative, y is a value tanh
double dtanh(double y)
{
    y = qTan(y);
    return 1.0 - y * y;
}

 void winit (double w [], int n) // initializes weights
{
    for(int i=0; i<n; i++)
                 w [i] = ((2.0 * Random::randomNumber()) / ((double) 1000000 + 1.0) - 1.0); // uniform random distribution
}
void RNN::chooseVMtoInt(int num)
{
    switch(num){
        case 1: intWeight1(); break;
        case 2: intWeight2(); break;
        case 3: intWeight3(); break;
        case 4: intWeight4(); break;
        case 5: intWeight5(); break;
        case 6: intWeight6(); break;
        case 7: intWeight7(); break;
        case 8: intWeight8(); break;
        case 9: intWeight9(); break;
        case 10: intWeight10(); break;
        case 11: intWeight11(); break;
        case 12: intWeight12(); break;
        case 13: intWeight13(); break;
        case 14: intWeight14(); break;
        case 15: intWeight15(); break;
    }

}
RNN::RNN()
{
    x = new double[innode];
    y = new double[outnode];
    winit((double*)W_I, innode * hidenode);
    winit((double*)U_I, hidenode * hidenode);
    winit((double*)W_F, innode * hidenode);
    winit((double*)U_F, hidenode * hidenode);
    winit((double*)W_O, innode * hidenode);
    winit((double*)U_O, hidenode * hidenode);
    winit((double*)W_G, innode * hidenode);
    winit((double*)U_G, hidenode * hidenode);
    winit((double*)W_out, hidenode * outnode);
}

RNN::RNN(int flavor_num, int timestep)
{
         batch_size = Day_Num / timestep; // 2-dimensional array of rows
    time_step = timestep;
    thisFlavorNUM = flavor_num;

    reshape(time_step, flavor_num);

    x = new double[innode];
    y = new double[outnode];

    chooseVMtoInt(flavor_num);





    winit((double*)W_I, innode * hidenode);
//
    winit((double*)U_I, hidenode * hidenode);
//
    winit((double*)W_F, innode * hidenode);
//
    winit((double*)U_F, hidenode * hidenode);
//
    winit((double*)W_O, innode * hidenode);
//
    winit((double*)U_O, hidenode * hidenode);
//
    winit((double*)W_G, innode * hidenode);
//
    winit((double*)U_G, hidenode * hidenode);
//
    winit((double*)W_out, hidenode * outnode);
    //load input and output vectors
    loadData(flavor_num,this->filepath);

}

RNN::RNN(int flavor_num, int timestep, QString *filepath)
{
         batch_size = Day_Num / timestep; // 2-dimensional array of rows
    time_step = timestep;
    thisFlavorNUM = flavor_num;

    reshape(time_step, flavor_num);

    x = new double[innode];
    y = new double[outnode];

    chooseVMtoInt(flavor_num);






//
    winit((double*)U_I, hidenode * hidenode);

//
    winit((double*)U_F, hidenode * hidenode);
//

//
    winit((double*)U_O, hidenode * hidenode);
//

//
    winit((double*)U_G, hidenode * hidenode);
//
  //  winit((double*)W_out, hidenode * outnode);
  //winit((double*)W_O, innode * hidenode);
    //    winit((double*)W_I, innode * hidenode);
      //  winit((double*)W_G, innode * hidenode);
    //winit((double*)W_F, innode * hidenode);
    //load input and output vectors
   // setFilepath(*filepath);
    loadData(flavor_num,*filepath);

}

RNN::~RNN()
{
    delete x;
    delete y;
    delete []matX;
    delete []matY;
}


void RNN::createMarkovChain() {
    for (size_t i = 0; i < this->words_.size() - 1; ++i)
      this->markovChain_[this->words_[i]].push_back(this->words_[i + 1]);

}
bool RNN::filetoChain (QString filepath) {

    QFile f(filepath);
    //(fileName);

    QString data;
     QStringList wordList;
    if (f.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        int qq=0;
//            while(!f.atEnd())
       while(!f.atEnd())
        {

           data = f.readLine();

           wordList = data.split(' ');
           foreach(QString word, wordList) {
this->words_.push_back( word.toUtf8().constData());

           }

       }
       }
  f.close();

  this->createMarkovChain();

  return true;

}

string RNN::generateIdea(int numberOfWords, int weight)
{
    int rand_num= weight;
  std::string randomWord = this->words_[rand_num % this->words_.size()];
  std::string sentence = randomWord;

  for (int i = 0; i < numberOfWords; ++i)
  {
    randomWord = this->markovChain_[randomWord][ weight % this->markovChain_[randomWord].size()];
    sentence += " " + randomWord;
  }

  return sentence + '\n';
}
void RNN::train()
{

        int epoch, i, j, k, m, p;
        vector<double*> I_vector;      //Enter the gate
        vector<double*> F_vector;      //The Forgotten Door
        vector<double*> O_vector;      //Output gate
        vector<double*> G_vector;      //New memory
        vector<double*> S_vector;      //Status value
        vector<double*> h_vector;      //output value
        vector<double> y_delta;        //Save the partial derivative of the error about the output layer

        for(epoch=0; epoch<11000; epoch++)  //Training times
        {
            double e = 0.0;  //error

            int predict[binary_dim];               //Save the predicted value generated each time
         // memset_s(predict, 0, sizeof(predict));

            int a_int = (int)randval(1000000/2.0);  // randomly generate an addend a
            int a[binary_dim];
            int2binary(a_int, a);                 //Convert to binary number

            int b_int = (int)randval(1000000/2.0);  // randomly generate another addend b
            int b[binary_dim];
            int2binary(b_int, b);                 //Convert to binary number

            int c_int = a_int + b_int;            //True and c
            int c[binary_dim];
            int2binary(c_int, c);                 //Convert to binary number

            //There is no previous hidden layer at time 0, so initialize a all 0
            double *S = new double[hidenode];     //Status value
            double *h = new double[hidenode];     //output value

            for(i=0; i<hidenode; i++)
            {
                S[i] = 0;
                h[i] = 0;
            }
            S_vector.push_back(S);
            h_vector.push_back(h);

            //Forward propagation
            for(p=0; p<binary_dim; p++)           //Loop through the binary array, starting from the lowest bit
            {
                x[0] = a[p];
                x[1] = b[p];
                double t = (double)c[p];          //Actual value
                double *in_gate = new double[hidenode];     //Enter the gate
                double *out_gate = new double[hidenode];    //Output gate
                double *forget_gate = new double[hidenode]; //The Forgotten Door
                double *g_gate = new double[hidenode];      //New memory
                double *state = new double[hidenode];       //Status value
                double *h = new double[hidenode];           //Hidden layer output value

                for(j=0; j<hidenode; j++)
                {
                    //The input layer is broadcast to the hidden layer
                    double inGate = 0.0;
                    double outGate = 0.0;
                    double forgetGate = 0.0;
                    double gGate = 0.0;
                    double s = 0.0;

                    for(m=0; m<innode; m++)
                    {
                        inGate += x[m] * W_I[m][j];
                        outGate += x[m] * W_O[m][j];
                        forgetGate += x[m] * W_F[m][j];
                        gGate += x[m] * W_G[m][j];
                    }

                    double *h_pre = h_vector.back();
                    double *state_pre = S_vector.back();
                    for(m=0; m<hidenode; m++)
                    {
                        inGate += h_pre[m] * U_I[m][j];
                        outGate += h_pre[m] * U_O[m][j];
                        forgetGate += h_pre[m] * U_F[m][j];
                        gGate += h_pre[m] * U_G[m][j];
                    }

                    in_gate[j] = sigmoid(inGate);
                    out_gate[j] = sigmoid(outGate);
                    forget_gate[j] = sigmoid(forgetGate);
                    g_gate[j] = sigmoid(gGate);

                    double s_pre = state_pre[j];
                    state[j] = forget_gate[j] * s_pre + g_gate[j] * in_gate[j];
                    h[j] = in_gate[j] * qTan(state[j]);
                }


                for(k=0; k<outnode; k++)
                {
                    //The hidden layer propagates to the output layer
                    double out = 0.0;
                    for(j=0; j<hidenode; j++)
                        out += h[j] * W_out[j][k];
                    y[k] = sigmoid(out);               //The output of each unit of the output layer
                }

                predict[p] = (int)qFloor(y[0] + 0.5);   //Record predicted value

                //Save the hidden layer for next calculation
                I_vector.push_back(in_gate);
                F_vector.push_back(forget_gate);
                O_vector.push_back(out_gate);
                S_vector.push_back(state);
                G_vector.push_back(g_gate);
                h_vector.push_back(h);

                //Save the partial derivative of the standard error with respect to the output layer
                y_delta.push_back( (t - y[0]) * dsigmoid(y[0]) );
                e += abs(t - y[0]);          //error
            }

            //Error back propagation

            //Hidden layer deviation, calculated by the hidden layer error at a later point in time and the current output layer error
            double h_delta[hidenode];
            double *O_delta = new double[hidenode];
            double *I_delta = new double[hidenode];
            double *F_delta = new double[hidenode];
            double *G_delta = new double[hidenode];
            double *state_delta = new double[hidenode];
            //A hidden layer error after the current time
            double *O_future_delta = new double[hidenode];
            double *I_future_delta = new double[hidenode];
            double *F_future_delta = new double[hidenode];
            double *G_future_delta = new double[hidenode];
            double *state_future_delta = new double[hidenode];
            double *forget_gate_future = new double[hidenode];
            for(j=0; j<hidenode; j++)
            {
                O_future_delta[j] = 0;
                I_future_delta[j] = 0;
                F_future_delta[j] = 0;
                G_future_delta[j] = 0;
                state_future_delta[j] = 0;
                forget_gate_future[j] = 0;
            }
            for(p=binary_dim-1; p>=0 ; p--)
            {
                x[0] = a[p];
                x[1] = b[p];

                //Current hidden layer
                double *in_gate = I_vector[p];     //Enter the gate
                double *out_gate = O_vector[p];    //Output gate
                double *forget_gate = F_vector[p]; //The Forgotten Door
                double *g_gate = G_vector[p];      //New memory
                double *state = S_vector[p+1];     //Status value
                double *h = h_vector[p+1];         //Hidden layer output value

                //Previous hidden layer
                double *h_pre = h_vector[p];
                double *state_pre = S_vector[p];

                for(k=0; k<outnode; k++)  //For each output unit in the network, update the weight
                {
                    //Update the connection rights between the hidden layer and the output layer
                    for(j=0; j<hidenode; j++)
                        W_out[j][k] += alpha * y_delta[p] * h[j];
                }

                //For each hidden unit in the network, calculate the error term and update the weight
                for(j=0; j<hidenode; j++)
                {
                    h_delta[j] = 0.0;
                    for(k=0; k<outnode; k++)
                    {
                        h_delta[j] += y_delta[p] * W_out[j][k];
                    }
                    for(k=0; k<hidenode; k++)
                    {
                        h_delta[j] += I_future_delta[k] * U_I[j][k];
                        h_delta[j] += F_future_delta[k] * U_F[j][k];
                        h_delta[j] += O_future_delta[k] * U_O[j][k];
                        h_delta[j] += G_future_delta[k] * U_G[j][k];
                    }

                    O_delta[j] = 0.0;
                    I_delta[j] = 0.0;
                    F_delta[j] = 0.0;
                    G_delta[j] = 0.0;
                    state_delta[j] = 0.0;

                    //The correction error of the hidden layer
                    O_delta[j] = h_delta[j] * qTan(state[j]) * dsigmoid(out_gate[j]);
                    state_delta[j] = h_delta[j] * out_gate[j] * dtanh(state[j]) +
                                     state_future_delta[j] * forget_gate_future[j];
                    F_delta[j] = state_delta[j] * state_pre[j] * dsigmoid(forget_gate[j]);
                    I_delta[j] = state_delta[j] * g_gate[j] * dsigmoid(in_gate[j]);
                    G_delta[j] = state_delta[j] * in_gate[j] * dsigmoid(g_gate[j]);

                    //Update the weight between the previous hidden layer and the current hidden layer
                    for(k=0; k<hidenode; k++)
                    {
                        U_I[k][j] += alpha * I_delta[j] * h_pre[k];
                        U_F[k][j] += alpha * F_delta[j] * h_pre[k];
                        U_O[k][j] += alpha * O_delta[j] * h_pre[k];
                        U_G[k][j] += alpha * G_delta[j] * h_pre[k];
                    }

                    //Update the connection rights between the input layer and the hidden layer
                    for(k=0; k<innode; k++)
                    {
                        W_I[k][j] += alpha * I_delta[j] * x[k];
                        W_F[k][j] += alpha * F_delta[j] * x[k];
                        W_O[k][j] += alpha * O_delta[j] * x[k];
                        W_G[k][j] += alpha * G_delta[j] * x[k];
                    }

                }

                if(p == binary_dim-1)
                {
                    delete  O_future_delta;
                    delete  F_future_delta;
                    delete  I_future_delta;
                    delete  G_future_delta;
                    delete  state_future_delta;
                    delete  forget_gate_future;
                }

                O_future_delta = O_delta;
                F_future_delta = F_delta;
                I_future_delta = I_delta;
                G_future_delta = G_delta;
                state_future_delta = state_delta;
                forget_gate_future = forget_gate;
            }
            delete  O_future_delta;
            delete  F_future_delta;
            delete  I_future_delta;
            delete  G_future_delta;
            delete  state_future_delta;

            if(epoch % 1000 == 0)
            {
                cout << "error：" << e << endl;
                cout << "pred：" ;
                for(k=binary_dim-1; k>=0; k--)
                    cout << predict[k];
                cout << endl;

                cout << "true：" ;
                for(k=binary_dim-1; k>=0; k--)
                    cout << c[k];
                cout << endl;

                int out = 0;
                for(k=binary_dim-1; k>=0; k--)
                    out += predict[k] * pow(2, k);
                cout << a_int << " + " << b_int << " = " << out << endl << endl;
            }

            for(i=0; i<I_vector.size(); i++)
                delete I_vector[i];
            for(i=0; i<F_vector.size(); i++)
                delete F_vector[i];
            for(i=0; i<O_vector.size(); i++)
                delete O_vector[i];
            for(i=0; i<G_vector.size(); i++)
                delete G_vector[i];
            for(i=0; i<S_vector.size(); i++)
                delete S_vector[i];
            for(i=0; i<h_vector.size(); i++)
                delete h_vector[i];

            I_vector.clear();
            F_vector.clear();
            O_vector.clear();
            G_vector.clear();
            S_vector.clear();
            h_vector.clear();
            y_delta.clear();
        }

        if(writeFlag)
            writeData(thisFlavorNUM);
}


void RNN::backProp(double alphain, int j, int i,  int k,int p, double e, int epoch,   double * predict, double* x_batch_one,   vector<double*> I_vector,   vector<double*> O_vector,  vector<double*> F_vector,  vector<double*> G_vector,  vector<double*> S_vector,  vector<double*> h_vector, vector<double> y_delta) {


    // error back-propagation

    // hidden layer bias error by a time point after the current error of the hidden layer and output layer is calculated current
double h_delta[hidenode];
//shared_ptr<double *> *O_delta(double [hidenode]);
double *O_delta = new double[hidenode];
double *I_delta = new double[hidenode];
double *F_delta = new double[hidenode];
double *G_delta = new double[hidenode];
double *state_delta = new double[hidenode];
 //   A hidden layer error after the // current time
double *O_future_delta = new double[hidenode];
double *I_future_delta = new double[hidenode];
double *F_future_delta = new double[hidenode];
double *G_future_delta = new double[hidenode];
double *state_future_delta = new double[hidenode];
double *forget_gate_future = new double[hidenode];
for(j=0; j<hidenode; j++)
{
O_future_delta[j] = 0;
I_future_delta[j] = 0;
F_future_delta[j] = 0;
G_future_delta[j] = 0;
state_future_delta[j] = 0;
forget_gate_future[j] = 0;
}

for(p=time_step-1; p>=0 ; p--)
{
x[0] = x_batch_one[p];

            // currently hidden layer
            double * in_gate = I_vector [p]; // input gate
            double * out_gate = O_vector [p]; // output gates
            double * forget_gate = F_vector [p]; // forgotten door
            double * g_gate = G_vector [p]; // New Memory
            double * state = S_vector [p + 1]; // state value
            double * h = h_vector [p + 1]; // hidden layer output values

            // before a hidden layer
double *h_pre = h_vector[p];
double *state_pre = S_vector[p];

            for (k = 0; k <outnode; k ++) // for each network output units, the weights are updated
{
                    // update the connection weights between the hidden layer and output layer
   for(j=0; j<hidenode; j++)
       W_out[j][k] += alphain * y_delta[p] * h[j];
}

            // hide for each network unit, calculate an error term, and the weights are updated
for(j=0; j<hidenode; j++)
{
   h_delta[j] = 0.0;
   for(k=0; k<outnode; k++)
   {
       h_delta[j] += y_delta[p] * W_out[j][k];
   }
   for(k=0; k<hidenode; k++)
   {
       h_delta[j] += I_future_delta[k] * U_I[j][k];
       h_delta[j] += F_future_delta[k] * U_F[j][k];
       h_delta[j] += O_future_delta[k] * U_O[j][k];
       h_delta[j] += G_future_delta[k] * U_G[j][k];
   }

   O_delta[j] = 0.0;
   I_delta[j] = 0.0;
   F_delta[j] = 0.0;
   G_delta[j] = 0.0;
   state_delta[j] = 0.0;

                    // correct errors of the hidden layer
   O_delta[j] = h_delta[j] * qTan(state[j]) * dsigmoid(out_gate[j]);
   state_delta[j] = h_delta[j] * out_gate[j] * dtanh(state[j]) +
                    state_future_delta[j] * forget_gate_future[j];
   F_delta[j] = state_delta[j] * state_pre[j] * dsigmoid(forget_gate[j]);
   I_delta[j] = state_delta[j] * g_gate[j] * dsigmoid(in_gate[j]);
                    G_delta [j] = state_delta [j] * in_gate [j] * dtanh (g_gate [j]); // where the modified dtanh

                    // update before a weights between the hidden layer and the hidden layer now
   for(k=0; k<hidenode; k++)
   {
       U_I[k][j] += alphain * I_delta[j] * h_pre[k];
       U_F[k][j] += alphain * F_delta[j] * h_pre[k];
       U_O[k][j] += alphain * O_delta[j] * h_pre[k];
       U_G[k][j] += alphain * G_delta[j] * h_pre[k];
   }

                    // update the connection weights between the input layer and the hidden layer
   for(k=0; k<innode; k++)
   {
       W_I[k][j] += alphain * I_delta[j] * x[k];
       W_F[k][j] += alphain * F_delta[j] * x[k];
       W_O[k][j] += alphain * O_delta[j] * x[k];
       W_G[k][j] += alphain * G_delta[j] * x[k];
   }

}

if(p == time_step-1)
{
    if(O_future_delta!=nullptr)
   delete[]  O_future_delta;
    if(F_future_delta!=nullptr)
   delete[]  F_future_delta;
   if(I_future_delta!=nullptr)
    delete[]  I_future_delta;
   if(G_future_delta!=nullptr)
   delete[]  G_future_delta;
   if(state_future_delta!=nullptr)
   delete[]  state_future_delta;
   if( forget_gate_future!=nullptr)
  delete[]  forget_gate_future;
}

O_future_delta = O_delta;
F_future_delta = F_delta;
I_future_delta = I_delta;
G_future_delta = G_delta;
state_future_delta = state_delta;
forget_gate_future = forget_gate;
}

//delete[]  &O_future_delta;
//delete  O_future_delta;
//delete  F_future_delta;
//delete I_future_delta;

  //  delete  I_future_delta;

//delete state_future_delta;

if(epoch % 1000 == 0 && showLog)
{
cout << "error：" << e << endl;
cout << "x:\t" ;
for(int l=0; l<batch_size; l++)
{
   for(k=0; k<time_step; k++) {
       cout << matX[l][k]<<"\t";

}
}
cout << "\nreal:\t" ;
for(int l=0; l<batch_size; l++)
{
   for(k=0; k<time_step; k++)
       //cout << setprecision(3) << matY[l][k]<<"\t";
   cout << matY[l][k]<<"\t";

}

cout << "\npred:\t" ;
for(k=0; k<time_step; k++)
  // cout << setprecision(3) << predict[k]<<"\t";
   cout <<  predict[k]<<"\t";
cout << endl;
this->predict[k]=predict[k];

}
            // delete predict;

for(i=0; i<(int)I_vector.size(); i++)
//delete[] I_vector[i];
for(i=0; i<(int)F_vector.size(); i++)
//delete[] F_vector[i];
for(i=0; i<(int)O_vector.size(); i++)
//delete[] O_vector[i];
for(i=0; i<(int)G_vector.size(); i++)
//delete[] G_vector[i];
for(i=0; i<(int)S_vector.size(); i++)
//delete[] S_vector[i];
for(i=0; i<(int)h_vector.size(); i++)
//delete[] h_vector[i];

I_vector.clear();
F_vector.clear();
O_vector.clear();
G_vector.clear();
S_vector.clear();
h_vector.clear();
y_delta.clear();


}



/*
 x is an x-axis data, two-dimensional data, how much data combined by the timestep sized
*/

void RNN::train(int loop_time, double alphain)
{
    int epoch, i, j, k, m, p, batch_count;
    batch_count = 0;
         // training time will be cleared once these vector
         vector <double *> I_vector; // input gate
         vector <double *> F_vector; // forgotten door
         vector <double *> O_vector; // output gates
         vector <double *> G_vector; // new memories
         vector <double *> S_vector; // state value
         vector <double *> h_vector; // output value
         vector <double> y_delta; // save the error regarding the output layer deflector





         for (epoch = 0; epoch <loop_time; epoch ++) // number of training
    {
                 double e = 0.0; // Error

                 double * predict = new double [time_step]; // save each generated predicted value to generate a set of predicted values ​​for each batch
    //memset disable
                 //memset(predict, 0, sizeof(int)*time_step);

                 // 0 before the time is not hidden layer, so a full initialization is 0
                 double * S = new double [hidenode]; // state value
                 double * h = new double [hidenode]; // output value

        for(i=0; i<hidenode; i++)
        {
            S[i] = 0;
            h[i] = 0;
        }
        S_vector.push_back(S);
        h_vector.push_back(h);

        double *x_batch_one = matX[batch_count];
        double *y_batch_one = matY[batch_count];
        batch_count++;
        if(batch_count >= batch_size)
            batch_count = 0;

                 // forward propagation
                 for (p = 0; p <time_step; p ++) // iterate a value inside the batch
        {

            x[0] = x_batch_one[p];
                         double t = (double) y_batch_one [p]; // predicted y values

                         double * in_gate = new double [hidenode]; // input gate
                         double * out_gate = new double [hidenode]; // output gates
                         double * forget_gate = new double [hidenode]; // forgotten door
                         double * g_gate = new double [hidenode]; // New Memory
                         double * state = new double [hidenode]; // state value
                         double * h = new double [hidenode]; // hidden layer output values

            for(j=0; j<hidenode; j++)
            {
                                 // input layer to the hidden layer broadcast
                double inGate = 0.0;
                double outGate = 0.0;
                double forgetGate = 0.0;
                double gGate = 0.0;

                                 for (m = 0; m <innode; m ++) // input gate, forgetting gate, an output gate,
                {
                                         inGate += x [m] * W_I [m] [j]; // input gate
                                         outGate += x [m] * W_O [m] [j]; // output gates
                                         forgetGate += x [m] * W_F [m] [j]; // forgotten door
                                         gGate += x [m] * W_G [m] [j]; // create new memory
                }

                                 double * h_pre = h_vector.back (); // return the end value, the value of a hidden layer weights
                double *state_pre = S_vector.back();//
                for(m=0; m<hidenode; m++)
                {
                                         inGate += h_pre [m] * U_I [m] [j]; // on a hidden layer weights and the present input hidden layer
                    outGate += h_pre[m] * U_O[m][j];
                    forgetGate += h_pre[m] * U_F[m][j];
                    gGate += h_pre[m] * U_G[m][j];
                }

                in_gate[j] = sigmoid(inGate);
                out_gate[j] = sigmoid(outGate);
                forget_gate[j] = sigmoid(forgetGate);
                g_gate [j] = qTan (gGate); // g_gate [j] = sigmoid (gGate); // this modified Sigmoid!

                double s_pre = state_pre[j];
                state[j] = forget_gate[j] * s_pre + g_gate[j] * in_gate[j];
                                 h [j] = out_gate [j] * qTan (state [j]); // h [j] = in_gate [j] * tanh (state [j]); out the modified
            }

                         // the hidden layer to the output layer propagated
            for(k=0; k<outnode; k++)
            {

                double out = 0.0;
                for(j=0; j<hidenode; j++)
                    out += h[j] * W_out[j][k];
                                 y [k] = sigmoid (out); // for each output layer unit outputs a regression problem if it is done without actually should sigmoid function
            }

 // predict [p] = (int) floor (y [0] + 0.5); // record the predicted value
                         predict [p] = y [0]; // record the predicted value

                         // Save the hidden layer to the next calculation
            I_vector.push_back(in_gate);
            F_vector.push_back(forget_gate);
            O_vector.push_back(out_gate);
            S_vector.push_back(state);
            G_vector.push_back(g_gate);
            h_vector.push_back(h);

                         // save deflector t standard error regarding the output layer is the actual value
            y_delta.push_back( (t - y[0]) * dsigmoid(y[0]) );
                         //e += fabs (1.0*(t - y[0])); // Error
            e += abs (1.0*(t - y[0]));
        }


//back prop error start


          backProp(alpha, j, i, k, p, e, epoch, predict, x_batch_one,  I_vector, O_vector, F_vector, G_vector,S_vector,  h_vector,  y_delta );

         }



//back prop end


         // loop for training times
cout << endl << "Was writed file data" << endl;
    if(writeFlag)
        writeData(thisFlavorNUM);

}





void RNN::train(int loop_time, double alphain, QString filepath, int topology)
{
    int epoch, i, j, k, m, p, batch_count;
    batch_count = 0;
         // training time will be cleared once these vector
         vector <double *> I_vector; // input gate
         vector <double *> F_vector; // forgotten door
         vector <double *> O_vector; // output gates
         vector <double *> G_vector; // new memories
         vector <double *> S_vector; // state value
         vector <double *> h_vector; // output value
         vector <double> y_delta; // save the error regarding the output layer deflector




         for (epoch = 0; epoch <loop_time; epoch ++) // number of training
    {
                 double e = 0.0; // Error

                 double * predict = new double [time_step]; // save each generated predicted value to generate a set of predicted values ​​for each batch
    //memset disable
                 //memset(predict, 0, sizeof(int)*time_step);

                 // 0 before the time is not hidden layer, so a full initialization is 0
                 double * S = new double [hidenode]; // state value
                 double * h = new double [hidenode]; // output value

        for(i=0; i<hidenode; i++)
        {
            S[i] = 0;
            h[i] = 0;
        }
        S_vector.push_back(S);
        h_vector.push_back(h);

        double *x_batch_one = matX[batch_count];
        double *y_batch_one = matY[batch_count];
        batch_count++;
        if(batch_count >= batch_size)
            batch_count = 0;

                 // forward propagation
                 for (p = 0; p <time_step; p ++) // iterate a value inside the batch
        {

            x[0] = x_batch_one[p];
                         double t = (double) y_batch_one [p]; // predicted y values

                         double * in_gate = new double [hidenode]; // input gate
                         double * out_gate = new double [hidenode]; // output gates
                         double * forget_gate = new double [hidenode]; // forgotten door
                         double * g_gate = new double [hidenode]; // New Memory
                         double * state = new double [hidenode]; // state value
                         double * h = new double [hidenode]; // hidden layer output values

            for(j=0; j<hidenode; j++)
            {
                                 // input layer to the hidden layer broadcast
                double inGate = 0.0;
                double outGate = 0.0;
                double forgetGate = 0.0;
                double gGate = 0.0;

                                 for (m = 0; m <innode; m ++) // input gate, forgetting gate, an output gate,
                {
                                         inGate += x [m] * W_I [m] [j]; // input gate
                                         outGate += x [m] * W_O [m] [j]; // output gates
                                         forgetGate += x [m] * W_F [m] [j]; // forgotten door
                                         gGate += x [m] * W_G [m] [j]; // create new memory
                }

                                 double * h_pre = h_vector.back (); // return the end value, the value of a hidden layer weights
                double *state_pre = S_vector.back();//
                for(m=0; m<hidenode; m++)
                {
                                         inGate += h_pre [m] * U_I [m] [j]; // on a hidden layer weights and the present input hidden layer
                    outGate += h_pre[m] * U_O[m][j];
                    forgetGate += h_pre[m] * U_F[m][j];
                    gGate += h_pre[m] * U_G[m][j];
                }

                in_gate[j] = sigmoid(inGate);
                out_gate[j] = sigmoid(outGate);
                forget_gate[j] = sigmoid(forgetGate);
                g_gate [j] = qTan (gGate); // g_gate [j] = sigmoid (gGate); // this modified Sigmoid!

                double s_pre = state_pre[j];
                state[j] = forget_gate[j] * s_pre + g_gate[j] * in_gate[j];
                                 h [j] = out_gate [j] * qTan (state [j]); // h [j] = in_gate [j] * tanh (state [j]); out the modified
            }

                         // the hidden layer to the output layer propagated
            for(k=0; k<outnode; k++)
            {

                double out = 0.0;
                for(j=0; j<hidenode; j++)
                    out += h[j] * W_out[j][k];
                                 y [k] = sigmoid (out); // for each output layer unit outputs a regression problem if it is done without actually should sigmoid function
            }

 // predict [p] = (int) floor (y [0] + 0.5); // record the predicted value
                         predict [p] = y [0]; // record the predicted value

                         // Save the hidden layer to the next calculation
            I_vector.push_back(in_gate);
            F_vector.push_back(forget_gate);
            O_vector.push_back(out_gate);
            S_vector.push_back(state);
            G_vector.push_back(g_gate);
            h_vector.push_back(h);

                         // save deflector t standard error regarding the output layer is the actual value
            y_delta.push_back( (t - y[0]) * dsigmoid(y[0]) );
                         //e += fabs (1.0*(t - y[0])); // Error
            e += abs (1.0*(t - y[0]));
        }


//back prop error start


          backProp(alphain, j, i, k, p, e, epoch, predict, x_batch_one,  I_vector, O_vector, F_vector, G_vector,S_vector,  h_vector,  y_delta );

         }



//back prop end


         // loop for training times
cout << endl << "Was writed file data" << endl;
    if(writeFlag)
        writeData(thisFlavorNUM);




  //  if(epoch==loop_time) return;

}

void RNN::loadData(int num, QString filepath)
{

    QFile f(filepath);
    //(fileName);

    QString data;
     //QStringList wordList;
    if (f.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qDebug() << endl << "load data"<< endl;

        //pre topology


           QTextStream in(&f);
           in.readLine(); // topology get




           while (!in.atEnd()) {

               QString line = in.readLine();
               QStringList wordList1 = line.split("= ");

              line = in.readLine();
              QStringList wordList2= line.split("= ");

          line = in.readLine();
           QStringList wordList3 = line.split("= ");

      line = in.readLine();
      QStringList wordList4 = line.split("= ");


               for(int i=0; i<innode; i++)
                   for(int j=0; j<hidenode; j++)
                   {

                       W_I[i][j]=wordList1.at(1).toDouble();

                   W_F[i][j]=wordList2.at(1).toDouble();

               W_O[i][j]=wordList3.at(1).toDouble();


           W_G[i][j]=wordList4.at(1).toDouble();


           qDebug() <<  W_I[i][j];
                  qDebug() <<  W_F[i][j];
                         qDebug() <<  W_O[i][j];
                                qDebug() <<  W_G[i][j];




                   }


               line = in.readLine();
               QStringList wordList5 = line.split("= ");

               for(int i=0; i<hidenode; i++)
                   for(int j=0; j<outnode; j++)
                   {


                      W_out[i][j]=wordList5.at(1).toDouble();
                         qDebug() <<  W_out[i][j];
                         //  qDebug() << wordList.at(0).toDouble();
                          //qDebug() << wordList.at(2).toDouble();

                   }


               // process your line here
           }




           }



    f.close();

}




void RNN::deleteLast() {





}



int RNN::rnn_predict(int timelength)
{
         // training time will be cleared once these vector
         vector <double *> I_vector; // input gate
         vector <double *> F_vector; // forgotten door
         vector <double *> O_vector; // output gates
         vector <double *> G_vector; // new memories
         vector <double *> S_vector; // state value
         vector <double *> h_vector; // output value

         // 0 before the time is not hidden layer, so a full initialization is 0
         double * S = new double [hidenode]; // state value
       //  double * h = new [hidenode] double; // output value
          double * h = new double[hidenode];

    for(int i = 0; i < hidenode; i++)
    {
        S[i] = 0;
        h[i] = 0;
    }

    S_vector.push_back(S);
    h_vector.push_back(h);

         double * predict = new double [time_step]; // save each generated predicted value to generate a set of predicted values ​​for each batch
 //mem set disable
         //memset(predict, 0, sizeof(double)*time_step);

    double * x_batch_one = new double[time_step];
    for(int i = 1; i<=time_step; i++)
    {
        x_batch_one[i - 1] = Day_Num + i;
        x_batch_one[i - 1] = (x_batch_one[i - 1] - minX)/(maxX - minX) * XDataRate - 1;
    }

         // forward propagation
         for (int p = 0; p <time_step; p ++) // iterate a value inside the batch
    {
        x[0] = x_batch_one[p];

                 double * in_gate = new double [hidenode]; // input gate
        double * out_gate = new double [hidenode]; // output gates
                 double * forget_gate = new double [hidenode]; // forgotten door
                 double * g_gate = new double [hidenode]; // New Memory
                 double * state = new double [hidenode]; // state value
                 double * h = new double [hidenode]; // hidden layer output values

        for(int j = 0; j < hidenode; j++)
        {
                         // input layer to the hidden layer broadcast
            double inGate = 0.0;
            double outGate = 0.0;
            double forgetGate = 0.0;
            double gGate = 0.0;

                         for (int m = 0; m <innode; m ++) // input gate, forgetting gate, an output gate,
            {
                                 inGate += x [m] * W_I [m] [j]; // input gate
                                 outGate += x [m] * W_O [m] [j]; // output gates
                                 forgetGate += x [m] * W_F [m] [j]; // forgotten door
                                 gGate += x [m] * W_G [m] [j]; // create new memory
            }

                         double * h_pre = h_vector.back (); // return the end value, the value of a hidden layer weights
            double * state_pre = S_vector.back(); //

            for(int m = 0; m < hidenode; m++)
            {
                                 inGate += h_pre [m] * U_I [m] [j]; // on a hidden layer weights and the present input hidden layer
                outGate += h_pre[m] * U_O[m][j];
                forgetGate += h_pre[m] * U_F[m][j];
                gGate += h_pre[m] * U_G[m][j];
            }

            in_gate[j] = sigmoid(inGate);
            out_gate[j] = sigmoid(outGate);
            forget_gate[j] = sigmoid(forgetGate);
            g_gate[j] = qTan(gGate);

            double s_pre = state_pre[j];
            state[j] = forget_gate[j] * s_pre + g_gate[j] * in_gate[j];
            h[j] = out_gate[j] * qTan(state[j]);
        }

                 // the hidden layer to the output layer propagated
        for(int k = 0; k < outnode; k++)
        {

            double out = 0.0;

            for(int j = 0; j < hidenode; j++)
            {
                out += h[j] * W_out[j][k];
            }

                         y [k] = sigmoid (out); // for each output layer unit outputs a regression problem if it is done without actually should sigmoid function
        }

 // predict [p] = (int) floor (y [0] + 0.5); // record the predicted value
                 predict [p] = y [0]; // record the predicted value
        cout<<predict[p]<<"\t";

                 // Save the hidden layer to the next calculation
        I_vector.push_back(in_gate);
        F_vector.push_back(forget_gate);
        O_vector.push_back(out_gate);
        S_vector.push_back(state);
        G_vector.push_back(g_gate);
        h_vector.push_back(h);
    }
    cout<<"\n";

    int i;
    for(i=0; i<(int)I_vector.size(); i++)
        delete I_vector[i];
    for(i=0; i<(int)F_vector.size(); i++)
        delete F_vector[i];
    for(i=0; i<(int)O_vector.size(); i++)
        delete O_vector[i];
    for(i=0; i<(int)G_vector.size(); i++)
        delete G_vector[i];
    for(i=0; i<(int)S_vector.size(); i++)
        delete S_vector[i];
    for(i=0; i<(int)h_vector.size(); i++)
        delete h_vector[i];

    I_vector.clear();
    F_vector.clear();
    O_vector.clear();
    G_vector.clear();
    S_vector.clear();
    h_vector.clear();

    double temp = predict[timelength - 1] / YDataRate * (maxY - minY) + minY;

    int temp2 = (int)qFloor(temp + 0.5) - (int)maxY;
    if(temp2 < 0)
    {
        cout<<"VM"<<thisFlavorNUM<<" predict error!!! "<<temp2<<endl;
        temp2 = 1;
    }
    else
    {
        cout<<"VM"<<thisFlavorNUM<<" predict:"<<temp2<<endl;
    }

    delete predict;
    delete x_batch_one;

    return temp2;
}

 void RNN :: reshape (int timestep, int flavor_num) // timestep flavor began to count from 1 starting at 1 count plus normalization
{
     double VM_dwz[Day_Num-1][flavor_num-1];
         int start = Day_Num% timestep; // beginning from the first of several one-dimensional arrays of values ​​1
    int day = start + 1;
    maxY = VM_dwz[Day_Num - 1][flavor_num - 1];
    minY = VM_dwz[start][flavor_num - 1];
    maxX = Day_Num;
    minX = day;

    matY = new double *[batch_size];
    matX = new double *[batch_size];

    for(int i=0; i<batch_size; i++)
    {
        matX[i] = new double [timestep];
        matY[i] = new double [timestep];
    }

    for(int i=0; i<batch_size; i++)
    {
        for(int j=0; j<timestep; j++)
        {
            matY[i][j] = VM_dwz[start + i*timestep + j][flavor_num - 1];

            matY[i][j] = (matY[i][j] - minY)/(maxY - minY) * YDataRate;

                         matX [i] [j] = (day - minX) / (maxX - minX) * XDataRate - 1; // scaled to -11
            day ++;
        }
    }
}


void RNN::writeData(int num)
{

QString name="/home/h1p3m/Adonai/data";
name.append(QString::number(num));
name.append(".cpp");

    QFile writefile(name);




    if(!writefile.open(QIODevice::ReadWrite)) {
                 writefile.open(QIODevice::ReadWrite);
        cout << "Open file failure" << endl;
    } //else{
      // qDebug() << "File is open";
    //}
     QTextStream outfile(&writefile);

    outfile
    <<num<<endl;
   // <<"{<<endl;

    for(int i=0; i<innode; i++)
        for(int j=0; j<hidenode; j++)
        {
            outfile<<"\tW_I["<<i<<"]["<<j<<"] = "<<W_I[i][j]<<endl;
            outfile<<"\tW_F["<<i<<"]["<<j<<"] = "<<W_F[i][j]<<endl;
            outfile<<"\tW_O["<<i<<"]["<<j<<"] = "<<W_O[i][j]<<endl;
            outfile<<"\tW_G["<<i<<"]["<<j<<"] = "<<W_G[i][j]<<endl;
        }

    for(int i=0; i<hidenode; i++)
        for(int j=0; j<hidenode; j++)
        {
            outfile<<"\tU_I["<<i<<"]["<<j<<"] = "<<U_I[i][j]<<endl;
            outfile<<"\tU_F["<<i<<"]["<<j<<"] = "<<U_F[i][j]<<endl;
            outfile<<"\tU_O["<<i<<"]["<<j<<"] = "<<U_O[i][j]<<endl;
            outfile<<"\tU_G["<<i<<"]["<<j<<"] = "<<U_G[i][j]<<endl;
        }

    for(int i=0; i<hidenode; i++)
        for(int j=0; j<outnode; j++)
        {
            outfile<<"\tW_out["<<i<<"]["<<j<<"] = "<<W_out[i][j]<<endl;
        }



    //outfile<<"}"<<endl;

    writefile.close();

}



void RNN::intWeight1()
{

}

void RNN::intWeight2()
{

}

void RNN::intWeight3()
{

}

void RNN::intWeight4()
{

}

void RNN::intWeight5()
{

}

void RNN::intWeight6()
{

}

void RNN::intWeight7()
{

}

void RNN::intWeight8()
{

}

void RNN::intWeight9()
{

}

void RNN::intWeight10()
{

}

void RNN::intWeight11()
{

}

void RNN::intWeight12()
{

}

void RNN::intWeight13()
{

}

void RNN::intWeight14()
{

}

void RNN::intWeight15()
{

}

