
# Mise en route de Biken

## Pré-requis pour faire fonctionner le programme sur Qt:

Le logiciel a été réalisé sur la version 5.11 de Qt. Il faut avoir une version au moins aussi récente pour pouvoir utiliser toutes les fonctionnalités du programme.

## Avertissement
Les calculs effectués dans Biken sont assez complexes et nécessitent une certaines puissance. La rapidité de la recherche dépendra donc beaucoup de votre configuration.
De plus il est fortement recommandé d'installer le projet sur SSD si possible, cela diminue le temps des requêtes dans la base de donnée.

### Windows
    Avoir le shell bash sur Windows.
    Installer Qt avec le module QtWebEngine (ou l'ajouter si Qt est déja installé).
    Sur Visual Studio, installer tous les modules comme expliqué sur ce poste de Chris Kawa : [https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12](https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12)
    Sur Qt, vérifier tout ce qui est évoqué sur le lien précédent.
    Installer folium.
    Installer Nodejs (version 10.15 minimum). [https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0](https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0)
    
### Linux
    Installer Qt avec le module QtWebEngine (ou l'ajouter si Qt est déja installé).
    Installer folium.
    Installer Nodejs (version 10.15 minimum). [https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0](https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0)

### Création de la base de donnée 
Vous pouvez télécharger la base de donnée de la Bretagne [ici](https://we.tl/t-n98GX0dBoO)
Il faut placer la BDD téléchargée à cet emplacement  : /routing/Data

Ou sinon dans le dossier routing, exécutez $python generateTiles 29 56 .... avec en arguments, les numéros des départements souhaités.

Ou en lançant le programme pour la première fois, le programme 
	va télécharger le département 29, s'il n'existe pas.

Dans les deux derniers cas, la BDD se créée au bon endroit directement, ce n'est pas nécessaire de la déplacer.
	
Il peut arriver que le serveur d'OSM ne soit pas très réactif et renvoie des erreurs. Le script va alors continuer de demander les informations jusqu'à ce que toute la base de donnée soit téléchargée. Cela peut prendre jusqu'à 1 à 2 minutes par départements.


## Utilisation
Au lancement, l'application peut mettre jusqu'à une dizaine de secondes avant d'afficher le menu principal et vous serez bloqué sur l'écran d'accueil.

Pour l'instant le logiciel est configuré pour charger les données de la Bretagne, les objets sont donc chargées à cet endroit. Pour changer l'endroit de la France qui est chargé il faut modifier le nom de la ville au centre de ce que vous souhaitez charger dans le fichier main.cpp

      QString  defaultAdress  =  "NomDUneVille";  //load  the  database  around  the  adress
      QList<double>  defaultCoord  =  myAdress->toCoordinates(defaultAdress);
      db->requestRoads(defaultCoord[0],defaultCoord[1],RayonACharger);  //radius  in  km  Load  the  data  and  convert  from  database  to  object

Exemple : Pour charger la Bretagne nous avons mis une ville au centre de la Bretagne avec un rayon de 150km

Il faut aussi que la région que vous souhaitez charger ai précédemment été ajouté dans la base de donnée. C'est faisable depuis l'onglet "Départements" ou il suffit de cocher le/les département(s) choisi(s), d'appuyer sur "Valider" et d'attendre le temps de chargement de la base de donnée ( Pas de retour utilisateur )





> **Développé par  :** 
> Beuzet Charles,
> Lepoittevin Titouan,
> Mérel Léo,
> Mesnage Guillaume,
> Philipp Quentin

> **Biken**, Projet S6, Juin 2019, ENIB

