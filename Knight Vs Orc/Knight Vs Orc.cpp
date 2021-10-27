// Knight Vs Orc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Character.h"
#include "GeneralTypes.h"
#include "View.h";
#include "Game.h"

int main()
{
    //Defining the knight character and its weapon
    Character knight = Character::Character(GeneralTypes::Class::Knight, "Knight", 50, 20, 1);

    Character orc = Character::Character(GeneralTypes::Class::Orc, "Knight", 0, 80, 1);

    knight.takeDamage(20);
    knight.toString();
    knight.takeDamage(40);
    knight.toString();
    knight.heal(5);

    View v = View::View();


    knight.toString();
    knight.heal(30);
    knight.toString();

    Game g = Game(v);
    g.start();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage