import requests
import json

#doc :
#https://openweathermap.org/forecast5

key = 'ac69ab213a56edaffaac9baa47770444'

city = 'Brest'
country = 'FR'

requestURL = 'http://api.openweathermap.org/data/2.5/forecast?q='+city+','+country+'&units=metric'+'&APPID='+key

meteo = requests.get(requestURL).json()



#print meteo["city"]  #print info of the city              {u'country': u'FR', u'population': 144899, u'id': 3030300, u'coord': {u'lat': 48.3905, u'lon': -4.4861}, u'name': u'Brest'}

#print meteo["list"]  #print list of the data


for i in range(len(meteo)):
    #3h between each forecast
    print "\n\n"
    print meteo["list"][i]["dt_txt"],' : '
    print ' | Meteo : ', meteo["list"][i]["weather"][0]["description"]
    print ' | Temperature : ', meteo["list"][i]["main"]["temp"]
    print ' | Vitesse du vent : ', meteo["list"][i]["wind"]["speed"]
    print ' | Direction du vent : ', meteo["list"][i]["wind"]["deg"]
