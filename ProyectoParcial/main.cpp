
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int N;
vector<string> equipos;
vector<int> peso;
int **matriz;

void imprimeMatriz(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout<<matriz[j][i]<<" ";
        }
        cout<<endl;
    }
}

int generaPartidos(int x1, int y1, int sX, int sY){
    if(sX == 0) return 0;
    else{
        for(int i = 0; i < sY/2; i++){
            matriz[x1+sX/2][y1+sY/2+i] = matriz[x1][y1+i];
        }
        int contY = 0;
        for(int i = sY/2; i <sY; i++){
            matriz[x1+sX/2][y1+contY] = matriz[x1][y1+sY/2+ contY];
            contY++;
        }
        generaPartidos(x1, y1, sX/2, sY/2);
        generaPartidos(x1 + sX/2, y1, sX/2, sY/2);
        generaPartidos(x1, y1 + sY/2, sX/2, sY/2);
        generaPartidos(x1 + sX/2, y1 + sY/2, sX/2, sY/2);
    }
    return 0;
}

void generaPartidos(){
    if(N % 2 == 0){
        generaPartidos(0, 0, N, N);
    }
}

void crearMatriz(){
    if(N % 2 == 0){
        matriz = new int *[N];
        for(int i = 0 ; i < N; i++){
            matriz[i] = new int[N];
        }
        for(int i = 0 ; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == 0){
                    matriz[i][j] = j+1;
                }else{
                    matriz[i][j] = 0;
                }
            }
        }
    }else{
        matriz = new int *[N+1];
        for(int i = 0 ; i < N+1; i++){
            matriz[i] = new int[N];
        }
        for(int i = 0 ; i < N+1; i++){
            for(int j = 0; j < N; j++){
                if(i == 0){
                    matriz[i][j] = j+1;
                }else{
                    matriz[i][j] = 0;
                }
            }
        }
    }
}

void leerArchivo(string ruta){
    string delimiter = " ";
    size_t pos;
    string line;
    ifstream myfile(ruta);
    if (myfile.is_open())
    {
        getline(myfile,line);
        N = stoi(line);
        while (getline(myfile,line))
        {
            pos = 0;
            string token;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                equipos.push_back(token);
                //cout << token << endl;
                line.erase(0, pos + delimiter.length());
            }
            //cout << line << endl;
            peso.push_back(stoi(line));
        }
        myfile.close();
    }
    else{
        cout << "No se pudo leer el archivo";
    }
}

int main(){
    
    leerArchivo("/Users/Antonio/Desktop/Algoritmos/ProyectoParcial/Equipos.txt");
    crearMatriz();
    generaPartidos();
    imprimeMatriz();
    cout<<"Número de equipos: "<<N<<endl;
   
    //cout<<sizeof(matriz)/sizeof(*matriz);
    return 0;
}