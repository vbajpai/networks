#include<iostream>
#include<cmath>
using namespace std;

class HammingCodeGenerator{

    string message;

    public:

    HammingCodeGenerator(string message){

        this->message = message;

        }

    string calculate(){

        int pcount = paritycount();
        int hcsize = message.size() + pcount;

        char hc[hcsize];

        for(int i=0,k=0;i<hcsize;i++){

                if(!raised2(i+1)){

                    hc[i] = message.at(k);
                    k += 1;

                    }
            }

        for(int i=0,j=0;i<hcsize;i++){

                if(raised2(i+1)){

                    char parity = calparity(j,hcsize, hc);
                    hc[i] = parity;
                    j += 1;

                    }
            }

        string hcode(hc, hcsize);

        return (hcode);

        }

    char calparity(int j,int size, char *hc){

        char parity='0';
        int power = pow(2.0,j);

        for(int i=1;i<=size;i++){

            if((i&power) != 0){

                if(!raised2(i))
                    parity = charxor(parity,hc[i-1]);
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

    bool raised2(int i){


        for(int k=0;k<i;k++){

            if(pow(2.0,k) == i)
                return true;

            }
        return false;

        }

    int paritycount(){

        int size = message.size();
        int p = 0;

        while(true){

            if(size <= int(pow(2.0,p)) - p - 1)
                break;

            p += 1;

            }

        return(p);

        }

    };

int main(){

    string message;

    cout<<"Hamming Code Generator\n";
    cout<<"----------------------\n\n";

    cout<<"Enter Message:";
    cin>>message;

    HammingCodeGenerator *hc = new HammingCodeGenerator(message);

    string hcode = hc->calculate();

    cout<<"\n\nGenerated Hamming Code: "<<hcode<<endl;

    return(0);

    }
