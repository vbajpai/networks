/* Cyclic Redundancy Check

   Generator Polynomial Used: 10011
*/

#include<iostream>
using namespace std;

class CRC{

    string frame;
    string generator;

    public:

    CRC(string frame, string generator){

        this->frame = frame;
        this->generator = generator;

        }

    string calculate(){

        append();

        string remainder = modulo2divide();

        string transmitframe = add(remainder);

        return(transmitframe);
        }

    string add(string remainder){

        string temp;

        for(int i=0;i<remainder.size();i++){

            char c = charxor(remainder.at(i), frame.at(frame.size() - remainder.size()));
            temp.push_back(c);

            }

        string newstring = frame.substr(0,frame.size() - remainder.size());

        newstring.append(temp);

        return(newstring);

        }

    string modulo2divide(){

        string substring;

        int size = generator.size();

        int i = 0;

        substring = frame.substr(0,size);

        while(true){

            substring = subfromgen(substring);

            if(generator.size() + i == frame.size())
                break;

            substring.push_back(frame.at(generator.size() + i));

            i++;

            }

        return (substring);

        }

    string subfromgen(string substring){

        string result;

        if(substring.at(0) == '0')
            return(substring.substr(1));

        for(int i=1;i<generator.size();i++){

            char c = charxor(substring.at(i), generator.at(i));

            result.push_back(c);

            }

        return (result);

        }

    char charxor(char a, char b){

        if((a == '1' && b == '1') || (a == '0' && b == '0'))
            return '0';

        else
            return '1';

        }

    void append(){

        int i =  (generator.size() - generator.find_first_of('1') - 1);

        while(i>0){

            frame.append("0");
            i--;
            }

        }
    };


int main(){

    string frame, generator = "10011";

    cout<<"Cyclic Redundancy Check\n";
    cout<<"-----------------------\n\n";
    cout<<"Generator Polynomial Used: "<<" x4 + x + 1\n\n";

    cout<<"Enter Frame: ";
    cin>>frame;

    if(frame.size() <= 5){

        cout<<"\n\nFrame must be longer than Generator!\n\n";
        return(-1);

        }


    CRC *c = new CRC(frame, generator);

    string result = c->calculate();

    cout<<"\n\nChecksumed Frame: "<<result<<endl<<endl;

    return(0);

    }
