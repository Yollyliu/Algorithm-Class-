#include <iostream>
#include <fstream>
#include <vector>

//#ifndef T_SIMPLE_MATRIX_H
#define T_SIMPLE_MATRIX_H

using namespace std;

template<class T>
class SMatrix {
  private:

    // Storage
    std::vector<T> v;

    int N;

  public:

    SMatrix<T>(int M){v.resize(M*M);N = M;}
    SMatrix<T>(){N = 0;}

    void resize(int M){
        v.resize(M*M);
        N = M;
    }

    int size(){
        return N;
    }


    // access matrix(r, c) (row and column)  for R/W operations
    T& operator() (int r, int c){
        return  v[N*r+c];
    }
    const T& operator()(int r, int c) const{
        return  v[N*r+c];
    }

};

SMatrix<double> sMMR(SMatrix<double> ma, SMatrix<double> mb);

int main(int argc, char* argv[]){


    ifstream input(argv[1]);

    if(!input){
      return -1;
    }

    ofstream output(argv[2]);

    if(!output){
        cout<<"We cannot open your output file; try again later; bye; kkkkkk"<<endl;
        return -1;
    }

    int N;
    input>>N;

    for(int i=0;i<N;++i){

        int len;
        input>>len;


        if(len==0){
            output<<"The "<<i<<"dataset is empty"<<endl;
        }
        else{
            SMatrix<double> ma,mb,mc;
            ma.resize(len);
            mb.resize(len);
            mc.resize(len);



            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                    input >> ma.operator()(i,j);
                }

            }


            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){

                    input>>  mb.operator()(i,j);
                }

            }


            mc=sMMR(ma,mb);

            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                    output<<mc(i,j)<<" ";
                }
                cout<<endl;
            }

        }
        output<<endl;


    }

    return 0;
}
SMatrix<double> sMMR(SMatrix<double> ma, SMatrix<double> mb){

    int len=ma.size();
    SMatrix<double> c;
    c.resize(len);
    if(len==1) {
        c.operator()(0, 0) = ma.operator()(0, 0) * mb.operator()(0, 0);
        return c;

    }else if((len!=1)&&(len%2==1)){
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                c(i,j)=0;
                for(int k=0;k<len;k++){
                    c(i,j)=c(i,j)+ma.operator()(i,k)*mb.operator()(k,j);
                }
            }
        }
        return c;

    }

    else {


        int floor = len / 2;
        SMatrix<double> s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,
                p1,p2,p3,p4,p5,p6,p7,
                c1,c2,c3,c4,
                ma1,ma2,ma3,ma4,
                mb1,mb2,mb3,mb4;
        s1.resize(floor);
        s2.resize(floor);
        s3.resize(floor);
        s4.resize(floor);
        s5.resize(floor);
        s6.resize(floor);
        s7.resize(floor);
        s8.resize(floor);
        s9.resize(floor);
        s10.resize(floor);

        p1.resize(floor);
        p2.resize(floor);
        p3.resize(floor);
        p4.resize(floor);
        p5.resize(floor);
        p6.resize(floor);
        p7.resize(floor);

        c1.resize(floor);
        c2.resize(floor);
        c3.resize(floor);
        c4.resize(floor);

        ma1.resize(floor);
        ma2.resize(floor);
        ma3.resize(floor);
        ma4.resize(floor);

        mb1.resize(floor);
        mb2.resize(floor);
        mb3.resize(floor);
        mb4.resize(floor);

        for(int i=0;i<floor;i++){
            for(int j=0;j<floor;j++){
                ma1(i,j)=ma.operator()(i,j);
                ma2(i,j)=ma.operator()(i,j+floor);
                ma3(i,j)=ma.operator()(i+floor,j);
                ma4(i,j)=ma.operator()(i+floor,j+floor);
                mb1(i,j)=mb.operator()(i,j);
                mb2(i,j)=mb.operator()(i,j+floor);
                mb3(i,j)=mb.operator()(i+floor,j);
                mb4(i,j)=mb.operator()(i+floor,j+floor);
            }
        }



        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                s1(i,j)=mb2.operator()(i,j)-mb4.operator()(i,j);//B12-B22

                  s2(i,j)=ma1.operator()(i,j)+ma2.operator()(i,j);//A11+A12

                  s3(i,j)=ma3.operator()(i,j)+ma4.operator()(i,j);//A21+A22

                  s4(i,j)=mb3.operator()(i,j)-mb1.operator()(i,j);//B21-B11

                  s5(i,j)=ma1.operator()(i,j)+ma4.operator()(i,j);//A11+A22

                  s6(i,j)=mb1.operator()(i,j)+mb4.operator()(i,j);//B11+B22

                  s7(i,j)=ma2.operator()(i,j)-ma4.operator()(i,j);//A12-A22

                s8(i,j)=mb3.operator()(i,j)+mb4.operator()(i,j);//B21+B22

                s9(i,j)=ma1.operator()(i,j)-ma3.operator()(i,j);//A11-A21

                s10(i,j)=mb1.operator()(i,j)+mb2.operator()(i,j); //B11+B12


            }
        }






                p1=sMMR(ma1,s1);//p1=A11*S1
                p2=sMMR(s2,mb4);//p2=s2*b22
                p3=sMMR(s3,mb1);//p3=s3*b11
                p4=sMMR(ma4,s4);//p4=A22*s4
                p5=sMMR(s5,s6);//p5=S5*S6
                p6=sMMR(s7,s8);//p6=s7*s8
                p7=sMMR(s9,s10); //p7=s9*s10





        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c1(i,j)=p5.operator()(i,j)+p4.operator()(i,j)-p2.operator()(i,j)+p6.operator()(i,j);
                c2(i,j)=p1.operator()(i,j) + p2.operator()(i,j);
                c3(i,j) = p3.operator()(i,j) + p4.operator()(i,j);
                c4(i,j) = p5.operator()(i,j) + p1.operator()(i,j) - p3.operator()(i,j) - p7.operator()(i,j);
            }
        }


        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {
                c(i,j)=c1.operator()(i,j);

            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {
                c(i,j+floor)=c2.operator()(i,j);
            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {
                c(i+floor,j)=c3.operator()(i,j);
            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {
                c(i+floor,j+floor)=c4.operator()(i,j);
            }
        }
        return c;

    }

}

