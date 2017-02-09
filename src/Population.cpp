#include "Population.h"
#include "DrawLineGene.h"
#include <boost/lexical_cast.hpp>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

namespace GeneticImages
{
	Population::Population(const SkBitmap* targetBitmap)
	{
		this->targetBitmap = targetBitmap;
		this->currentGeneration = 1;
	}

	Population::~Population()
	{
		this->DeleteGenePool();
	}

	void Population::Init()
	{
		for (int i = 0; i < 100; ++i)
		{
			DrawLineGene* gene = new DrawLineGene(this->targetBitmap->width(), this->targetBitmap->height());
			gene->InitRandomly();
			this->genes.push_back(gene);
		}
	}

	void Population::EvaluateFitness()
	{
		boost::thread_group threads;

		for (int i = 0; i < this->genes.size(); ++i)
		{
			if (i % 8 == 0) // TODO: Instead of hardcoding '8', this should be the number of CPU cores available (+ virtual cores?)
				threads.join_all();

			threads.create_thread(boost::bind<void>([this, i]() {
				this->genes[i]->Draw();
				this->genes[i]->EvaluateFitness(*this->targetBitmap);
			}));
		}

		threads.join_all();
	}

	void Population::NaturalSelection()
	{
		std::vector<Gene*> topGenes = this->GetTopGenes();

		topGenes[0]->Save("best-of-generation-" + boost::lexical_cast<std::string>(this->currentGeneration) + ".png");

		// Reproduce the top genes
		std::vector<Gene*> newGenes = this->Reproduce(topGenes);

		// Delete all the old genes
		this->DeleteGenePool();

		// Set the new genes
		this->genes = newGenes;

		// Increment the generation counter
		++this->currentGeneration;
	}

	void Population::DeleteGenePool()
	{
		for (Gene* gene : this->genes)
		{
			delete gene;
		}

		this->genes.clear();
	}

	std::vector<Gene*> Population::Reproduce(const std::vector<Gene*> genePool)
	{
		std::vector<Gene*> newGenes;

		for (Gene* gene1 : genePool)
		{
			for (Gene* gene2 : genePool)
			{
				// if (gene1 != gene2)
				// {
					newGenes.push_back(gene1->Crossover(gene2));

					if (newGenes.size() == 100) // TODO: Make this a variable (populationLimit)
					{
						return newGenes;
					}
				//}
			}
		}

		// This will probably never be reached
		return newGenes;
	}

	std::vector<Gene*> Population::GetTopGenes()
	{
		std::vector<Gene*> topGenes;

		// Loop through all genes to find the top performers
		for (Gene* gene : this->genes)
		{
			// If the top genes list isn't full yet
			if (topGenes.size() < 10) // TODO: Turn this into a variable
			{
				// Add this gene
				topGenes.push_back(gene);

				// Sort descending
				std::sort(topGenes.begin(), topGenes.end(), [](Gene* a, Gene* b) {
					return (*a) > (*b);
				});

				// Continue to the next loop
				continue;
			}
			
			// Check if this gene is better than one of the current top genes
			for (int i = 0; i < topGenes.size(); ++i)
			{
				// If this gene's fitness is better than the current top gene
				if ((*gene) > (*topGenes[i]))
				{
					// Remove the smallest gene
					topGenes.pop_back();

					// Add this gene
					topGenes.push_back(gene);

					// Sort descending
					std::sort(topGenes.begin(), topGenes.end(), [](Gene* a, Gene* b) {
						return (*a) > (*b);
					});

					// Break out of this loop
					break;
				}
			}
		}

		return topGenes;
	}
}