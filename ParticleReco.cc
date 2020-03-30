#include "ParticleReco.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <math.h>

using namespace std;

Constants cost;


ParticleReco::ParticleReco() {
}


ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  // retrieve particles in the event
  typedef const Event::Particle* part_ptr;

  // variables to loop over particles
  int i;

  // positive / negative track counters
  int p = 0,
      n = 0;

  // variables for momentum sums
  float sumPx = 0,
        sumPy = 0,
        sumPz = 0;

  // variables for energy sums, for K0 and Lambda0
  float sumEnK0 = 0,
        sumEnL0 = 0;

  // loop over particles - momenta
  for ( i = 0; i < ev.numParticles(); ++i ) {
    // get particle pointer
    part_ptr par = new Event::Particle;
    par = ev.particle( i );

    // update momentum sums
    sumPx += par->Px;
    sumPy += par->Py;
    sumPz += par->Pz;

    // update energy sums, for K0 and Lambda0 hypotheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively
    // update positive/negative track counters
    sumEnK0 += Utilities::energy ( par->Px, par->Py, par->Pz,
                        cost.massPion );

    if ( par->q == 1 ){
      sumEnL0 +=  Utilities::energy ( par->Px, par->Py, par->Pz,
                          cost.massProton );
      ++p;
      }
    else {
      sumEnL0 += Utilities::energy ( par->Px, par->Py, par->Pz,
                          cost.massPion );
      ++n;
      }

  }

  // check for exactly one positive and one negative track
  if ( n == p ){
    // invariant masses for different decay product mass hypotheses
    double K0exp = Utilities::restMass ( sumPx, sumPy, sumPz,
                              sumEnK0 );
    double L0exp = Utilities::restMass ( sumPx, sumPy, sumPz,
                              sumEnL0 );

   // compare invariant masses with known values and set final values
   // ( type, energy and mass )
    if ( fabs( K0exp - cost.massK0      ) <
         fabs( L0exp - cost.massLambda0 ) ){
            mass   =   K0exp;
            energy = sumEnK0;
            type   =      K0;
    }

    else{
            mass   =   L0exp;
            energy = sumEnL0;
            type   = Lambda0;
    }
  }

  return;

}


float ParticleReco::totalEnergy() {
  // check for new event and return result
  check();
  return energy;
}


float ParticleReco::invariantMass() {
  // check for new event and return result
  check();
  return mass;
}


ParticleReco::ParticleType ParticleReco::particleType() {
  // check for new event and return result
  check();
  return type;
}

