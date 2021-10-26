// Knight Vs Orc.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Character.h"
#include "GeneralTypes.h"

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
    knight.toString();
    knight.heal(30);
    knight.toString();
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
