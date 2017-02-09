#pragma once

#include <vector>
#include <SkPaint.h>
#include <SkPoint.h>

namespace GeneticImages
{
	class Stroke
	{
		public:
			std::vector<SkPoint> points;
			SkPaint paint;
			
			void InitRandomly(int width, int height);
			static SkPoint RandomPoint(int width, int height);
			static std::vector<SkPoint> RandomPoints(int width, int height);
			static SkPaint RandomPaint();
	};
}