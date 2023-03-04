# Presentation Shell

## Introduction

Pour lancer le projet shell realise pour le TP SR:  
`make`  
`./shell`

## Fonctionalites    
Le shell peut executer 
- simple lignes de commandes (+ quit)  
- Redirection entree/sortie
- Commandes composees ( 2 ou plusieurs )
- Commandes arriere-plan 
 
Tout les fonctionalites vont etre montre par la suite des tests sur notre terminal

## Bugs detecte, a faire
- ligne vide -> seg fault
- cat < Makefile (une fois execute il exit)
- ls > a.txt (il affiche rien, il met `shell>exit` dans a.txt)
- ls < alksdjf ( il close le shell apres l'affichage d'erreur )
- pas de `cd ..`
- il execute pas `jobs`
- `cat &` avec ls il execute pas ls, mais il fait cat

