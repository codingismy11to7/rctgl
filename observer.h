// ----------------------------------------------------------
// Observer.h
// ----------------------------------------------------------

#pragma once
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Observer
{

public:

   Observer(double, double, int, int, int, int, int, int);
   ~Observer(void);

   double getLatitude();
   double getLongtitude();
   int getYear();
   int getMonth();
   int getDay();
   int getHour();
   int getMinute();
   int getSecond();

private:

   double latitude;
   double longitude;
   int year;
   int month;
   int day;
   int hour;
   int minute;
   int second;

};

inline double Observer::getLatitude() { return latitude; }
inline double Observer::getLongtitude() { return longitude; }
inline int Observer::getYear() { return year; }
inline int Observer::getMonth() { return month; }
inline int Observer::getDay() { return day; }
inline int Observer::getHour() { return hour; }
inline int Observer::getMinute() { return minute; }
inline int Observer::getSecond() { return second; }

#endif // __OBSERVER_H__