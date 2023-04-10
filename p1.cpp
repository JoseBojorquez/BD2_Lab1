#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

struct Alumno {
    char codigo [5];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
};

istream & operator >> (istream & stream, Alumno & p){	
    stream.get(p.codigo, 5);
    stream.get(p.nombre, 11);
    stream.get(p.apellidos, 20);
    stream.get(p.carrera, 15);
    stream.get();
    return stream;
}

ostream & operator << (ostream & stream, Alumno & p){
	stream << p.codigo << " ";
    stream << p.nombre << " ";
    stream << p.apellidos << " ";
    stream << p.carrera << " ";
    stream << "\n";
	
	stream << flush;
	return stream;
}

class FixedRecord{
    private:
    string filename;

    public:
    FixedRecord(string _filename){
        filename = _filename;
    }

    vector<Alumno> load(){

        ifstream inFile;
        inFile.open(filename);
        string s;
        Alumno temp;
        vector<Alumno> res;

        if(inFile.is_open()){
            do{
                inFile >> temp;
                res.push_back(temp);
            }while(getline(inFile,s));
            inFile.close();
            res.pop_back();
        }
        else 
            cerr<<"No se pudo abrir el archivo\n";
        return res;
    }

    void add(Alumno record){
        ofstream outFile;
        outFile.open(filename, ios::app);

        if(outFile.is_open()){	
            outFile << record;
            outFile.close();            
        }
        else 
            cerr<<"No se pudo abrir el archivo\n";	
    }

    Alumno readRecord(int pos){
        ifstream inFile;
        inFile.open(filename);
        Alumno res;
        string s;
        int count = 0;

        if(inFile.is_open()){
            do{
                if(count == pos){
                    inFile >> res;
                }
                count++;
            }while(getline(inFile,s));
        }
        else 
            cerr<<"No se pudo abrir el archivo\n";
        return res;
    }
};

void ejemplo_load(string filename){
    FixedRecord record(filename);
    auto x = record.load();
    for(int i = 0; i<x.size();i++){
        cout<<x[i].codigo<<" "<<x[i].nombre<<" "<<x[i].apellidos<<" "<<x[i].carrera<<endl;
    }
    cout<<x.size()<<endl;
}

void readFromConsole(char buffer[], int size){
	string temp;			
	getline(cin,temp);
	for(int i=0; i<size; i++)		
		buffer[i] = (i < temp.size())? temp[i] : ' ';
	buffer[size-1] = '\0';
	cin.clear();
}

void ejemplo_add(string filename){
    FixedRecord record(filename);
    Alumno temp;
    cout<<"codigo: "; readFromConsole(temp.codigo,5);
    cout<<"nombre: "; readFromConsole(temp.nombre,11);
    cout<<"apellidos: "; readFromConsole(temp.apellidos,20);
    cout<<"carrera: "; readFromConsole(temp.carrera,15);
    record.add(temp);
}

void ejemplo_readRecord(string filename){
    FixedRecord record(filename);
    int pos;
    cout<<"Index: "; cin>>pos;
    Alumno temp = record.readRecord(pos);
    cout<<temp.codigo<<" "<<temp.nombre<<" "<<temp.apellidos<<" "<<temp.carrera<<endl;
}

int main(){
    //cambiar filename segun la necesidad
    string filename = "datos1.txt";
    ejemplo_load(filename);
    ejemplo_add(filename);
    ejemplo_load(filename);
    ejemplo_readRecord(filename); 
}

