#include <gr/Primitive.h>

BEGIN_NAMESPACE(gr) 


Primitive::Primitive() : 
	ContextObject(CLASSID_PRIMITIVE) 
{
}

void Primitive::setPerspectiveCorrection( int /*quality*/ )
{
}

void Primitive::setWireframeColor( int /*color*/ )
{
}

void Primitive::setOpacity( int /*opacity*/ )
{
    assert(false); //[ADD] Recover from Darkest Fear and AA 24 | 24 ABS 3.0.0
}


} // gr

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
