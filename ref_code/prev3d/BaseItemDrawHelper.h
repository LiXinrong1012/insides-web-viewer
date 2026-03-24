#pragma once

namespace INSIDES{
	class FEMPartBaseItem;
	class BaseItem;
	class AppearanceItem;
}

class BaseItemDrawHelper
{
public:
	BaseItemDrawHelper(void);
	~BaseItemDrawHelper(void);


	static void drawFEMPart(INSIDES::FEMPartBaseItem* item, INSIDES::AppearanceItem* appItem);
	static void drawFEMPartNodeID(int nodeCount,void* nodexyz,void* nodes);
};

