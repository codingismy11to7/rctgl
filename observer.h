// ----------------------------------------------------------
// Observer.h
// ----------------------------------------------------------

#pragma once
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

struct Observer
{
   Observer(double, double, int, int, int, int, int, int);

   double latitude;
   double longitude;
   int year;
   int month;
   int day;
   int hour;
   int minute;
   int second;
};


#endif // __OBSERVER_H__