/*3. Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente). */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int nprod {5};

void mostS(string v[], int dim){        //mostrar vectores de tipo string
    for(int i = 0; i < dim; i++){
        cout << "v[" << i << "] : " << v[i] << endl; 
    }
}

void mostI(int v[], int dim){           //mostrar vectores de tipo entero
    for(int  i = 0; i < dim; i++){
        cout << "v[" << i << "] : " << v[i] << endl;
    }
}

void mostF(float v[], int dim){         //mostrar vector de tipo flotante
    for(int i = 0; i < dim; i ++){
        cout <<"v[" << i << "] : " << v[i] << endl;
    }
}

void mostFS(float v[], int dim, string prod[]){ //mostrar vector de tipo flotante con nombres
    for(int i = 0; i < dim; i ++){  
        cout << prod[i] << " : " << v[i] << endl;
    }
}

void mostMf(float m[][nprod], int ncl, string nomb[], string pro[]){    //mostrar matrices de variable flotante
    for(int i = 0; i < ncl; i++){
        for(int j = 0; j < nprod; j++){
            cout << nomb[i] << " " << pro[j] << " : " << m[i][j] << endl;
        }
    }
}

void mostMi(int m[][nprod], int ncl, string nomb[], string pro[]){  //mostrar matrices de variable entera
    for(int i = 0;  i < ncl; i++){
        for(int j = 0; j < nprod; j++)
            cout << nomb[i] << " " << pro[j] << " : " << m[i][j] << endl;
    }

}

void mayor(float m[][nprod], int ncl, string nomb[], string pro[]){ //listado de clientes cuyos productos superan los 13000kg (punto 1)
    cout << "\n Listado :" << endl;
    for(int i = 0; i < ncl; i++){
        cout << nomb[i] << " = ";
        for(int j = 0; j < nprod; j++)
            if(m[i][j] > 13000){
                cout << pro[j] << ",";
            }
    cout << endl;
    }

}

void superan(float m[][nprod], int ncl, int aux[]){ //genera un vector con la cantidad de veces que cada cliente supera los 13000kg
    aux[ncl];                                       //(punto 2)       
    int sup ;
    for(int i = 0; i < ncl; i++){
        sup = 0;
        for(int j = 0; j < nprod; j++)
            if(m[i][j] > 13000){
                sup++;     
            }
    aux[i] = sup;
    }
}

int BusMay(int v[], int dim){        //Busca el mayor elemento del vector que fue generado anteriormente
    int max = v[0];                 // para saber cual fue el cliente con mas cantidad de veces que supero los 13000kg
    int imax = 0;                   //se complementa con la funcion de arriba (punto 2)
    for(int i = 0; i < dim; i++){
        if(v[i] > max){
            max = v[i];
            imax = i;
        }
    }
    return imax;
}
int BusMayF(float v[], int dim){        //Busca el mayor elemento del vector que fue generado anteriormente
    int max = v[0];                 // para saber cual fue el cliente con mas cantidad de veces que supero los 13000kg
    int imax = 0;                   //se complementa con la funcion de arriba (punto 2)
    for(int i = 0; i < dim; i++){
        if(v[i] > max){
            max = v[i];
            imax = i;
        }
    }
    return imax;
}

void sortdoble(float v[], int tam, string vpaux[]){     //ordenamiento del vector (punto 2)
    int i, j, imax;
    for(i = 0; i < tam - 1; i++){
        imax = i;
        for(j = i+1; j < tam; j++)
            if(v[j] < v[imax])
                imax = j;
        swap(v[i],v[imax]);
        swap(vpaux[i],vpaux[imax]);    
    }
}

int main(){

    const int nclient {8};        
    float dist[nclient][nprod] {};  //distancia de cada cliente-producto
    float peso[nclient][nprod] {};  //peso de cada cliente-producto
    int entregas[nclient][nprod] {}; //entregas de cada cliente-producto (punto3)

    bool debug {true}; //Para mostrar los carteles de seguimiento

    string clientes[nclient];   //nombre de los clientes
    string producc[nprod];      //nombre de los productos

    ifstream nombres;       //lectura de los nombres de clientes y productos
    nombres.open("Nombres.txt");
    if(! nombres){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    for(int i = 0; i < nclient && nombres >> clientes[i]; i++); // se cargan los nombres de clientes a partir de los archivos
    for(int i = 0; i < nprod && nombres >> producc[i]; i++);    //se cargan los nombres de los productos a partir de los archivos
    nombres.close();

    ifstream datos;
    datos.open("Datos1.txt");
    if(! datos){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int iclie, iprod;   
    float ipeso, idist;
    while(datos >> iclie >> iprod >> ipeso >> idist ){  //se cargan los datos de peso y distancia en sus respectivas matrices
        peso[iclie][iprod] += ipeso;
        dist[iclie][iprod] += idist;
        entregas[iclie][iprod]++;
    }
    datos.close();

    if(debug){  //mostrar los datos recien cargados; entregas, pesos, distancias, clientes y productos
    mostS(clientes, nclient );
    cout <<"\nPesos : " << endl;
    mostMf(peso,nclient,clientes,producc);
    cout << "\nDistancias : " << endl;
    mostMf(dist, nclient,clientes,producc);
    cout << "\nEntregas : " << endl;
    mostMi(entregas, nclient, clientes, producc);
    }

    //punto 1
    cout << "\n===============Punto 1===============" << endl;
    mayor(peso,nclient,clientes,producc);

    //punto 2
    cout << "\n===============Punto 2===============" << endl;
    int may;
    int supve[nclient]{};   // vector "auxiliar" para saber la cantidad de veces que cada cliente supero los 13000kg con cada producto
    superan(peso,nclient,supve);
    if(debug){mostI(supve,nclient);}
    may = BusMay(supve,nclient); //recibe las coordenadas del mayor elemento del vector
    //cout << "\nEl cliente con mas product que superan los 13milkg es:  " << clientes[may] << endl;
    float auxd[nprod]{};    //vector para guardar la distancia del cliente (may) de cada producto
    for(int i = 0; i < nprod; i++){
        auxd[i] =  dist[may][i];
    }
    if(debug){mostF(auxd,nprod);}
    string auxv[nprod];     //vector auxiliar de los nombres, para no perder su posicion inicial al ordenarlos
    for(int i = 0; i < nprod; i++){
        auxv[i] = producc[i];
    }
    sortdoble(auxd,nprod,auxv);
    mostFS(auxd,nprod,auxv);

    //punto 3
    cout << "\n===============Punto 3===============" << endl;
    float vaux[nprod]{};
    for(int i = 0; i < nprod; i++){     
        vaux[i] =  dist[may][i];        
    }
    int mayor = BusMayF(vaux,nprod);    //No pude encontrar otra forma que no sea por el llamado a la funcion mayor
    int sum {};
    for(int i = 0; i < nclient; i++){
        sum += entregas[i][mayor];
    }
    cout << "Cantidad de entregas para el tipo de producto " << producc[mayor] << " : " << sum;

    return 0;
}