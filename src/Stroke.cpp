#include "Stroke.h"

namespace GeneticImages
{
	void Stroke::InitRandomly(const int width, const int height)
	{
		this->points.push_back(Stroke::RandomPoint(width, height));
		this->points.push_back(Stroke::RandomPoint(width, height));
		this->paint = Stroke::RandomPaint();
	}

	SkPoint Stroke::RandomPoint(const int width, const int height)
	{
		return SkPoint::Make(
			rand() % width,
			rand() % height
		);
	}

	std::vector<SkPoint> Stroke::RandomPoints(int width, int height)
	{
		std::vector<SkPoint> points;
		points.push_back(Stroke::RandomPoint(width, height));
		points.push_back(Stroke::RandomPoint(width, height));

		return points;
	}

	SkPaint Stroke::RandomPaint()
	{
		SkPaint paint;
		paint.setStrokeWidth(rand() % 5 + 1);	// Range: 1-5
		paint.setAntiAlias(true);
		paint.setColor(
			SkColorSetARGB(
				rand() % 256,
				rand() % 256,
				rand() % 256,
				rand() % 256
			)
		);

		return paint;
	}
}