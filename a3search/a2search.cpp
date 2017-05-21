//
// Created by avina on 5/16/2017.
//

//g++ -std=c++11 test.cpp
#include <ios>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "english_stem.h"
#include <unordered_map>
#include <unordered_set>
#include <dirent.h>

using namespace std;

typedef vector<string> StringVector;
typedef std::unordered_map<std::string,int> stringmap;
typedef std::unordered_map<char,unordered_map<std::string,int>> charAlphabetMap;
stringmap addressmap;
string sourceDir,destDir;
charAlphabetMap indexMap;
stringmap finalIndexMap;
const string HASHFILE = "indexHash.txt";

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

unordered_set<std::string> stopwords={"a", "an", "and", "are", "as", "at", "be", "but", "by",
                          "for","from","if", "in", "into", "is", "it",
                          "no", "not", "of", "on", "or", "such",
                          "that", "the", "their", "then", "there", "these",
                          "they", "this", "to", "was", "will", "with"};

charAlphabetMap readFileinVector(string fileName);


stringmap updateIndexFile(string filename, int &i, const string key, string data,stringmap wordmap);

void writeIndexHashInFile(string folder);

void loadIndexInMemory(string dest);

StringVector listFileFromDir(string dir){
    DIR *pDIR;
    struct dirent *entry;
    StringVector listOfFile;
    if( pDIR=opendir(dir.c_str()) ){
        while(entry = readdir(pDIR)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                //listOfFile.push_back(dir+separator()+entry->d_name);
                listOfFile.push_back((basic_string<char, char_traits<char>, allocator<char>> &&) entry->d_name);
        }
        closedir(pDIR);
    }
    return listOfFile;
}

std::wstring StringToWString(const std::string& s)
{
    std::wstring temp(s.length(),L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

/*void  writeMapinFile(stringmap map,string filename){
    ofstream out(filename);
    for(auto const &ent1 : map){
        cout << out.tellp()<<endl;
        std::stringstream ss;
        ss << ent1.first << "=" << to_string(ent1.second) << endl;
        out << ss.rdbuf();
    }

}*/
/*void  writeMapinFile(charAlphabetMap map,string filename){
    ofstream out(filename);
    for(auto const &ent1 : map){
            out << ent1.first << endl;
        for(auto const &ent2:ent1.second){
            cout << out.tellp()<<endl;
            std::stringstream ss;
            ss << ent2.first << "=" << to_string(ent2.second) << endl;
            out << ss.rdbuf();
        }

    }

}*/

void  writeMapinFile(charAlphabetMap map,string dir,string ogFile){
    //ofstream out(filename);
    mkdir(dir.c_str());
    stringmap indexWordMap;
    //indexWordMap.clear();
    for(auto const &ent1 : map){
        if(indexMap.find(ent1.first)!=indexMap.end()){
            indexWordMap = indexMap[ent1.first];
        }
        string filename = dir+separator()+ent1.first+".txt";
        ofstream out(filename,ios::binary | ios::app | ios::ate);
        //out<<endl;
        if(!out){
            out.open(filename,ios::binary);
        }
        //out << ent1.first << endl;
        for(auto const &ent2:ent1.second){
            string data = ogFile +":" + to_string(ent2.second);
            if(indexWordMap.find(ent2.first)==indexWordMap.end()){
                //cout << out.tellp()<<endl;

                std::stringstream ss;
                //cout << ent2.first<< ":"<< out.tellp()<<endl;
                indexWordMap[ent2.first]=out.tellp();
                ss << ent2.first << "=" << data  << endl;
                out << ss.rdbuf();
            } else{
                indexWordMap = updateIndexFile(filename,indexWordMap[ent2.first],ent2.first,data,indexWordMap);
            }

        }
        indexMap[ent1.first]=indexWordMap;
        out.close();

    }

}

stringmap updateIndexFile(string filename, int &i, const string key, string data,stringmap wordmap) {
   // stringmap wordmap;
    ifstream in(filename);
    string s;
    string temp;
    in.seekg(i);
    getline(in,temp);
    vector<string> xv;
    while(getline(in,s)){
        xv.push_back(s);
    }
    in.close();
    fstream out(filename,ios::in | ios::out);
    out.seekp(i);
    //cout << out.tellp()<<":"<<s << endl;
    out << temp <<'|'<< data << endl;
    for(auto const x : xv){
        vector<string> tempV = split(x,'=');
        wordmap[tempV[0]]=out.tellp();
        out << x<<endl;
    }
    out.close();

    return wordmap;
}


void createIndexFile(string source,string dest){
    //dest="index";
    DIR* dir = opendir(dest.c_str());
    if(dir)
        return;
    StringVector listOffiles = listFileFromDir(source);
    for(auto const &file : listOffiles){
        charAlphabetMap wordmap = readFileinVector(file);
        writeMapinFile(wordmap,dest,file);
    }
    writeIndexHashInFile(dest);
}

void writeIndexHashInFile(string folder)
{
    string fileLocation = folder + separator() + HASHFILE;
    ofstream out(fileLocation, ios::binary);
    for(auto const &ent : indexMap){
        for(auto const &ent2 : ent.second){
            out << ent2.first << '=' << ent2.second<<endl;
        }
    }

}

int main(int argc, char const *argv[]){
    sourceDir="books200m";
    destDir = "index";
    createIndexFile(sourceDir,destDir);
    loadIndexInMemory(destDir);
    //listFileFromDir("simple");
    //charAlphabetMap wordmap = readFileinVector("simple/file1.txt");
    //writeMapinFile(wordmap,"a1.txt");
    return 0;
}

void loadIndexInMemory(string dest) {
    finalIndexMap.clear();
    string fileLocation = dest+separator()+HASHFILE;
    ifstream in(fileLocation,ios::binary);
    string s;
    vector<string> temp;
    while(getline(in,s)){
        temp=split(s,'=');
        finalIndexMap[temp[0]]=stoi(temp[1]);
    }
    /*for(auto const &x : finalIndexMap){
        cout << x.first << ":" << x.second;
    }*/
}

charAlphabetMap readFileinVector(string fileName) {
    fileName = sourceDir+separator()+fileName;
    ifstream in(fileName);
    charAlphabetMap indexMap;
    stringmap localmap;
    localmap.clear();
    string s;
    vector<string> sep;
    while (getline(in,s)){
        sep  = split(s,' ');
        for(int i=0;i<sep.size();i++){
            std::wstring temp = StringToWString(sep[i]);
            stemming::english_stem<> StemEnglish;
            StemEnglish(temp);
            transform(temp.begin(),temp.end(),temp.begin(),::tolower);
            const std::string s( temp.begin(), temp.end() );

            if(stopwords.find(s)==stopwords.end()){
                char temp = s[0];
                if(indexMap.find(temp)!=indexMap.end()){
                    localmap=indexMap[temp];
                } else{
                    localmap.clear();
                }
                if(localmap.find(s)==localmap.end()){
                    localmap[s]=1;
                }
                else{
                    localmap[s]=localmap[s]+1;
                }
                indexMap[temp]=localmap;
            }
        }
    }
    return indexMap;
}