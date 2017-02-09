#pragma once

#include <SkBitmap.h>
#include <vector>
#include "Gene.h"

namespace GeneticImages
{
	class Population
	{
		private:
			const SkBitmap* targetBitmap;
			std::vector<Gene*> genes;
			int currentGeneration;

			std::vector<Gene*> GetTopGenes();
			std::vector<Gene*> Reproduce(const std::vector<Gene*> topGenes);
			void DeleteGenePool();
			
		public:
			 Population(const SkBitmap* targetBitmap);
			 ~Population();
			 void Init();
			 void EvaluateFitness();
			 void NaturalSelection();
	};
}