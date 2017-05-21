//#include <iostream>
//#include <fstream>
//#include <limits>
//#include <string>
//#include <ios>
//#include <stdlib.h>
//
//using namespace std;
//std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
//{
//    pos = in.tellg();
//    return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}
//
//std::string getLastLine(std::ifstream& in)
//{
//    std::ifstream::pos_type pos = in.tellg();
//
//    std::ifstream::pos_type lastPos;
//    while (in >> std::ws && ignoreline(in, lastPos))
//        pos = lastPos;
//
//    in.clear();
//    in.seekg(pos);
//
//    std::string line;
//    std::getline(in, line);
//    return line;
//}
//
//int main() {
//   // std::cout << "Hello, World!" << std::endl;
//   // return 0;
//    std::string x;
//    std::ifstream in("a.txt");char ch;
//   /* while (in.get(ch)){
//        std::cout << ch;
//
//    }*/
//    x=getLastLine(in);
//    int y=atoi(x.c_str());
//    cout<< y << endl;
//
//    while(getline(in,x)){
//        std::cout << x << std::endl;
//    }
//
//   /* FILE *file;
//    file=fopen("a.txt","rb");
//    //in.seekg(i);
//    //fseek(file,i,SEEK_SET);
//    char c;
//    string s;
//    while(getline(file,s){
//        cout << s;
//    }*/
//    //in.get(c);
//    //in.close();
//
//
//}
/*



void changeFile(const char string[6]);

void printFile2(string filename);

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

*/
/*ifstream readFile(string filename){
    //std::vector<char> v;
    ifstream fp(filename);

    return fp;
}*//*


std::wstring StringToWString(const std::string& s)
{
    std::wstring temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

void printFile(ifstream &file){
    string s;
    vector<string> final;
    stringmap localmap;
    //cout << file.good();
    while(getline(file,s)){
        vector<string> sep  = split(s,' ');
        for (int i = 0; i < sep.size() ; ++i) {
            std::wstring temp = StringToWString(sep[i]);
            stemming::english_stem<> StemEnglish;
            StemEnglish(temp);
            const std::string s( temp.begin(), temp.end() );
            //if(stopwords.)
            cout << s << endl;
            localmap[s]=1;
        }

    }
}


//int main(int argc, char const *argv[])
//{
//    //ifstream file =  readFile("simple/file1.txt");
//    ifstream file("simple/file1.txt");
//    //printFile(file);
//    printFile2("a.txt");
//    file.close();
//    changeFile("a.txt");
//
//    return 0;
//}

void printFile2(string filename) {
    ifstream in(filename);
    string s;
    int x = in.tellg();
    while(getline(in,s)){

        cout << x << " : " << s << endl;
        x = in.tellg();
    }

}

void changeFile(const char string[6]) {
    ifstream in(string);


}
*/
