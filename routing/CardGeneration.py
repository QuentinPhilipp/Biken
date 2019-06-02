# -*- coding: utf-8 -*-
import folium
import os
import sys


def MapCreation(nodes):
	c= folium.Map(location=[48.3677820, -4.7591771])
	deparr=[]
	deparr.append(nodes[0])
	deparr.append(nodes[len(nodes)-1])					#on récupère le premier et le dernier noeud pour y placer des marqueurs
	for each in deparr :
		folium.Marker(each,draggable = True).add_to(c)
	#add lines
	#folium.PolyLine(nodes, color="red", weight=2.5, opacity=1).add_to(c)
	folium.PolyLine(nodes).add_to(c)
	c.save('../routing/Data/card.html')
	#ouverture du fichier créé et inclusion de notre js
	fichier = open("../routing/Data/card.html","a")
	fichier.write("<script src='interaction.js'></script>")
	fichier.close()


def toHaveNodes():
	path=os.getcwd()
	with open("../routing/Data/coordinates.txt") as file:
		lines = [line.strip('\n') for line in file.readlines()]
		#pointsep contient chq lon et lap séparées
		pointsep=[float(i) for i in lines]
	#on remplit maintenant la liste points
	points=[]
	global a
	global b
	a=0
	b=1
	for i in range(int(len(pointsep)/2)):
		points.append([pointsep[a],pointsep[b]])
		a=a+2
		b=b+2
	return points

nodes = toHaveNodes()
MapCreation(nodes)
