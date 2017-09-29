// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the lambo class.
//

#include "lambo.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"


#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

lambo::lambo() {}

lambo::~lambo() {}



#ifndef LWH_AIAnalysisFactory_H
#ifndef LWH 
#define LWH ThePEGLWH
#endif
#include "ThePEG/Analysis/LWH/AnalysisFactory.h"
#endif

void lambo::analyze(tEventPtr event, long ieve, int loop, int state) {
  AnalysisHandler::analyze(event, ieve, loop, state);
  // Rotate to CMS, extract final state particles and call analyze(particles).
  N_++;
  dentro_->Fill(); 
}

LorentzRotation lambo::transform(tcEventPtr event) const {
  return LorentzRotation();
  // Return the Rotation to the frame in which you want to perform the analysis.
}

void lambo::analyze(const tPVector & particles, double weight) {
  AnalysisHandler::analyze(particles);
  // Calls analyze() for each particle.
}

void lambo::analyze(tPPtr, double weight) {}

void lambo::dofinish() {
  AnalysisHandler::dofinish();
  // *** ATTENTION *** Normalize and post-process histograms here.
  dentro_ ->GetCurrentFile();
  dentro_ ->Write();
  myfile_ ->Close();
}

void lambo::doinitrun() {
  AnalysisHandler::doinitrun();
  // *** ATTENTION *** histogramFactory().registerClient(this); // Initialize histograms.
  // *** ATTENTION *** histogramFactory().mkdirs("/SomeDir"); // Put histograms in specal directory.
  std::cout <<"creating a TTree to be saved in output.root" << std::endl; 
  myfile_ = new TFile("output.root","RECREATE");
  dentro_ = new TTree("dentro","dentro");
  dentro_ ->Branch("N", &N_, "N/I"); 

  N_ = 0;
}


IBPtr lambo::clone() const {
  return new_ptr(*this);
}

IBPtr lambo::fullclone() const {
  return new_ptr(*this);
}


// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void lambo::persistentOutput(PersistentOStream & os) const {
  // *** ATTENTION *** os << ; // Add all member variable which should be written persistently here.
}

void lambo::persistentInput(PersistentIStream & is, int) {
  // *** ATTENTION *** is >> ; // Add all member variable which should be read persistently here.
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<lambo,AnalysisHandler>
  describeThePEGlambo("ThePEG::lambo", "lambo.so");

void lambo::Init() {

  static ClassDocumentation<lambo> documentation
    ("There is no documentation for the lambo class");

}

