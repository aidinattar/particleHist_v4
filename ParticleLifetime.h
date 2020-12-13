#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "AnalysisSteering.h"
#include "../util/include/ActiveObserver.h"
#include <string>
#include <vector>

class Event;
class LifetimeFit;
class TH1F;

class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event>  {

 public:

  ParticleLifetime( const AnalysisInfo* info );
  virtual ~ParticleLifetime();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void   endJob();
  // function to be called for each event
  virtual void update( const Event& ev );


 private:

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleLifetime           ( const ParticleLifetime& x );
  ParticleLifetime& operator=( const ParticleLifetime& x );

  struct Particle {
    std::string   name; // element name
    LifetimeFit* pMean; // statistic object
    TH1F*        hMean; // graph
  };

  // set of masses for different particles
  std::vector<Particle*> pList;

  void pCreate( const std::string& name,
                float      min, float      max, 
                double timeMin, double timeMax );

};

#endif

