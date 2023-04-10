#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
#include <string.h>
#include <string>
using namespace std;

struct Alumno{
    string Nombre;
    string Apellidos;
    string Carrera;
    float mensualidad;
};

Alumno stringToAlumno(string s){
    Alumno res;
    vector<int> division;
    int siz = s.size();
    for(int i = 0;i < siz;i++){
        if(s[i] == '|'){
            division.push_back(i);
        }
    }
    res.Nombre = s.substr(0,division[0]);
    res.Apellidos = s.substr(division[0]+1,division[1]-division[0]-1);
    res.Carrera = s.substr(division[1]+1,division[2]-division[1]-1);
    string temp = s.substr(division[2]+1,s.size()-division[2]);
    res.mensualidad = stof(temp);

    return res;
}

ostream & operator << (ostream & stream, Alumno & p){
	stream << p.Nombre;
    stream << "|";
	stream << p.Apellidos;
    stream << "|";
    stream << p.Carrera;
    stream << "|";
    stream << to_string(p.mensualidad);
    stream << "\n";	
	
	stream << flush;
	return stream;
}

class VariableRecord{
    private:
    string filename;

    public:
    VariableRecord(string _filename){
        filename = _filename;
    }

    vector<Alumno> load(){

        ifstream inFile;
        inFile.open(filename);
        string s;
        Alumno temp;
        vector<Alumno> res;
        
        getline(inFile,s); //salto de la primera linea indicado en el enunciado
        if(inFile.is_open()){
            while(getline(inFile,s)) {
                temp = stringToAlumno(s);
                res.push_back(temp);
            }
            inFile.close();
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
        string s;
        Alumno res;
        int count = 0;

        getline(inFile,s);
        if(inFile.is_open()){
            while(getline(inFile,s)) {
                if(count == pos){
                    res = stringToAlumno(s);
                }
                count++;
            }	
            inFile.close();
        }
        else 
            cerr<<"No se pudo abrir el archivo\n";
        return res;
    }
};

void ejemplo_load(string filename){
    VariableRecord r (filename);
    auto x = r.load();
    for(int i = 0; i<x.size();i++){
        cout<<x[i].Nombre<<" "<<x[i].Apellidos<<" "<<x[i].Carrera<<" "<<x[i].mensualidad<<endl;
    }
    cout<<x.size()<<endl;
}

void ejemplo_add(string filename){
    VariableRecord r (filename);
    Alumno temp;
    cout<<"Nombre: "; getline(cin,temp.Nombre);
    cout<<"Apellidos: "; getline(cin,temp.Apellidos);
    cout<<"Carrera: "; getline(cin,temp.Carrera);
    cout<<"mensualidad: "; cin>>temp.mensualidad;
    r.add(temp);
}

void ejemplo_readRecord(string filename){
    VariableRecord r (filename);
    int pos;
    cout<<"Index: "; cin>> pos;
    Alumno temp = r.readRecord(pos);
    cout<<temp.Nombre<<" "<<temp.Apellidos<<" "<<temp.Carrera<<" "<<temp.mensualidad<<endl;
}

int main(){
    //cambiar filename segun la necesidad
    string filename = "datos3.txt"; 
    ejemplo_load(filename);
    ejemplo_add(filename);
    ejemplo_load(filename);
    ejemplo_readRecord(filename);
}

