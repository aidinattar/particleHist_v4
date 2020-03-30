#include "ParticleLifetime.h"

#include "Event.h"
#include "LifetimeFit.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleReco.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include <iostream>


double timeMinK0 =   10.0;
double timeMaxK0 =  500.0;
double timeMinL0 =   10.0;
double timeMaxL0 = 1000.0;


// arbitrary bin number
int nBin = 128;

// concrete factory to create an ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
  // create an ParticleLifetime when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new ParticleLifetime( info );
  }
};
// create a global ParticleLifetimeFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleLifetimeFactory will be available with name "plot".
static ParticleLifetimeFactory er;

ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


ParticleLifetime::~ParticleLifetime() {
}


// function to be called at execution start
void ParticleLifetime::beginJob() {

  // create mass distributions for different particles
  pList.reserve( 10 );
  pCreate( "K0" , timeMinK0, timeMaxK0 );
  pCreate( "L0" , timeMinL0, timeMaxL0 );

  return;

}


// function to be called at execution end
void ParticleLifetime::endJob() {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "RECREATE" );

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    // get mass informations
    LifetimeFit* pMean = pList[i]->pMean;
    TH1F*        hMean = pList[i]->hMean;
    // compute results
    pMean->compute();

    // print number of events
//    std::cout << pMean->nEvents() << std::endl;
    // save distribution
    hMean->Write();
  }

  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;

}


// function to be called for each event
void ParticleLifetime::update( const Event& ev ) {
  // loop over mass distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;

  // get invariant mass
  static ParticleReco*   pr = ParticleReco::instance();
  double               Mass = pr->invariantMass();

  for ( i = 0; i < n; ++i ){
    // get mass informations
    LifetimeFit* pMean = pList[i]->pMean;
    TH1F*        hMean = pList[i]->hMean;

    if( pMean->add( ev ) == true )
      // set center values in the graph
      // by using SetBinContent, bin count starts from 1
      hMean->Fill( Mass );
  }
  return;
}


void ParticleLifetime::pCreate( const std::string& name,
                                double timeMin, double timeMax ){

  // create mass distribution for events with mass in given range

  // create name for TH1F object
  const char* hName = ( "time" + name ).c_str();
  std::cout << "titolo: " << hName << std::endl;

  // create TH1F and statistic objects and store their pointers
  Particle* pm = new Particle;
  pm-> name = name;
  pm->pMean = new LifetimeFit( timeMin, timeMax );
  pm->hMean = new TH1F( hName, hName, nBin, timeMin, timeMax );
  pList.push_back( pm );

  return;

}