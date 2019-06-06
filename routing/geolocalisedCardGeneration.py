# -*- coding: utf-8 -*-
import os
import urllib
import json
import requests
import folium

def givemyIP():
	response = requests.get("http://ip.jsontest.com/")		#récupération IP --> avoir la position
	ip = response.json()["ip"]
	return ip


def givemyPosition():
	ip = givemyIP()
	access_key  = "e67caa15202f570e722a94906ed95535"
	urlString = "http://api.ipstack.com/"+ip+"?access_key="+access_key+"&format=1"
	contents = requests.get(urlString)
	latitude = contents.json()["latitude"]
	longitude = contents.json()["longitude"]						#récupération position grâce à API et adresse IP user
	return [latitude,longitude]

def MapCreation():
	c= folium.Map(location=givemyPosition(),zoom_start=9,zoom_control=False)
	c.save('../routing/Data/card.html')
	fichier = open("../routing/Data/card.html","a")				
	#inclusion de notre js 													#création de la carte centrée sur région concernée
	fichier.write("<script src='interactionGeolocalisedCard.js'></script>")
	fichier.close()


MapCreation()
