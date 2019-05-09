#ifndef WEATHER_H
#define WEATHER_H

#include <vector>

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


    //Accessing to forecast data
    double getWindDirection(){return windDirection;}

    double getWindSpeed(){return windSpeed;}

    double getTemp(){return temperature;}

    QString getDescription(){return weatherDescription;}
    void setDescription(QString des){weatherDescription = des;}

    bool getActive(){return active;}
    void swapActive(){active ? active = 0 : active = 1;}

    QString getIcon(){return iconCode;}
};

class Weather: public QObject
{
    Q_OBJECT

private:
    std::vector<Forecast> forecasts;
    double lat,lon;
    QString error;

    void translate();

public:
    explicit Weather(QObject *parent = nullptr);

signals:

public slots:
    void createForecast(double lat, double lon);
    void changeForecast(int id);
    int findActive();

    double getActiveDirection();
    QString getActiveWindSpeed();
    double getActiveTemp();
    QString getActiveWindStrength();
    QString getActiveDescription();
    QString getActiveIcon();
    QString getError(){return error;}

};

#endif // WEATHER_H
