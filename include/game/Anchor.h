#ifndef _GAME_ANCHOR_H
#define _GAME_ANCHOR_H

#include <gr/Rect.h>

BEGIN_NAMESPACE(game)

class Anchor //12
{
public:
	enum VAnchor { TOP, VCENTER, BOTTOM, BASELINE, VPIVOT, VUNDEFINED }; //15
	enum HAnchor { LEFT, HCENTER, RIGHT, HPIVOT, HUNDEFINED }; //16

	VAnchor v; //37
	HAnchor h; //38
	Anchor() { v = TOP; h = LEFT; } //18 | Check?
	Anchor(VAnchor va) { v = va; } //19 | Check?
	Anchor(HAnchor ha) { h = ha; } //20 | Check?
	Anchor(VAnchor va, HAnchor ha) { v = va; h = ha; } //21 | Check?
	Anchor(HAnchor ha, VAnchor va) { h = ha; v = va; } //22 | Check?

	bool operator==(const Anchor& anchor) const; //24 | Unused?

	void fromString(const char* str); //29

	NS(gr, Rect) offsetRect(const NS(gr, Rect)&, int refX, int refY) const; //34
};

END_NAMESPACE();

#endif