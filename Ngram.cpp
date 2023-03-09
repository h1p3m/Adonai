#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
//#include "train.cpp"
#include <cctype>

#include <string>

#include <algorithm>

#include <iterator>
#include <set>
#include <map>
#include <cstring>
#include <list>
#include "Random.hpp"
#include <unordered_map>
#include <QFile>
#include <QString>
//#include <Learn.h>
#include <QDateTime>

using namespace std;
class NGrams {
public:
    vector <string> ngrams;
   vector<string> table;
   std::vector<std::string> words_;
   std::unordered_map<std::string, std::vector<std::string>> markovChain_;
   map<string, int>D;


    std::vector<std::pair<std::string, int>> v;


   list <pair<string, double>>  chain;
void createMarkovChain() {

      for (size_t i = 0; i < this->words_.size() - 1; ++i)
        this->markovChain_[this->words_[i]].push_back(this->words_[i + 1]);

}


   bool readFile(QString filename)
   {
       QFile f(filename);
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
   void printChain() {
       for (std::list <pair<string, double>>::const_iterator iter = this->chain.begin();
              iter != this->chain.end();
              ++iter)
         {
            std::cout << "First: "    << iter->first
                      << ", Second: " << iter->second <<std::endl;

       }

   }
void printWordFrequency () {
    for (size_t i = 0; i < v.size(); ++i) {

          //  res << this->v[i].first << " " <<this-> v[i].second << "\n";
           cout << this->v[i].first << " " << this->v[i].second << "\n";
    }

}
    void printTable() {
        for(int i=0; i<table.size(); ++i) {
          std::cout << ngrams[i] << ' ';
        }

    }
    vector<string> getTable() {
        return this->table;
    }
void getNgrams(string word,  int n = 3) {
//vector <string> ngrams;
//ngrams = array();

int len = word.length();

for(int i = 0; i < len; i++) {

if(i > (n - 2)) {

string ng = "";

for(int j = n-1; j >= 0; j--) {

ng += word[i-j];

}

this->ngrams.push_back(ng);

}

}

//return $ngrams;
}
std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}
void generate_markov_table(string file) {

// walk through the text and make the index table for words

    string s;


   // vector <string, double>

       ifstream in1(file);


       while (in1 >> s) {
           while (s.find_first_of("<><[]« :,.;!\"?1234567890-'/)(_“\\\0\t") != -1) {
               s.replace(s.find_first_of("<>[]« :,.-;!\"?1234567890-'/)(_“\\\0\t"), 1, "");

           }
           this->D[s]++;
       }
       in1.close();

       map <string, int>::iterator it;

       ofstream res("result.txt", ios_base::app);

      this->v= { std::make_move_iterator(begin(this->D)),
                                             std::make_move_iterator(end(this->D)) };
       // Create a vector with the map parameters

       sort(begin(this->v), end(this->v),
           [](pair<std::string, int> p1, pair<std::string, int> p2) {return p1.second < p2.second; });

       for (size_t i = 0; i < v.size(); ++i) {

               res << this->v[i].first;
               res << " " <<this-> v[i].second << "\n";
             //  cout << this->v[i].first << " " << this->v[i].second << "\n";



       }
       cout << endl << "Завершено." << endl;

       for (size_t i = 0; i < v.size(); ++i) {
       this->ngrams.clear();
                  getNgrams(this->v[i].first);
                     //this->chain.push_back({getNgrams(), vec_centroid})
                 // res << this->v[i].first << " " <<this-> v[i].second << "\n";
                    //  cout << this->v[i].first << " " << this->v[i].second << "\n";
       for (size_t j=0; j < this->ngrams.size(); j++) {

       double distance=1.*damerau_levenshtein_distance(this->v[i].first, this->ngrams[j])/1.*damerau_levenshtein_distance(this->ngrams[j], this->v[i].first);
          this->chain.push_back({this->ngrams[j], distance});
       }


        }



}




string generateSentence(int numberOfWords)
{
    int rand_num= Random::randomNumber();
  std::string randomWord = this->words_[rand_num % this->words_.size()];
  std::string sentence = randomWord;

  for (int i = 0; i < numberOfWords; ++i)
  {
    randomWord = this->markovChain_[randomWord][ Random::randomNumber() % this->markovChain_[randomWord].size()];
    sentence += " " + randomWord;
  }

  return sentence + '\n';
}




string generateIdea(int numberOfWords, int weight)
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


bool sentenceBegin(string str) {
  return ((str[0]>= 1040 && str[0] <= 1071) || (str[0] == 1025));

}






void print() {

    for(int i=0; i<ngrams.size(); ++i) {
      std::cout << ngrams[i] << ' ';
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



};
