#include<iostream>
#include<cmath>
using namespace std;

class HammingCodeDetector{

    string hcode;

    public:

    HammingCodeDetector(string hcode){

        this->hcode = hcode;
        }

    int calculate(){

        int sum=0,power;

        for(int i=0,j=0;i<hcode.size();i++){

                if(raised2(i+1)){

                    power = pow(2.0,j);

                    char parity = calparity(j,hcode.size(), hcode);

                    if(hcode.at(i) != parity)
                        sum += power;

                    j += 1;

                    }
            }

        return(sum);

        }

    bool raised2(int i){


        for(int k=0;k<i;k++){

            if(pow(2.0,k) == i)
                return true;

            }
        return false;

        }

    char calparity(int j,int size, string hc){

        char parity='0';
        int power = pow(2.0,j);

        for(int i=1;i<=size;i++){

            if((i&power) != 0){

                if(!raised2(i))
                    parity = charxor(parity,hc.at(i-1));
                }
            }

        return (parity);

        }

    char charxor(char a, char b){

        if((a == '1' && b == '1') || (a == '0' && b == '0'))
            return '0';

        else
            return '1';

        }


    };

int main(){

    string hcode;

    cout<<"Hamming Code Detector\n";
    cout<<"----------------------\n\n";

    cout<<"Enter Received Hamming Code:";
    cin>>hcode;

    HammingCodeDetector *hc = new HammingCodeDetector(hcode);

    int error = hc->calculate();

    if(error!=0)
        cout<<"\n\nError Bit: "<<error<<endl;
    else
        cout<<"\n\nNo Error!"<<endl;

    return(0);

    }
