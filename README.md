# WaveNetVA

Feedforward WaveNet for black-box virtual analog modeling. This code is related to our paper submitted to [SMC 2019](http://smc2019.uma.es/): https://link-to-pre.print

A real-time implementation of the model built using JUCE. The code can be built as a standalone audio application or as an VST3, AU or AAX etc. plugin.

Audio samples are available on the [demo page](http://research.spa.aalto.fi/publications/papers/smc19-black-box/).

## Getting Started

### Installing

* Clone the repo.
* Download and install [JUCE](https://juce.com/)
  * The software has been tested with Juce version 5.4.2
* Download [Eigen](http://eigen.tuxfamily.org)
  * Extract Eigen somewhere, e.g. your home directory.
  * The software has been tested with Eigen version 3.3.7
* Open WaveNetVA.jucer file with Projucer
  * Add the Eigen folder to "Header Search Paths" in Exporters -> Debug/Release
  * Open and build project in XCode or Visual Studio.

### Loading trained models

The trained models are stored as json files. The pre-trained models of the Ibanez Tube Screamer, Boss DS-1 and Electro-Harmonix Big Muff Pi described in the paper are included in the [Models](Models) directory.

## License
This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.

