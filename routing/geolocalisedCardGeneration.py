# -*- coding: utf-8 -*-
import os
import urllib
import json
import requests
import folium

def givemyIP():
	response = requests.get("http://ip.jsontest.com/")
	ip = response.json()["ip"]
	return ip


def givemyPosition():
	ip = givemyIP()
	access_key  = "e67caa15202f570e722a94906ed95535"
	urlString = "http://api.ipstack.com/"+ip+"?access_key="+access_key+"&format=1"
	contents = requests.get(urlString)
	latitude = contents.json()["latitude"]
	longitude = contents.json()["longitude"]
	return [latitude,longitude]

def MapCreation():
	c= folium.Map(location=givemyPosition(),zoom_start=9) 
	folium.Marker(givemyPosition()).add_to(c)
	c.save('../routing/Data/card.html')

MapCreation()
