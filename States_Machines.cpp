#include <iostream>
#include <list>
#include <queue>

using namespace std;
/*
	Máquina que dada una gramática puede o no reconocer un lenguaje, para resolverlo utilice una implementación
 	de grafo, donde cada nodo representa un estado, de esta manera las aristas son las distintas transiciones 
 	de la máquina.
 */


class NodosAdyacentes //Esta clase representa los posibles estados a los que puede saltar un estado actual de llegarle un símbolo
{
	public:
		//Atributos
		int Nombre;//Nombre del estado
		char Transicion;//Símbolo de transición
		//Metodos
		NodosAdyacentes()//constructor que inicializa la clase on valores que nunca se podrán alcanzar
		{
			Nombre=0;
			Transicion=' ';
		}
		NodosAdyacentes(int Name,char Trans)//Constructor que establece valores a los atributos.
		{
			Nombre=Name;
			Transicion=Trans;
		}

};

class Nodos//Clase que representa los estados de la máquina
{
	public:
		//Atributos
		int Nombre;//Nombre del estado
		bool Final;//Indica si el estado es final
		list<NodosAdyacentes> Adyacentes;//Lista de posibles estados de llegada
		//Metodos
		Nodos()//Constructor sin parámetros que establece valores inalcanzables
		{
			Nombre=0;
			Final=false;
			Adyacentes=list<NodosAdyacentes>();
		}
		Nodos(int Nom,bool Fin)//Constructor parametrizado que establece valores otorgados para los atributos de la clase
		{
			Nombre=Nom;
			Final=Fin;
			Adyacentes=list<NodosAdyacentes>();
		}
};

class Grafo//Clase Grafo que tendrá una lista de nodos/estados asociados al grafo
{
	public:
		//Atributos
		int NumNodos;//Numero de estados de la máquina
		list<Nodos> Estados;//Lista de estados de la máquina
		queue<string> Pruebas;//Cola de las cadenas de prueba de la máquina
		//Metodos
		Grafo()//Constructor sin parámetros que establece valores inalcanzables
		{
			NumNodos=0;
			Estados= list<Nodos>();
			Pruebas= queue<string>();
		}

		void AgregarGrafo(int NumEstados,int NumTer,int NumNoTer,int NumPruebas);//Pérmite agregar un grafo a la clase
		char VerificarCadena();//Verifica si las cadenas de la cola de pruebas pertenecen o no al lenguaje
};

void Grafo::AgregarGrafo(int NumEstados,int NumTer,int NumNoTer,int NumPruebas)
{
	int Finales=0, Origen=0,Destino=0;//Definición de variables a leer
	char Transicion=' ';//Definición de variables a leer
	string Cadenas;//Definicion de variables a leer

	list<Nodos>::iterator it;//Apuntador a objetos de la clase nodo
	list<NodosAdyacentes>::iterator it2;//Apuntador a objetos de la clase NodosAdyacentes
	
	NumNodos=NumEstados;//Transfiero el parametro a la clase

	for(int i=1;i<=NumNodos;i++)
	{
		Estados.push_back(Nodos(i,false));//creo el numero de nodos que son pasados por parametros
	}

	for(int i=1;i<=NumTer;i++)
	{
		it=Estados.begin();//Inicializo el apuntador it al principio de la lista de estados
		cin>>Finales;//lee valor del estado terminal

		for(int i=1;i<Finales;i++)//mueve el apuntador it hasta el estado correspondiente
			it++;

		it->Final=true;//asigna verdad al atributo final del estado al que apunta
	}
	
	for(int i=0;i<NumEstados*NumNoTer;i++)//lee las producciones
	{
		it=Estados.begin();//coloca el apuntador it al principio de la lista de los estados
		cin>>Origen;//lee el origen
		cin>>Destino;//lee el destino
		cin>>Transicion;//lee la transicion

		for(int i=1;i<Origen;i++)//Desplaza el apunatdor hasta el estado correspondiente
			it++;

		it->Adyacentes.push_back(NodosAdyacentes(Destino,Transicion));//Coloca un nodoadyacente en la lista de adyacentes del nodo
	}
	
	for(int i=1;i<=NumPruebas;i++)//lee las cadenas de prueba y las coloca en una cola de strings
	{
		cin>>Cadenas;

		Pruebas.push(Cadenas);
	}
}
char Grafo::VerificarCadena()//Definición del metodo de verificacion de cadena
{
	string cadena;//Auxiliar de string para jalar la cadena de la cola y colocarla aca
	list<Nodos>::iterator it;//Apuntador a objetos de la clase nodo
	list<NodosAdyacentes>::iterator it1;//Apuntador a objetos de la clase NodosAdyacentes
	char auxTrans;//Transicion, almacena un caracter del string
	
	while(!Pruebas.empty())//Mientras la cola no este vacia
	{
		cadena=Pruebas.front();//A Cadena se le asigna el primer elemento de la cola
		Pruebas.pop();//Se desencola el primero elemento de la cola
		it=Estados.begin();//Se coloca el apunatdor it al primer elemento de la lista de estados

		for(int i=0;i<cadena.size();i++)//Mientras no se recorran todas las posciioens del string cadena
		{			
			auxTrans=cadena[i];//Se almacena en esta avriable un acracter de la cadena en una posicion dada

			it1=it->Adyacentes.begin();//Se coloca el apuntador it1 en la primera posicion de la lista de nodos adyacentes de un estado dado
			
			while(it1->Transicion != auxTrans)//Mientras la transicion no coincida con el elemento que se saco del string, se aumenta el apuntador
				it1++;

			it=Estados.begin();//Se coloca el apuntado de estados al principio de la lista

			for(int i=1;i<it1->Nombre;i++)//Mientras no se llegue al estado al que va la transicion, se aumenta el apuntador de estados
				it++;
		}
		
		if(it->Final)//Si el estado es un estado final, se imprime Y, en caso contrario se imprime N
			cout<<'Y'<<endl;
		else
			cout<<'N'<<endl;
	}
}

int main()
{
	int T,N,F,M,S;
	Grafo A= Grafo();

	cin>>T;

	for(int i=0;i<T;i++)
	{
		A= Grafo();
		cin>>N>>F>>M>>S;
		A.AgregarGrafo(N,F,M,S);
		A.VerificarCadena();
	}

	return 0;
}