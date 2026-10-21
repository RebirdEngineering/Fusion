#ifndef _GR_CONTEXTOBJECT_H
#define _GR_CONTEXTOBJECT_H

#include <lang/Object.h>

BEGIN_NAMESPACE(gr) 
	
/**
 * Base class for rendering context dependent objects.
 * @ingroup gr
 */
class ContextObject : //11
	public NS(lang,Object)
{
public:
	/**
	 * Context object class identifier.
	 * Used by the implementation to avoid depending on RTTI.
	 */
	enum ClassId //19
	{
		/**
		 * Geometric primitive (list) resource.
		 */
		CLASSID_PRIMITIVE,
		/**
		 * Shader resource.
		 */
		CLASSID_SHADER,
		/**
		 * Texture resource.
		 */
		CLASSID_TEXTURE,
		/**
		 * Cube texture resource.
		 */
		CLASSID_CUBETEXTURE,
		/**
		 * Palette resource.
		 */
		CLASSID_PALETTE,
        /**
		 * 
		 */
		CLASSID_IMAGE,
		CLASSID_COUNT
	};

	/**
	 * Context objects need to be locked before raw data can be accessed.
	 */
	enum LockType //50
	{
		/** No lock. */
		LOCK_NONE		= 0,
		/** Read-only lock. */
		LOCK_READ		= 1,
		/** Write-only lock. */
		LOCK_WRITE		= 2,
		/** Read-write lock. */
		LOCK_READWRITE	= 3,
        /**  */
        LOCK_READ_VERTEXONLY		= 5,
		/**  */
		LOCK_WRITE_VERTEXONLY		= 6,
		/**  */
		LOCK_READWRITE_VERTEXONLY	= 7,
		/**  */
		LOCK_VERTEXONLY_FLAG = 4 //Why the confusing order
	};
	
	/**
	 * Helper class for locking context objects for data access.
	 */
	class Lock //73
	{
	public:
		/** 
		 * Locks object until end of scope.
		 */
		explicit Lock( ContextObject* obj, LockType lock ); //79
	
		/**
		 * Unlocks object.
		 */
		~Lock(); //84
	
	private:
		P(ContextObject)	m_obj; //87
	
		Lock(); //89
		Lock( const Lock& ); //90
		Lock& operator=( const Lock& ); //91
	};

	ContextObject( ClassId classid ); //94

	/**
	 * Locks object for specified access. Default behaviour just returns the parameter,
	 * which in effect means that any object property can be accessed any time.
	 * Don't use this method directly, but use Lock handle/wrapper instead,
	 * which is exception-safe.
	 */
	virtual void		lock( LockType lock ); //102

	/**
	 * Releases access to object.
	 * Don't use this method directly, but use Lock handle/wrapper instead,
	 * which is exception-safe.
	 */
	virtual void		unlock(); //109

	/** 
	 * Returns current lock state of the object.
	 * Default state is LOCK_READWRITE (=object can be read
	 * or written any time).
	 */
	virtual LockType	locked() const; //116

	/**
	 * Returns class type id.
	 * Used by the implementation to avoid depending on RTTI.
	 */
	ClassId				classId() const		{return m_classId;} //122
    
    /**
	 * 
	 */
	bool		isVertexOnlyLock( LockType lock ); //127

private:
	ClassId		m_classId;
};


END_NAMESPACE() // gr


#endif // _GR_CONTEXTOBJECT_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
