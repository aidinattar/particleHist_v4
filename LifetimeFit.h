// Created by Aidin Attar. 2019

// LifetimeFit.h

#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;

class LifetimeFit {

 public:

  LifetimeFit( float min, float max ); // mass range
  ~LifetimeFit();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int    nEvents(); // return number of accepted events

 private:

  double massMin; // min mass
  double massMax; // max mass

  int nEvt; // number of accepted events

};

#endif