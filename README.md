# Projet S6
> Written with [StackEdit](https://stackedit.io/).

## API Météo :
On utilise l'API de openweathermap.org

Voici la doc : [https://openweathermap.org/forecast5](https://openweathermap.org/forecast5)


 - Le fichier est en python pour l'instant, c’était juste pour les tests
   mais on le changera en cpp. Il faut juste trouver l'équivalent de la
   fonction **request()**


Il faut la clé de l'API, elle est dans le programme.
Pour l'appel il faut renseigner la ville, le pays et la clé.

La fonction ***requests.get(....).json()*** nous renvoie un fichier json que l'on peux facilement traiter. Regardez le retour de la fonction si vous voulez voir l’intégralité du fichier