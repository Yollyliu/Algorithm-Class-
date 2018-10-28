

#include <iostream>
#include <fstream>


using namespace std;

double** sMMR(int len,double **ma, double **mb);

int main(int argc, char* argv[]){






    ifstream fi(argv[1]);


    if(!fi){
    //if(!fi.is_open()){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }

    ofstream fo(argv[2]);

    if(!fo){
        cout<<"We cannot open your output file; try again later; bye; kkkkkk"<<endl;
        return -1;
    }

    int N;
    fi>>N;

    for(int i=0;i<N;++i){

        int len;
        fi>>len;


        if(len==0){
            fo<<"The "<<i<<"dataset is empty"<<endl;
        }
        else{
     

            double **ma = new double*[len];
            for(int f = 0; f < len; ++f) {
                ma[f] = new double[len];
            }

            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                    fi>>ma[i][j];
                }

            }

            double **mb = new double*[len];
            for(int f= 0; f < len; ++f) {
                mb[f] = new double[len];
            }

            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                    //fi>>mb[i][j];
                    fi>>mb[i][j];
                }

            }

            double **c = new double*[len];
            for(int f= 0; f < len; ++f) {
                c[f] = new double[len];
            }




            c=sMMR(len,ma,mb);

            for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                    fo<<c[i][j]<<" ";
                }
          //      cout<<endl;
            }

            for(int i = 0; i < len; ++i) {
                delete [] ma[i];
                delete [] mb[i];
                delete [] c[i];
            }
            delete [] ma;
            delete []mb;
            delete []c;

        }
        fo<<endl;


    }

    return 0;
}
double** sMMR(int len,double **ma, double **mb){

    double** c = 0;
    c = new double*[len];
    for(int i=0;i<len;i++){
        c[i]=new double[len];
    }



    if(len==1){
        //int c[1][1];
        c[0][0]=ma[0][0]*mb[0][0];
//        cout<<"hello1"<<endl;
//        cout<<c[0][0]<<endl;
        return c;
    }else if((len!=1)&&(len%2==1)){
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                c[i][j]=0;
                for(int k=0;k<len;k++){
                    c[i][j]+=ma[i][k]*mb[k][j];
                }
            }
        }
        return c;

    }



    else {


        int floor = len / 2;
        double s1[floor][floor];
        double s2[floor][floor];
        double s3[floor][floor];
        double s4[floor][floor];
        double s5[floor][floor];
        double s6[floor][floor];
        double s7[floor][floor];
        double s8[floor][floor];
        double s9[floor][floor];
        double s10[floor][floor];
        double p1[floor][floor];
        double p2[floor][floor];
        double p3[floor][floor];
        double p4[floor][floor];
        double p5[floor][floor];
        double p6[floor][floor];
        double p7[floor][floor];
        double c1[floor][floor];
        double c2[floor][floor];
        double c3[floor][floor];
        double c4[floor][floor];


        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                s1[i][j] = mb[i][floor + j] - mb[floor + i][floor + j];  //B12-B22

                s2[i][j] = ma[i][j] + ma[i][floor + j];    //A11+A12

                s3[i][j] = ma[i + floor][j] + ma[floor + i][floor + j];  //A21+A22

                s4[i][j] = mb[i + floor][j] - mb[i][j];   //B21-B11

                s5[i][j] = ma[i][j] + ma[i + floor][j + floor];   //A11+A22

                s6[i][j] = mb[i][j] + mb[i + floor][j + floor];   //B11+B22

                s7[i][j] = ma[i][j + floor] - ma[i + floor][j + floor];  //A12-A22

                s8[i][j] = mb[i + floor][j] + mb[floor + i][floor + j];   //B21+B22

                s9[i][j] = ma[i][j] - ma[i + floor][j];   //A11-A21

                s10[i][j] = mb[i][j] + mb[i][j+floor];  //B11+B12
            }
        }


        for (int i = 0; i < floor; ++i) {
            for (int j = 0; j < floor; ++j) {

                p1[i][j] = ma[i][j] * s1[i][j];      //p1=A11*S1

                p2[i][j] = s2[i][j] * mb[floor + i][floor + j];    //p2=s2*b22

                p3[i][j] = s3[i][j] * mb[i][j];       //p3=s3*b11
                p4[i][j] = ma[i + floor][j + floor] * s4[i][j];     //p4=A22*s4

                p5[i][j] = s5[i][j] * s6[i][j];    //p5=S5*S6
                p6[i][j] = s7[i][j] * s8[i][j];     //p6=s7*s8
                p7[i][j] = s9[i][j] * s10[i][j];        //p7=s9*s10

            }

        }


        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c1[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
                c2[i][j] = p1[i][j] + p2[i][j];
                c3[i][j] = p3[i][j] + p4[i][j];
                c4[i][j] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j];
            }
        }


        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c[i][j]=c1[i][j];

            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c[i][j+floor]=c2[i][j];
            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c[i+floor][j]=c3[i][j];
            }
        }
        for (int i = 0; i < floor; i++) {
            for (int j = 0; j < floor; j++) {

                c[i+floor][j+floor]=c4[i][j];
            }
        }
        return c;

    }




}

