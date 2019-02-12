/*
  ==============================================================================

    WaveNetLoader.h
    Created: 3 Feb 2019 8:55:31pm
    Author:  Eero-Pekka Damskägg

  ==============================================================================
*/

#pragma once
#include <string>

#include "../JuceLibraryCode/JuceHeader.h"

#include "WaveNet.h"

class WaveNetLoader
{
public:
    WaveNetLoader(File configFile);
    void loadJson();
    int numChannels;
    int inputChannels;
    int outputChannels;
    int filterWidth;
    std::vector<int> dilations;
    std::string activation;
    void loadVariables(WaveNet &model);
    
private:
    std::vector<int> readDilations();
    File jsonFile;
    var config;
};
