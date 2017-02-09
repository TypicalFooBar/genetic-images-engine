#include <SkCanvas.h>

#include "DrawLineGene.h"

namespace GeneticImages
{
	DrawLineGene::DrawLineGene(const int width, const int height)
		: Gene(width, height)
	{}

	DrawLineGene::~DrawLineGene()
	{}

	void DrawLineGene::Init(const std::vector<Stroke>& strokes)
	{
		this->strokes = strokes;
	}

	void DrawLineGene::InitRandomly()
	{
		int numberOfStrokes = 250; // TODO: Make this a variable

		for (int i = 0; i < numberOfStrokes; ++i)
		{
			Stroke stroke;
			stroke.InitRandomly(this->bitmap.width(), this->bitmap.height());
			
			this->strokes.push_back(stroke);
		}
	}

	void DrawLineGene::Draw()
	{
		SkCanvas canvas(this->bitmap);
		canvas.clear(SK_ColorTRANSPARENT);

		for (Stroke& stroke : this->strokes)
		{
			canvas.drawLine(
				stroke.points[0].x(), stroke.points[0].y(),
				stroke.points[1].x(), stroke.points[1].y(),
				stroke.paint
			);
		}
	}

	Gene* DrawLineGene::Crossover(Gene* mate)
	{
		DrawLineGene* childGene = new DrawLineGene(this->bitmap.width(), this->bitmap.height());
		DrawLineGene* mateDrawLineGene = static_cast<DrawLineGene*>(mate);

		int mutationMax = 1000;
		int numberOfStrokes = 250; // TODO: Make this a variable

		std::vector<Stroke> newStrokes;

		for (int i = 0; i < numberOfStrokes; ++i)
		{
			Stroke stroke;

			// Determine the paint
			stroke.paint =
				rand() % mutationMax == 675 ?
				Stroke::RandomPaint() :
				(
					rand() % 100 > 49 ?
						this->strokes[i].paint :
						mateDrawLineGene->GetStrokes()[i].paint
				);

			// Determine the points
			stroke.points =
				rand() % mutationMax == 675 ?
				Stroke::RandomPoints(this->bitmap.width(), this->bitmap.height()) :
				(
					rand() % 100 > 49 ?
						this->strokes[i].points :
						mateDrawLineGene->GetStrokes()[i].points
				);

			newStrokes.push_back(stroke);
		}

		childGene->Init(newStrokes);

		return childGene;
	}

	const std::vector<Stroke>& DrawLineGene::GetStrokes() const
	{
		return this->strokes;
	}
}