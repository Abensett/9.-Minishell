<p align="center">

![shell](https://user-images.githubusercontent.com/85625233/206887409-d411cb06-36ff-4ed2-8c6d-8432bb4aeb5a.jpg)

</p>


<H1 align="center">
9-MINISHELL
</H1>

## Table of contents
* [Goal](#Goal)  
* [Requirements](#Requirements)
* [Ressources](#Ressources)

## GOAL

L’objectif de ce projet est de créer un shell minimaliste en C. 

## Requirements

- [x]  Afficher un prompt en l’attente d’une nouvelle commande.
- [x] Posséder un historique fonctionnel
- [x] Chercher et lancer le bon exécutable (en se basant sur la variable d’environnement
PATH, ou sur un chemin relatif ou absolu).
- [x] Une variable globale max
- [x] Ne pas interpréter de quotes (guillemets) non fermés, \ (le backslash) ou ; (le point-virgule).
- [x] Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.
- [x] Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $ (signe dollar)
- [x] Redirections :
  * \< doit rediriger l’entrée.
  * \> doit rediriger la sortie.
  * \<< doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
  * \>> doit rediriger la sortie en mode append
- [x]  Pipes | . La sortie de chaque commande de la pipeline
est connectée à l’entrée de la commande suivante grâce à un pipe
- [x] Gérer les variables d’environnement (un $ suivi d’une séquence de caractères)
qui doivent être substituées par leur contenu.
- [x] Gérer $? qui doit être substitué par le statut de sortie de la dernière pipeline
exécutée au premier plan.
- [x] Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent fonctionner comme dans bash.
- [x] En mode interactif :  
  * Ctrl + C => nouveau prompt.
  * Ctrl + D => quitte le shell.
  * Ctrl + \ => ne fait rien.
- [x] Builts-ins :  
   - [x] echo avec l'option - n
   - [x] cd no option
   - [x] pwd no option
   - [x] export no option
   - [x] env no option or argument
   - [x] exit no option

## Ressources
### RFC
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)

### Parsing
* [La ligne de commande c'est quoi ?](https://linux.goffinet.org/administration/le-shell/la-ligne-de-commande/)

### Execution
* [Explication processus](https://www.journaldunet.fr/web-tech/dictionnaire-du-webmastering/1445274-process-informatique-definition-detaillee-et-concrete/)
* [execve(), fork() et pipe()](https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe)
* [Unix Pipe](https://aurelienbrabant.fr/blog/an-introduction-to-unix-pipes)
* [Exit Status](https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/)
* [Wexitstatus](https://www.demo2s.com/c/c-wexitstatus-child-status.html)
 
### Heredoc
* [Bash Heredoc](https://linuxize.com/post/bash-heredoc/)

***
## 42 Project 101/100

