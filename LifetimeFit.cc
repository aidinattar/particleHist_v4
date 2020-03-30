// Created by Aidin Attar. 2019

// LifetimeFit.cc

#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"

#include <cmath>

LifetimeFit::LifetimeFit( float min, float max ):
 // initializations
  massMin( min ),
  massMax( max ),
  nEvt( 0 ){
}


LifetimeFit::~LifetimeFit() {
}


// add data from a new event
bool LifetimeFit::add( const Event& ev ) {
  // get invariant mass
  static ParticleReco* pr = ParticleReco::instance();
  double Mass = pr->invariantMass();

  // check for mass being in range
  if ( Mass < massMin || Mass > massMax ) 
    return false;

  // update number of events
  ++nEvt;

  return true;

}


void LifetimeFit::compute() {
}


// return number of selected events
int LifetimeFit::nEvents(){
  return nEvt;
}