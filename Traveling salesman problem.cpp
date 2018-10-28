//40055006 Youlin Liu

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>


using namespace std;

int main(int argc, char* arg[]) {
    ifstream input(arg[1]);
    if(!input) {
        cout << "you cannot open input file, please try another file" << endl;
        return -1;
    }

    ofstream output(arg[2]);
    if(!output){
        cout << "you cannot write to output file, please try another file" << endl;
        return -1;
    }

    int N;
    input>>N;
    for(int j=0;j<N;j++) {
        int vertexs, edges;

        input >> vertexs >> edges;

        vector<vector<int> > weighted(vertexs, vector<int>(vertexs));


        int allVertex[vertexs];
        for(int i=0;i<vertexs;i++){
            allVertex[i]=i;
        }

        for (int i = 0; i < edges; i++) {
            int first, second, weight;
            input >> first >> second >> weight;

            weighted[first][second ] = weight;
            weighted[second][first] = weight;
        }
        int path=2147483647;


        int count=0;




        do {

            vector<int> cycle;

            cycle.push_back(allVertex[0]);

            for (int i = 1; i < vertexs; i++) {
            //    cout<<allVertex[i]<<" ";
                cycle.push_back(allVertex[i]);
            }
            cycle.push_back(allVertex[0]);
            int tempcost=0;


            for(int k=0;k<cycle.size()-1;k++){
              //  cout<<k<<"->"<<k+1<<" "<<weighted[k][k+1]<<"   ";
               int first=cycle[k];
                int second=cycle[k+1];

              //  cout<<first<<"->"<<second<<" "<<weighted[first][second]<<"   ";
                tempcost+=weighted[first][second];
            //    cout<<first<<"->"<<second<<" "<<weighted[first][second]<<"    cost: "<<tempcost;

            }


            if(tempcost<path){
                path=tempcost;
            }


        } while (std::next_permutation(allVertex+1, allVertex + vertexs));
       output<<path<<endl;
    }


}