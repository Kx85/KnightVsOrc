// KnightVsOrc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Character.h"
#include "GeneralTypes.h"
#include "View.h";
#include "Game.h"

#include<conio.h>
#include <Windows.h>
using namespace std;

int main()
{
    //Defining the knight character and its weapon
    Character knight = Character::Character(GeneralTypes::Class::Knight, "Knight", 50, 20, 1);

    Character orc = Character::Character(GeneralTypes::Class::Orc, "Knight", 0, 80, 1);

    char key_press;
    int ascii_value;
    cout << "\n\t\t\tPress Any Key To Check  Its ASCI Value\n\n\t\t\tPress ESC to EXIT\n\n\n";
    while (1)
    {
        key_press = _getch(); // a remplacer par cin >> c
        ascii_value = key_press;
        if (ascii_value == 27) // For ESC
            break;
        cout << "\t\t\tKEY Pressed-> \" " << key_press << " \" Ascii Value =  " << ascii_value << "VK_UP = " << VK_UP << "\n\n";
    }

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