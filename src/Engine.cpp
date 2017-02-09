#include <iostream>
#include "Engine.h"
#include "Population.h"
#include <SkCodec.h>

namespace GeneticImages
{
	Engine::Engine(const std::string targetBitmap)
	{
		this->DecodeFile(targetBitmap.c_str(), &this->targetBitmap);
	}

	void Engine::Run()
	{
		Population population(&this->targetBitmap);
		population.Init();

		int t0 = time(NULL);
		for (int i = 0; i < 100; ++i)
		{
			population.EvaluateFitness();
			population.NaturalSelection();
		}
		int t1 = time(NULL);
    	std::cout << t1 - t0 << std::endl;
	}

	bool Engine::DecodeFile(const char* filename, SkBitmap* bitmap, SkColorType colorType, bool requireUnpremul)
	{
		SkASSERT(kIndex_8_SkColorType != colorType);
		sk_sp<SkData> data(SkData::MakeFromFileName(filename));
		std::unique_ptr<SkCodec> codec(SkCodec::NewFromData(data));
		if (!codec) {
			return false;
		}

		SkImageInfo info = codec->getInfo().makeColorType(colorType);
		if (requireUnpremul && kPremul_SkAlphaType == info.alphaType()) {
			info = info.makeAlphaType(kUnpremul_SkAlphaType);
		}

		if (!bitmap->tryAllocPixels(info)) {
			return false;
		}

		return SkCodec::kSuccess == codec->getPixels(info, bitmap->getPixels(), bitmap->rowBytes());
	}
}