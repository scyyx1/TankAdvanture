#include "AutomatedObject.h"
#include "BaseEngine.h"
#include "CollisionDetection.h"
#include "header.h"
#include "Boss.h"
using namespace std;

AutomatedObject::AutomatedObject(GameEngine* pEngine, int iID, int iStartX, int iStartY,int iSize) 
	:DisplayableObject(iStartX, iStartY, pEngine, iSize, iSize, true), m_pEngine(pEngine)
{
	setVisible(true);
}

AutomatedObject::~AutomatedObject() {

}



void AutomatedObject::virtDraw()
{
	if (!isVisible())
		return;
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		m_iColour
	);


}

void AutomatedObject::virtDoUpdate(int iCurrentTime) {

}

