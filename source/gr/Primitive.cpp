#include <gr/Primitive.h>

BEGIN_NAMESPACE(gr) 


Primitive::Primitive() : 
	ContextObject(CLASSID_PRIMITIVE) 
{
}

void Primitive::setPerspectiveCorrection( int /*quality*/ ) //11
{
}

void Primitive::setWireframeColor( int /*color*/ ) //15
{
}

void Primitive::setOpacity( int /*opacity*/ ) //19
{
    assert(false); //[ADD] Recover from Darkest Fear and AA 24 | 24 ABS 3.0.0
}


} // gr

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
