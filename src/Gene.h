#pragma once

#include <string>
#include <SkBitmap.h>

namespace GeneticImages
{
	class Gene
	{
		protected:
			SkBitmap bitmap;
			unsigned int fitness;

		public:
			Gene(const unsigned int width, const unsigned int height);
			virtual ~Gene();
			virtual void InitRandomly() = 0;
			virtual Gene* Crossover(Gene* mate) = 0;
			virtual void Draw() = 0;
			void EvaluateFitness(const SkBitmap& targetBitmap);
			void Save(const std::string name) const;
			bool Load(const std::string name, SkColorType colorType = kN32_SkColorType, bool requireUnpremul = false);
			int GetFitness() const;
			bool operator < (const Gene& str) const;
			bool operator > (const Gene& str) const;
	};
}