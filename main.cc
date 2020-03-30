#include <vector>

#include "EventSource.h"
#include "SourceFactory.h"
#include "AnalysisInfo.h"
#include "AnalysisSteering.h"
#include "AnalysisFactory.h"

#include <iostream>


using namespace std;

int main( int argc, char* argv[] ) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  vector<AnalysisSteering*> aList = AnalysisFactory::create( info );

  // variables to loop over analyzers
  int l = aList.size();
  int i;

  // initialize all analyzers
  for ( i = 0; i < l; ++ i ) aList[i]->beginJob();

  // loop over events
  es->run();

  // finalize all analyzers
  for ( i = 0; i < l; ++ i ) aList[i]->endJob();

  return 0;

}

