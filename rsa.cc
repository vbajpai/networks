#include<iostream>
#include<gmpxx.h>
#include<cmath>
using namespace std;

class RSA{

    long e,d,n;

    public:

    RSA(long p, long q){

        long temp = (p-1)*(q-1);

        n = p*q;
        e = cale(n,temp);
        d = modinverse(e,temp);
        }

    string encrypt(string message){

        unsigned char ascii[message.size()];
        int cascii[int(ceil(message.size()/2.0))*2];
        string bit[message.size()];
        string cbit[int(ceil(message.size()/2.0))*2];
        string doublebit[int(ceil(message.size()/2.0))];
        int asciidouble[int(ceil(message.size()/2.0))];
        string cypher;

        for(int i=0;i<message.size();i++)
            ascii[i] = message.at(i);

        for(int i=0;i<message.size();i++)
            bit[i] = dec2binary(ascii[i],8);

        for(int i=0;i<ceil(message.size()/2.0);i++){

            if((2*i+1)<message.size())
                doublebit[i] = bit[2*i].append(bit[2*i+1]);
            else{

                doublebit[i] = bit[2*i];

                while(doublebit[i].size()<16){

                    string t;
                    t.push_back('0');
                    t.append(doublebit[i]);
                    doublebit[i]=t;
                    }
                }
            }

        for(int i=0;i<ceil(message.size()/2.0);i++)
            asciidouble[i] = binary2dec(doublebit[i]);

        for(int i=0;i<ceil(message.size()/2.0);i++){

            mpz_class tmp = 0;

            mpz_ui_pow_ui(tmp.get_mpz_t(), asciidouble[i], e);
            mpz_mod_ui(tmp.get_mpz_t(), tmp.get_mpz_t(), n);

            asciidouble[i] = tmp.get_si();
            }

        for(int i=0;i<ceil(message.size()/2.0);i++)
            doublebit[i] = dec2binary(asciidouble[i],16);

        for(int i=0;i<ceil(message.size()/2.0);i++){
                cbit[2*i] = doublebit[i].substr(0,8);
                cbit[2*i+1] = doublebit[i].substr(8,8);
            }

        for(int i=0;i<int(ceil(message.size()/2.0))*2;i++)
            cascii[i] = binary2dec(cbit[i]);

        for(int i=0;i<int(ceil(message.size()/2.0))*2;i++)
            cypher.push_back(cascii[i]);

        return (cypher);
        }

    string decrypt(string cypher){

        unsigned char ascii[cypher.size()];
        string bit[cypher.size()];
        string doublebit[int(ceil(cypher.size()/2.0))];
        int asciidouble[int(ceil(cypher.size()/2.0))];
        string cbit[int(ceil(cypher.size()/2.0))*2];
        int cascii[int(ceil(cypher.size()/2.0))*2];
        string message;

        for(int i=0;i<cypher.size();i++)
            ascii[i] = cypher.at(i);

        for(int i=0;i<cypher.size();i++)
            bit[i] = dec2binary(ascii[i],8);

        for(int i=0;i<ceil(cypher.size()/2.0);i++){

            if((2*i+1)<cypher.size())
                doublebit[i] = bit[2*i].append(bit[2*i+1]);
            else{

                doublebit[i] = bit[2*i];

                while(doublebit[i].size()<16){

                    string t;
                    t.push_back('0');
                    t.append(doublebit[i]);
                    doublebit[i]=t;
                    }
                }
            }

        for(int i=0;i<ceil(cypher.size()/2.0);i++)
            asciidouble[i] = binary2dec(doublebit[i]);

        for(int i=0;i<ceil(cypher.size()/2.0);i++){

            mpz_class tmp = 0;

            mpz_ui_pow_ui(tmp.get_mpz_t(), asciidouble[i], d);
            mpz_mod_ui(tmp.get_mpz_t(), tmp.get_mpz_t(), n);

            asciidouble[i] = tmp.get_si();
            }

        for(int i=0;i<ceil(cypher.size()/2.0);i++)
            doublebit[i] = dec2binary(asciidouble[i],16);

        for(int i=0;i<ceil(cypher.size()/2.0);i++){
                cbit[2*i] = doublebit[i].substr(0,8);
                cbit[2*i+1] = doublebit[i].substr(8,8);
            }

        for(int i=0;i<int(ceil(cypher.size()/2.0))*2;i++)
            cascii[i] = binary2dec(cbit[i]);

        for(int i=0;i<int(ceil(cypher.size()/2.0))*2;i++)
            message.push_back(cascii[i]);

        return(message);
        }

    int binary2dec(string bits){

        int size = bits.size();
        int sum=0;

        for(int i=0;i<size;i++){

            if(bits.at(i)=='1')
                sum+=pow(2.0,size-(i+1));
            }

        return(sum);
        }

    string dec2binary(int decimal, int size){

        string binary;
        char bit;

        while(decimal>0){

            if(decimal%2==0)
                bit = '0';
            else
                bit = '1';

            string t;
            t.push_back(bit);
            t.append(binary);
            binary=t;
            decimal/=2;
            }

        while(binary.size()<size){

            string t;
            t.push_back('0');
            t.append(binary);
            binary=t;
            }

        return(binary);
        }

    long modinverse(long e, long temp){

        long d=1;

        while(true){

            if(d>=temp || (e*d)%temp==1)
                return d;

            d+=1;
            }
        }

    long cale(long n, long temp){

        for(long e=2; e<=n;e++){

            long i = gcd(e,temp);

            if(i==1)
                return e;
            }
        }

    long gcd(long x,long y){

        if(x%y==0)
            return y;
        else{

            y = gcd(y,x%y);
            return y;
            }
        }
    };

int main(){

    long p,q;
    string message;

    cout<<"\n\nRSA Encryption|Decryption\n";
    cout<<"-----------------------\n\n";

    cout<<"Enter Message:";
    getline(cin,message);

    cout<<"\n\nEnter P:";
    cin>>p;
    cout<<"\n\nEnter Q:";
    cin>>q;

    RSA *rsa = new RSA(p,q);

    string cypher = rsa->encrypt(message);

    cout<<"\n\nCypher: "<<cypher;

    message = rsa->decrypt(cypher);

    cout<<"\n\nOriginal Message:"<<message<<endl<<endl;

    return(0);
    }

