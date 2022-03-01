#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Cartas
{
	string numero;
	char palo;
};

struct Jugador
{

	string nombreJugador;
	bool activo;
	vector<Cartas> manoJugador;

};