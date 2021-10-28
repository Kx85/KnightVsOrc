// KnightVsOrc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Character.h"
#include "GeneralTypes.h"
#include "View.h"
#include "Game.h"
#include "TitleScreen.h"

#include<conio.h>
#include <Windows.h>
using namespace std;

int main()
{
    //Defining the knight character and its weapon
    Character knight = Character::Character(GeneralTypes::Class::Knight, "Knight", 50, 20, 1);
    Character orc = Character::Character(GeneralTypes::Class::Orc, "Knight", 0, 80, 1);

    View v = View::View();
    Game g = Game(v);

    g.update();
    g.start();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage