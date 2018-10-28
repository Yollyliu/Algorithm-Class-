
#include <iostream>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;
string toString(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}
int length(vector<int>  nums, int total, vector<int> value);



int main(int argc, char* argv[]) {




    ifstream input(argv[1]);
    if (!input) {
        cout << "Cannot open your file!" << endl;
    } else {

        ofstream output(argv[2]);
        if (!output) {
            cout << "Cannot write to your file!" << endl;
        }





        int N;
        input >> N;


        for (int i = 0; i < N; i++) {
            int m;
            input >> m;

            vector<int> nums(m);

            for (int j = 0; j < m; j++) {

                input >> nums[j];

            }


            int total;
            input >> total;
            vector<int> value(total+1);

            value[0]=0;
            for(int f=1;f<= total;f++) {
                value[f] = 0;
            }



            int ans = length(nums, total,value);

            if ( ans!= 0 ) {
                output << ans<<endl;
            } else {
                output << "N"<<endl;


            }
        }
    }
    return 0;
}
int length( vector<int> nums, int total, vector<int> value) {

    vector<int> newnums;
    if(total==0){
        int len=0;
        for(int i=0;i<nums.size();i++){
            if(total==nums[i]){
                len++;
            }
        }
        if(len!=0){
            return 1;
        }else{
            return 0;
        }
    }


    for(int i=1;i<=total;i++) {
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] == i) {
                value[i] = 1;
            }

            string s = std::to_string(i);
            int len = s.size();

            int countconcate = 0;    //countconcate

            for (char ctemp: s) {               //concatenate

                for (int j = 0; j < nums.size(); j++) {

                    if ((ctemp - '0') != nums[j]) {


                    } else {
                        countconcate++;

                    }

                }
                if (countconcate == 0) { break; }


            }

            if (countconcate == len) {
                value[i] = countconcate;
                newnums.push_back(i);

            }

        }
    }


   // if(value[total]!=0) {return value[total];}


    vector<int> secondnums;
    secondnums=newnums;




    for(int i=1;i<=total;i++) {


            for (int j = 0; j < newnums.size(); j++) {
                if(newnums[j]!=0) {

                    if (i % newnums[j] == 0) {
                        int temp = i / newnums[j];
                        if (value[temp] != 0) {
                            int tempvalue = value[temp] + 1 + value[newnums[j]];
                            if (value[i] != 0 && value[i] > tempvalue) {
                                value[i] = tempvalue;
                                secondnums.push_back(i);

                            } else if (value[i] == 0) {
                                value[i] = tempvalue;
                                secondnums.push_back(i);

                            }

                        }

                    }
                }
        }
    }

    //if(value[total]!=0) {return value[total];}


    for(int i=1;i<=total;i++) {
        for (int j = 0; j < secondnums.size(); j++) {
           // if(nums[j]!=0) {
                if (i - nums[j] >= 0) {
                    if (value[i - nums[j]] != 0) {
                        int temp = value[nums[j]] + 1 + value[i - nums[j]];
                        if (value[i] != 0 && value[i] > temp) {

                            value[i] = temp;
                        } else if (value[i] == 0) {
                            value[i] = temp;
                        }

                    }

                }

        }
    }
    return value[total];
}














