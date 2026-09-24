#ifndef _GAME_ANCHOR_H
#define _GAME_ANCHOR_H

#include <gr/Rect.h>

BEGIN_NAMESPACE(game)

class Anchor //8
{
public:
	enum VAnchor { TOP, VCENTER, BOTTOM, BASELINE, VPIVOT, VUNDEFINED }; //15 / 14 (ABFM)
	enum HAnchor { LEFT, HCENTER, RIGHT, HPIVOT, HUNDEFINED }; //16 / 15 (ABFM)

	VAnchor v; //21
	HAnchor h; //22
	Anchor();
	Anchor(VAnchor);
	Anchor(HAnchor);
	Anchor(VAnchor va, HAnchor ha);
	Anchor(HAnchor, VAnchor);
	bool operator==(const Anchor&) const;

	void fromString(const char* str);

	NS(gr, Rect) offsetRect(const NS(gr, Rect)&, int, int, int) const;
};

END_NAMESPACE();

#endif