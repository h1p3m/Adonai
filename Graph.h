#include <iostream>

using namespace std;
class Graph {
private:
      bool** adjMatrix;

      int numVertices;
public:
      Graph(int numVertices) {
            this->numVertices = numVertices;
            adjMatrix = new bool*[numVertices];
            for (int i = 0; i < numVertices; i++) {
                  adjMatrix[i] = new bool[numVertices];
                  for (int j = 0; j < numVertices; j++)
                        adjMatrix[i][j] = false;
          }
    }

      void addEdge(int i, int j) {
                  adjMatrix[i][j] = true;
                  adjMatrix[j][i] = true;
    }

      void removeEdge(int i, int j) {
                  adjMatrix[i][j] = false;
                  adjMatrix[j][i] = false;
    }


      bool isEdge(int i, int j) {
                  return adjMatrix[i][j];
    }
    void toString() {
      for (int i = 0; i < numVertices; i++) {
                  cout << i << " : ";

                  for (int j = 0; j < numVertices; j++)

                      cout << adjMatrix[i][j] << " ";
                  cout << "\n";
      }
    }

    ~Graph() {
            for (int i = 0; i < numVertices; i++)
                  delete[] adjMatrix[i];
            delete[] adjMatrix;
    }
};

class WeightGraph {
private:

double** waveMatrix;
int numVertices;
public:
      WeightGraph(int numVertices) {
            this->numVertices = numVertices;
            waveMatrix = new double*[numVertices];
            for (int i = 0; i < numVertices; i++) {
                  waveMatrix[i] = new double[numVertices];
                  for (int j = 0; j < numVertices; j++) {
                        waveMatrix[i][j] = 0.0;
                  }
          }
    }

      void addEdge(int i, int j, double value) {
                  waveMatrix[i][j] = value;
                  waveMatrix[j][i] = value;
    }

      void removeEdge(int i, int j,double value) {
                  waveMatrix[i][j] = value;
                  waveMatrix[j][i] = value;
    }


      bool isEdge(int i, int j) {
                  return waveMatrix[i][j];
    }
    void toString() {
      for (int i = 0; i < numVertices; i++) {
                  cout << i << " : ";
                  for (int j = 0; j < numVertices; j++) {
                             cout<<  j << endl;
                        cout << waveMatrix[i][j] << " ";
                  }
                  cout << "\n";
      }
    }
//tofile and from file





    ~WeightGraph() {
            for (int i = 0; i < numVertices; i++)
                  delete[] waveMatrix[i];
            delete[] waveMatrix;
    }
};


