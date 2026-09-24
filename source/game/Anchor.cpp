#include <game/Anchor.h>
#include <lang/Exception.h>

USING_NAMESPACE(lang)

BEGIN_NAMESPACE(game)

void Anchor::fromString(const char* str)
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
            throwError(Exception(Format("Invalid anchor: {0}", str)));
    }
}

/*void Anchor::offset(int, int, int, int, int)
{
}

Rect Anchor::offsetRect(const Rect& rect, int, int, int) const
{
}*/

END_NAMESPACE()