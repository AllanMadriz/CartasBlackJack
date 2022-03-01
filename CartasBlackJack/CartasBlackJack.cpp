#include "funcionesProyecto.h"

int main()
{
	//Creamos las variables a utilizar
	int op2, turno, empates;
	string op;
	vector<Jugador> jugadores(0); //Creamos los vectores a utilizar
	vector<Cartas> mazoCartas(0);
	//Creamos un bucle en el cual se estara ejecutando el juego
	do {
		//Se crea otro bucle que se estara realizando hasta que se digite un numero correcto
		do {
			system("cls");
			cout << "\n\n\t1 - Nuevo Juego"
				<< "\n\t2 - Salir del Programa\n\n\t";
			cin >> op;
		} while (!revisaSiEsNumero(op));
		//Turno se iguala a 1
		turno = 1;
		//Se inicia el switch
		switch (stoi(op))
		{
		case 1:
			//llamamos el metodo limpiar vectores
			limpiarVectores(mazoCartas, jugadores);

			do {
				switch (turno) //Segun el turno se entrara en los cases
				{
				case 1:
					//Se llama al metodo funcionCases
					funcionCases(turno, jugadores, mazoCartas, 0);
					break;

				case 2:

					funcionCases(turno, jugadores, mazoCartas, 1);
					break;

				case 3:

					funcionCases(turno, jugadores, mazoCartas, 2);
					break;
				}

			} while (turno < 4);
			//Al cerrar el bucle se declarara un ganador
			declararGanador(jugadores);

			break;

		case 2:
			system("cls");
			cout << "\n\n\tHasta Luego!!\n\n"; //Se imprime el mensaje de despedida
			break;
		}

	} while (stoi(op) != 2);

	return 0;
}


