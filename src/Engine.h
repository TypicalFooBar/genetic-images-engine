#pragma once

#include <SkBitmap.h>

namespace GeneticImages
{
	class Engine
	{
		private:
			SkBitmap targetBitmap;
			bool DecodeFile(const char* filename, SkBitmap* bitmap, SkColorType colorType = kN32_SkColorType, bool requireUnpremul = false);

		public:
			Engine(const std::string targetBitmap);
			void Run();
	};
}