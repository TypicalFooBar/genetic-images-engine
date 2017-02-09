#pragma once

#include <vector>
#include "Stroke.h"
#include "Gene.h"

namespace GeneticImages
{
	class DrawLineGene : public Gene
	{
		private:
			std::vector<Stroke> strokes;

		public:
			DrawLineGene(const int width, const int height);
			~DrawLineGene();
			void Init(const std::vector<Stroke>& strokes);
			void InitRandomly() override;
			void Draw() override;
			Gene* Crossover(Gene* mate) override;
			const std::vector<Stroke>& GetStrokes() const;

	};
}