# -*- coding: utf-8 -*-
import folium
import os
import sys


def MapCreation(nodes):
	c= folium.Map(location=[48.3677820, -4.7591771])  
	for each in nodes:
		folium.Marker(each).add_to(c)
	#add lines
	folium.PolyLine(nodes, color="red", weight=2.5, opacity=1).add_to(c)
	folium.PolyLine(nodes).add_to(c)
	c.save('../routing/Data/card.html')

def toHaveNodes(*args,**kwargs):
	points = []
	reception = args[0]
	reception.remove(reception[0]) # on ne se retrouve qu'avec les coord, mais ce sont des string
	for each in reception :
		a=each.find(",")
		lon = float(each[1:a])
		b=a+1
		lat = float(each[b:len(each)-1])
		points.append([lon,lat]) #vérifier tous les points ont 7 chiffres après la virgule
	return points

nodes = toHaveNodes(sys.argv)
MapCreation(nodes)

