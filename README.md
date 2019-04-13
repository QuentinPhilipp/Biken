# Projet S6
> Written with [StackEdit](https://stackedit.io/).

## Dossier osmAPI :

Génération des routes et des nœuds grâce a l'API d'OSM et [overpassTurbo](http://overpass-turbo.eu/)
Création d'une base de donnée. Une fois la requête effectué chaque node et chaque way est stocké dans une base de donnée. Cela nous permettra (une fois implementé) de ne pas avoir besoin de faire de requête à Overpass mais uniquement de chercher dans la base de donnée. 

> Pour l'instant la création bug et il faut lancer plusieurs fois le
> programme pour avoir une base de donnée complète. Vous verrez quand
> elle est complète car il n'y aura plus d'erreur dans le terminal.

## Dossier routing

Début de l'interface graphique avec la recherche d’itinéraire par coordonnées GPS

## Dossier testMeteo
Test de l'API [openweathermap](https://openweathermap.org/api) et affichage des données météo en fonction d'une ville.

## WaysAndNodes.db
Fichier contenant la base de donnée. Se créé automatiquement au lancement du programme main.cpp du dossier osmAPI
