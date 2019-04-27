#ifndef WEATHER_H
#define WEATHER_H

#include <vector>
#include <tuple>

#include <QObject>

class Forecast
{
private:
    double windDirection;
    double windSpeed;
    double temperature;
    QString hour;
    QString date;
    QString weatherDescription;
    bool active;
    QString iconCode;

public:
    Forecast(double wDir,double wS,double temp,QString dt,QString wDes,bool active,QString code);

    void swapActive();
};

class Weather
{
private:
    std::vector<Forecast> forecasts;
    double lat,lon;

public:
    Weather();

    void createForecast(double lat, double lon);
};

#endif // WEATHER_H
