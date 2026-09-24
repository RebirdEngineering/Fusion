#include <gr/ContextObject.h>
#include <assert.h>

BEGIN_NAMESPACE(gr)

ContextObject::Lock::Lock( ContextObject* obj, LockType lock ) : //6
	m_obj( obj )
{
	assert( obj );
	obj->lock( lock );
}
	
ContextObject::Lock::~Lock()
{
	if ( m_obj )
		m_obj->unlock();
}

ContextObject::ContextObject( ClassId classid ) : //19
	m_classId(classid) 
{
}

ContextObject::LockType ContextObject::locked() const
{
	return LOCK_READWRITE;
}

void ContextObject::lock( LockType /*lock*/ ) //29
{
}

void ContextObject::unlock()
{
}


END_NAMESPACE() // gr

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
