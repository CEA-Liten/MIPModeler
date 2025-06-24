#ifndef __MIPModelerTest__
#define __MIPModelerTest__


#include "MIPModeler.h"

#include <vector>
int mFactory = 2;
int mClient = 3;
std::vector<double> mCapacity{ 350 , 600 };
std::vector<double> mDemand{ 325, 300, 275 };
std::vector<std::vector<double>> mCost{ {0.225, 0.153, 0.162}, {0.225, 0.162, 0.126} };

#define VERIFY(value, ref) \
	(fabs(value - ref) < 1e-4) ? 0 : 1



#endif
