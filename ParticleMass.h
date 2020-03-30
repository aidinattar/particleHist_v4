#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include "../util/include/ActiveObserver.h"
#include <string>
#include <vector>

class Event;
class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering,
                    public ActiveObserver<Event>  {

 public:

  ParticleMass( const AnalysisInfo* info );
  virtual ~ParticleMass();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void   endJob();
  // function to be called for each event
  virtual void update( const Event& ev );


 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleMass           ( const ParticleMass& x );
  ParticleMass& operator=( const ParticleMass& x );

  struct Particle {
    std::string  name;  // element name
    MassMean*   pMean; // statistic object
    TH1F*       hMean; // graph
  };

  // set of masses for different particles
  std::vector<Particle*> pList;

  void pCreate( const std::string& name, float min, float max );

};

#endif

