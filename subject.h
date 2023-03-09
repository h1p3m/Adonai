#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>
#include <QStringList>
#include <string>
#include <QtMath>
#include <vector>
#include <tuple>

#include <iostream>
#include <QChar>
#include <QObject>
using namespace std;
template <class T> class ContainerType {
public:
    T value;
 int length;
bool isRealContainer;
 virtual int get_length();
  virtual bool is_real_container();
 virtual void init();
};
//jlN Sub
template <class T> class Kids : public ContainerType <T>{
public:
    T* value;
 int* length;
bool* isRealContainer;
 Kids(T* val) {
  static_cast<T*>(nullptr);
     this->value     = &val;
    this->length     = sizeof(&val);
    this->isRealContainer = false;
    init();

}

void create(const T val) {
    this->value     = val;
    this->length     = sizeof(val);
    this->isRealContainer = false;
    init();

}
int get_length(){

        //return this->length;
return 0;
}
  bool is_real_container(){
       // this->isRealContainer = QChar::isDigit(QString::fromRawData(this->value).at(0));
        ///return this->isRealContainer;
        return false;
}

  void init(){
       // if(this->is_real_container()){
            //this->get_length();
     //   }
        //else{
          //  this->value="";
       // }

    }


};

template <class T> class ParentClass {
public:
    // w;
 //static
     QString * getchain;
     QString* classname;
     //T* classname;
     QString* parent;
  // const  T* parent;
// static f;
//const $ego=hrtime(true);

    QString* name=new QString(" Computer (Ego) call a Kids Science Portal");
   auto getChain() {

            //    auto callbacks = function($className='') use (& $chain, & $function) {

                    //    return calll
        auto callbacks = make_tuple(

            [&] () {

            if (this->classname==nullptr) {
            this->classname=this->name;
                        //className();

            }
            if (this->getchain== nullptr ) {

                 this->getchain = this->classname;
            }

            this->parent=new QString("QString");
            if (this->parent != nullptr) {
                QString chain=this->getchain+QString(" > ")+this->parent;
                 this->getchain=&chain;


                           //return $function($parent);

                        }

        }, // y is captured by reference
            [=] (auto callbacks) {

//this->callbacks=callbacks;
          //  this->parent=*typeid(T).name();
          //  cout << x <<"-"<< endl;


        } // y is captured by value
            // other lambdas here, if you want...
      ); //tupple and chain end


        return callbacks;
    }

    auto getChaintest() {



        auto callbacks = make_tuple(
            [] (int x) { cout << x << endl; },
            [&] () { cout << "-" << endl; }, // y is captured by reference
            [=] (int x) { cout << x <<"-"<< endl; } // y is captured by value
            // other lambdas here, if you want...
            );
        return callbacks;
    }
    
//$this->show();
};
template <class T> class Child : public ParentClass<T> {
public:
    int x = 500;
    int y = 500;
 // $tag_line ="A Computer Science Portal for Geeks!Family: mother";
    void display() {
       //var_dump($this->hrtime."<br/>");
       cout << "This time is 421124912409" <<endl;
    }
 void show() {

   // private function show()
   // {
   // $lim=print(hrtime(true). PHP_EOL);
///print_r(hrtime());

        //var_dump("This is private method of base class");
 cout << "This time is 1202410"<<endl;
       //echo "echo"; // hrtime(time);
 }


    double mul() //Multiply Function
    {
       // echo $sub=$this->x*$this->y;
    return this->x*this->y;
    }
    double sub()
    {
           return this->x-this->y;
    }
//$obj->mul();
//$obj->show();


};




class Subject
{
public:
    Subject();



};

#endif // SUBJECT_H



