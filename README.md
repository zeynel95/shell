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

## Tests effectuees
- test_redi -> tests redirection
- test_simple -> test de commandes simples
- test_pipe -> test pour commandes composees
- test_bg -> test pour `&`

## Launch tests
./sdriver.pl -t tests/test01.txt -s ./shell
