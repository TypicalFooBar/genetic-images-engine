#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "src/Engine.h"

int main(int argc, char** argv)
{
	// Seed the random number generator
	srand(time(NULL));

    // Create the engine output directory
    boost::filesystem::path engineOutputDirectory("engine-output");
    boost::filesystem::create_directory(engineOutputDirectory);

	GeneticImages::Engine engine("sonic32x32.png");
	engine.Run();

	return(0);
}