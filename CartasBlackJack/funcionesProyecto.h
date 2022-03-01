#pragma once
#include <string>
#include <time.h>  //Incluimos las librerias y las estructuras a usar
#include "estructuras.h" 
//Metodo para revisar que el dato pasado sea un numero
bool revisaSiEsNumero(string elNumero) {
	//Crea una variable booleana en true
	bool revision = true;
	//En caso de encontrar una letra se convierte en false
	for (int i = 0; i < elNumero.length(); i++)
	{
		if (!isdigit(elNumero[i])) {
			revision = false;
		}
	}
	//Retorna esa variable
	return revision;
}
//Metodo para crear la baraja de cartas
void crearBaraja(vector<Cartas>& vect) {
	//Se crea la variable necesaria para trabajar
	string valorCarta;
	//Se crea un for hasta 13 para crear las cadenas de cartas
	for (int i = 0; i < 13; i++)
	{
		//Acorde al valor de i, la carta sera una de las letras clasicas del naipe
		if (i == 0) {
			valorCarta = "A";
		}
		else if (i == 10) {
			valorCarta = "J";
		}
		else if (i == 11) {
			valorCarta = "Q";
		}
		else if (i == 12) {
			valorCarta = "K";
		} //si no es ninguno de esos numeros guardamos la i sumandole 1
		else {
			valorCarta = to_string(i + 1);
		}
		//Colocamos los palos de cada cadena de cartas, acorde al numero de la i
		vect[i].numero = valorCarta, vect[i].palo = 3;
		vect[double(i) + 13].numero = valorCarta, vect[double(i) + 13].palo = 4;
		vect[double(i) + 26].numero = valorCarta, vect[double(i) + 26].palo = 5;
		vect[double(i) + 39].numero = valorCarta, vect[double(i) + 39].palo = 6;
	}

}
//Metodo para repartir las cartas a los jugadores
void repartirCartas(vector<Cartas>& vect, vector<Jugador>& jugador, int pos) {
	//Creamos el numero random
	int numRandom;
	srand(time(NULL));
	//Se crea un bucle de iteracion 2

	for (int i = 0; i < 2; i++)
	{	//Se genera un numero random entre el vector de cartas
		numRandom = rand() % vect.size();
		jugador[pos].manoJugador.push_back(vect[numRandom]); //Se le agrega a la mano del jugador
		vect.erase(vect.begin() + numRandom);	//Eliminamos ese del vector de cartas
	}
}
//Metodo para crear a los jugadores
void crearJugadores(vector<Jugador>& vectJugador, vector<Cartas>& vectCartas) {
	//Solicitamos el nombre del jugador
	string nombre = "";
	cin.ignore(); //Se limpian los inputs anteriores
	//Con un for de 3 veces
	for (int i = 0; i < 3; i++)
	{
		system("cls");
		cout << "\n\n\tNombre para el jugador " << i + 1 << ":\n\t";
		getline(cin, nombre);	//Solicitamos el nombre
		vectJugador[i].nombreJugador = nombre; //Le asignamos el nombre a la estructura
		vectJugador[i].activo = true; //Colocamos estado como activo (que se encuentra jugando)
		repartirCartas(vectCartas, vectJugador, i); //Le repartimos sus cartas
	}

}
//Metodo para calcular suma de las cartas de los jugadores
int calcularSuma(vector<Jugador> jugador, int pos) {
	//Creamos un variable int
	int sumaMano = 0;
	//Hacemos un for por cada carta que tenga en la mano
	for (int i = 0; i < jugador[pos].manoJugador.size(); i++)
	{	//Revisamos si posee letras y le aumentamos 10 al numero
		if (jugador[pos].manoJugador[i].numero == "J" || jugador[pos].manoJugador[i].numero == "Q" || jugador[pos].manoJugador[i].numero == "K") {
			sumaMano += 10;
		} // Si no le aumentamos el numero
		else if (jugador[pos].manoJugador[i].numero != "A") {
			sumaMano += stoi(jugador[pos].manoJugador[i].numero);
		}

	}
	//Hacemos un for por cada carta que tenga en la mano
	for (int i = 0; i < jugador[pos].manoJugador.size(); i++)
	{	//Revisamos en caso de que tenga un As, se le asigna el valor acorde a las sumas anteriores
		if (jugador[pos].manoJugador[i].numero == "A") {
			if (sumaMano + 11 <= 21) {
				sumaMano += 11;
			}
			else {
				sumaMano += 1;
			}
		}
	}
	//Retornamos la suma de la mano
	return sumaMano;
}
//Metodo para tomar la carta extra
void cartaExtra(vector<Cartas>& vect, vector<Jugador>& jugador, int pos) {
	//Creamos un aleatorio para asignar
	int numRandom;
	srand(time(NULL));
	//Se genera el numero aleatorio
	numRandom = rand() % vect.size();
	jugador[pos].manoJugador.insert(jugador[pos].manoJugador.begin(), vect[numRandom]); //Esa carta se le asigna a la mano
	vect.erase(vect.begin() + numRandom); //Se borra esa carta de la baraja

}
//Metodo para mostrar la mano del jugador
void mostrarMano(vector<Jugador> jugador, int pos) {
	//Hacemos un for para pasar por cada carta del jugador
	for (int i = 0; i < jugador[pos].manoJugador.size(); i++)
	{	//Vamos imprimiendo cada una de las cartas que posee
		cout << "[" << jugador[pos].manoJugador[i].numero << jugador[pos].manoJugador[i].palo << "] ";
	}
	//Mostramos la suma de la mano que tendra el jugador
	cout << "\n\n\tSuma de la mano: " << calcularSuma(jugador, pos) << "\n\n";
}
//Metodo para declarar quien gano
void declararGanador(vector<Jugador>& jugador) {
	//Creamos la variables para trabajar
	int cont = 0;
	int sumaMayor = 0;
	//Se crea un bucle
	do {
		if (jugador[cont].activo == false) { //Si el jugador no se encuentra activo 
			jugador.erase(jugador.begin() + cont); //Se elimina
			cont = 0; //Cont vuelve a ser 0
		}
		else {
			cont++; //En caso de que no se aumenta
		}
	} while (cont < jugador.size()); //Mientras cont sea menor a la cantidad de jugadores

	for (int i = 0; i < jugador.size(); i++) //Se hace un for del tamano de la cantidad de jugadores
	{
		if (calcularSuma(jugador, i) > sumaMayor) { //Identificamos cual va ser el mayor 
			sumaMayor = calcularSuma(jugador, i);
		}
	}
	//Si todos se pasaron quedo vacio el vector y nadie ha ganado
	if (jugador.size() == 0) {
		system("cls");
		cout << "\n\n\tNadie ha ganado!\n\n\t";	//Se informa de que nadie ha ganado
		system("pause");
	}
	else {

		system("cls");
		for (int j = 0; j < jugador.size(); j++) //Un bucle para evaluar el ganador, en caso de varios tengan la cifra mayor significa empate y se muestran
		{
			if (calcularSuma(jugador, j) == sumaMayor) {

				cout << "\n\n\tGanador: " << jugador[j].nombreJugador //Imprimimos al/los ganadores
					<< "\n\n\tCon La Mano: ";
				mostrarMano(jugador, j);
				cout << "\n\n";
			}

		}
		cout << "\t";
		system("pause");
	}
}
//Metodo para limpiar los vectores
void limpiarVectores(vector<Cartas>& cartas, vector<Jugador>& jugadores) {
	//Vaciamos todos los vectores para evitar errores en juegos nuevos, en caso de que se inicie una partida luego de terminar otra
	cartas.resize(0);
	jugadores.resize(0);
	cartas.resize(52);
	jugadores.resize(3);
	//Creamos la baraja y los jugadores 
	crearBaraja(cartas);
	crearJugadores(jugadores, cartas);

}
//Metodo para mostrar el menu al usuario
int menuUsuario(vector<Jugador> jugadores, int pos) {
	//Variable a trabajar 
	string op;
	//Mostramos un menu para el usuario
	do {
		system("cls");
		cout << "  " << jugadores[pos].nombreJugador << " >>>  ";
		mostrarMano(jugadores, pos);
		cout << "  \n\n\tSeleccione una opci\242n"
			<< " \n\t-----------------------"
			<< "    \n\t1 - Pedir carta"
			<< "    \n\t2 - Pasar Turno"
			<< " \n\t-----------------------\n\n\t";
		cin >> op;
	} while (revisaSiEsNumero(op) != true); //Se hace hasta que el valor sea un numero valido
	//Devolvemos como int
	return stoi(op);
}
//Metodo para organizar los cases
void funcionCases(int& turno, vector<Jugador>& jugadores, vector<Cartas>& mazoCartas, int pos) {
	//variable a trabajar 
	int op2;
	//Mostramos nombre del jugador y la mano
	system("cls");
	cout << "  " << jugadores[pos].nombreJugador << " >>>  ";
	mostrarMano(jugadores, pos);
	//Revisamos que no tenga un numero mayor a 21
	if (calcularSuma(jugadores, pos) > 21) {
		cout << "\n\n\tTe pasate de 21, has perdido!!\n\n\t"; //Se le informa que se paso
		system("pause");
		jugadores[pos].activo = false; //Se convierte en false su estado activo
		turno++; //Se pasa al siguiente turno
	}
	else if (calcularSuma(jugadores, pos) == 21) { //En caso de que tenga 21 en mano

		turno = 4; //Finalizamos el bucle poniendo turno en 4 para proceder a ver quien gano

	}
	else {
		op2 = menuUsuario(jugadores, pos); //Mostramos menu de usuario
		system("cls");

		switch (op2)
		{
		case 1:
			cartaExtra(mazoCartas, jugadores, pos); //Metodo para pedir carta extra
			cout << "\n\n\tSe te ha dado la Carta Extra!\n\n\t"; //Se informa que se le dio la carta
			system("pause");
			break;

		case 2:
			cout << "\n\n\tTurno Terminado, pasando al siguiente jugador!!\n\n\t"; //Pasamos al siguiente jugador
			turno++;
			system("pause");
			break;
		}
	}

}