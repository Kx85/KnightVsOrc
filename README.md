
# Personal project for a job application

## Global use: 

<pre>
Arrow keys: Menu navigation  
Enter     : Selection/Validation  
Backspace : Return  
</pre>

## Title Screen:

Press Start => Allows to enter the fight customisation  
  - Enter the name (regex is `[a-zA-Z][a-zA-Z]*`). If the name exists, the associated character will be loaded, else the creation process continues  
  - Enter the Class name (choices are given). Using "Orc" or "Knight" will load the default Class spec. Using "Custom" will allow the hand definition of the stats  
  - Handwritten stats are : Hp, Shield, Weapon used (no restriction) and bind an ability  

When a fight ends, you will be prompted to go back to the main menu or to start a new fight with the same fighters  

Demo => Starts the basic demo with:  
  - Knight using a sword (5 damage) with 20/50 hp/shield and with a charge (60% accuracy) ability  
  - Orc using an axe (8 damage) with 80 hp and with a stun (20% accuracy) ability  
	
When a demo ends, you will be prompted to go back to the main menu or to start a new demo  

Settings => Allow to enter the Weapon, Abilities and Characters customisation:  
  - Abilities: Possibility to create a new Ability or delete an existing one  
  - Weapons: Possibility to create a new Weapon or delete an existing one  
  - Character: Possibility to create a new Character or delete an existing one  

When deleting an element, no prompt will be given. Game will not be broken as you can't delete the following existing objects.  
When creating an element, you will be given some information on whether the element already exists or not  
On character creation, using a class different than "Custom" will fetch the class specifications as specified below
  
Note this is solo work and some bugs could still be present.  

## Weapons

There are 2 base weapons:  
  
Sword:  
  - Name = Sword  
  - Type is Sword  
  - Damage = 5  
  - Speed (hidden value) = 60 for swords  
  
Axe:  
  - Name = Axe
  - Type is Axe  
  - Damage = 8  
  - Speed (hidden value) = 40 for swords  

## Abilities

There are 2 base abilities:  
  
Stun:  
  - Ability damage = 0  
  - Damage Modifier = 0  
  - Modifier type = None  
  - Status modifier = Stunned  
  - Effect duration = 1  
  - Cooldown = 5  
  - Accuracy = 20%  
  
Charge:  
  - Ability damage = 0  
  - Damage Modifier = 2  
  - Modifier type = Mult  
  - Status modifier = None  
  - Effect duration = 0  
  - Cooldown = 3  
  - Accuracy = 60%  

## Classes

There are 2 base classes:  

Knight:  
  - Hp = 20  
  - Shield = 50  
  - Weapon = Sword  
  - Ability = Charge  

Orc:  
  - Hp = 80  
  - Shield = 0  
  - Weapon = Axe  
  - Ability = Stun  
