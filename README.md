# Start-up of Biken

Check the demo video on youtube : [Biken Demo](https://www.youtube.com/watch?v=seBOBeAjZv8)

## Prerequisites to run the program on Qt:

This software was developed on version 5.11 of Qt. You must have at least as recent a version to be able to use all the features of the program.

## Warning Notice
The calculations performed in Biken are quite complex and require a certain amount of power. The speed of the search will therefore depend a lot on your configuration.
In addition, it is strongly recommended to install the project on SSD if possible, this reduces the time of queries in the database.

### Windows
    Install bash on Windows.
    Install Qt with QtWebEngine.
    On Visual Studio, install all of the moduls like in this post of Chris Kawa : [https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12](https://forum.qt.io/topic/78962/how-to-use-qt-with-visual-studio-2017/12)
    On Qt, check everything that is mentioned on the previous link.
    Install folium.
    Install Nodejs (version 10.15 minimum). https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0
    
### Linux
    Install Qt with QtWebEngine.
    Install folium.
    Install Nodejs (version 10.15 minimum). https://medium.com/@shivraj.jadhav82/nodejs-and-npm-setup-on-linux-mint-19-696023d50247?fbclid=IwAR2Vb6NeiFSxeEvuTXlk28dFL3IFhPn9N6Avev5VcFqSBT-EOny65V1oW_0

### Building of the database 

In the folder "routing" , execute $python generateTiles 29 56 35 .... with in arguments, the code of the desired departments. (Currently only for french departements). Or by starting the program for the first time, the program	will download department 29, if it doesn't exist.

29,56 and 35 correspond to departments from western France. It is necessary to search in the downloaded departments 

It can happen that the OSM server is not very responsive and returns errors. The script will then continue to request the information until the entire database is downloaded. This can take up to 1 to 2 minutes per department.

## Uses
At launch, the application may take up to ten seconds to display the main menu and you will be blocked on the home screen.



> **Developed by  :** 
> Beuzet Charles,
> Lepoittevin Titouan,
> Mérel Léo,
> Mesnage Guillaume,
> Philipp Quentin

> **Biken**, Semester 6 Project, June 2019, ENIB
