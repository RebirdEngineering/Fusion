#include <game/Anchor.h>
#include <lang/Exception.h>

USING_NAMESPACE(gr)
USING_NAMESPACE(lang)

BEGIN_NAMESPACE(game)

void Anchor::fromString(const char* str) //9
{
    if (!str)
        return;
    if (!strcmp(str, "TOP"))
        v = TOP;
    else if (!strcmp(str, "VCENTER"))
        v = VCENTER;
    else if (!strcmp(str, "BOTTOM"))
        v = BOTTOM;
    else if (!strcmp(str, "BASELINE"))
        v = BASELINE;
    else if (!strcmp(str, "VPIVOT"))
        v = VPIVOT;
    else
    {
        if (!strcmp(str, "LEFT"))
            h = LEFT;
        if (!strcmp(str, "HCENTER"))
            h = HCENTER;
        if (!strcmp(str, "RIGHT"))
            h = RIGHT;
        if (!strcmp(str, "HPIVOT"))
            h = HPIVOT;
        else
            throwError(Exception(Format("Invalid anchor: {0}", str))); //34
    }
}

Rect Anchor::offsetRect(const Rect& rect, int refX, int refY) const //Recovered from ABFM, not used in ABS 4.1.0
{
    Rect newRect;

    switch (v)
    {
    case VCENTER: newRect.setTop(rect.top() - ((rect.height()) >> 1)); newRect.setBottom(rect.bottom() - (rect.height() >> 1)); break;
    case BOTTOM: newRect.setTop(rect.top() - rect.height()); newRect.setBottom(rect.bottom() - rect.height()); break;
    case BASELINE:
    case VPIVOT: newRect.setTop(rect.top() - refY); newRect.setBottom(rect.bottom() - refY); break;
    }

    switch (h)
    {
    case HCENTER: newRect.setLeft(rect.left() - (rect.width() >> 1)); newRect.setRight(rect.right() - (rect.width() >> 1)); break;
    case RIGHT: newRect.setLeft(rect.left() - rect.width()); newRect.setRight(rect.right() - rect.width()); break;
    case HPIVOT: newRect.setLeft(rect.left() - refX); newRect.setRight(rect.right() - refX); break;
    }

    return newRect;
}

END_NAMESPACE()