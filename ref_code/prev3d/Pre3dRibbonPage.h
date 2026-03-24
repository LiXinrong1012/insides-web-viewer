#pragma once


namespace Qtitan
{
	class RibbonPage;
	class RibbonBar;
	class RibbonGroup;
}

class RibbonHoopsVisibilityWidget;
class RibbonHoopsMaterialWidget;

class Pre3dRibbonPage
{
public:
	Pre3dRibbonPage(void);
	~Pre3dRibbonPage(void);

	Qtitan::RibbonPage* initPage(Qtitan::RibbonBar* ribbonBar);
	void update();


	Qtitan::RibbonPage* ribbonPage;


private:
	void createGroupView(Qtitan::RibbonGroup& page);
	void createGroupVisibility(Qtitan::RibbonGroup& page);
	void createGroupMaterial(Qtitan::RibbonGroup& page);


	RibbonHoopsVisibilityWidget*	_visibilityWidget;
	RibbonHoopsMaterialWidget*		_materialWidget;

};

