#pragma once
namespace  ALight_Raster
{
	class  Math
	{
	public:
		static int Lerp(int a, int b, float t) //interplote int value
		{
			if (t <= 0) return a;
			if (t >= 1) return b;
			return static_cast<int>(b * t + (1 - t) * a + 0.5f);
		}
	};
}