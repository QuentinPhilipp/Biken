# Projet S6
> Written with [StackEdit](https://stackedit.io/).

## Pré-requis pour faire fonctionner le programme sur Qt:

Le logiciel a été réalisé sur la version 5.11 de Qt. Il faut avoir une version au moins aussi récente pour pouvoir utiliser toutes les fonctionnalités du programme.

### Windows
    Avoir le shell bash sur Windows.
    Installer Qt avec le module QtWebEngine (ou l'ajouter si Qt est déja installé).
    Sur Visual Studio, installer tous les modules comme expliqué sur ce poste de Chris Kawa : [https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12](https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12)
    Sur Qt, vérifier tout ce qui est évoqué sur le lien précédent.
    Installer folium.
    Installer Nodejs (version 10.15 minimum). [https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0](https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0)
    
### Linux
    Installer folium.
    Installer Nodejs (version 10.15 minimum). [https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0](https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0)




## API Météo :
On utilise l'API de openweathermap.org

Voici la doc : [https://openweathermap.org/forecast5](https://openweathermap.org/forecast5)


 - Le fichier est en python pour l'instant, c’était juste pour les tests
   mais on le changera en cpp. Il faut juste trouver l'équivalent de la
   fonction **request()**


Il faut la clé de l'API, elle est dans le programme.
Pour l'appel il faut renseigner la ville, le pays et la clé.

La fonction ***requests.get(....).json()*** nous renvoie un fichier json que l'on peux facilement traiter. Regardez le retour de la fonction si vous voulez voir l’intégralité du fichier