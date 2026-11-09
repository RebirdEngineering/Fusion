#ifndef _HGR_NODE_H
#define _HGR_NODE_H

#include <lang/Object.h>
#include <math/float3x4.h>

namespace gr
{
	class Context;
}


namespace hgr
{

class Camera;
class SceneInputStream;
class SceneOutputStream;

/**
 * Base class for all objects in scene graph. Node contains model
 * transformation and object hierarchy information.
 * Note that even though nodes are reference counted, 
 * references to parent are weak, i.e. parent can be destroyed
 * even though child is still referenced by the user. In that case
 * the child is automatically unlinked from the parent.
 * @ingroup hgr
 */
class Node : //99
	public lang::Object
{
public:
	/**
	 * Node class identifier. Used by the implementation to 
	 * avoid depending on RTTI, since this class might 
	 * be need to be ported to some platforms which do not 
	 * support run-time type information.
	 */
	enum NodeClassId //35
	{
		/** Node is either plain node or unknown derived class. Default type. */
		NODE_OTHER			= (0<<4),
		/** Node is Camera. */
		NODE_CAMERA			= (1<<4),
		/** Node is Console. */
		NODE_CONSOLE		= (2<<4),
		/** Node is Dummy. */
		NODE_DUMMY			= (3<<4),
		/** Node is Light. */
		NODE_LIGHT			= (4<<4),
		/** Node is Scene. */
		NODE_SCENE			= (5<<4),
		/** First class id of Visuals. */
		NODE_FIRST_VISUAL	= (6<<4),
		/** Node is Lines. */
		NODE_LINES			= (6<<4),
		/** Node is Mesh. */
		NODE_MESH			= (7<<4),
		/** Node is Visual, but not Mesh or ParticleSystem. */
		NODE_OTHER_VISUAL	= (8<<4),
		/** Node is ParticleSystem. */
		NODE_PARTICLESYSTEM = (9<<4),
		/** Last class id of Visuals. */
		NODE_LAST_VISUAL	= (9<<4),
		/** The first of the class IDs reserved to the user application. */
		NODE_USERCLASSID_1	= (12<<4),
		/** The second of the class IDs reserved to the user application. */
		NODE_USERCLASSID_2	= (13<<4),
		/** The third of the class IDs reserved to the user application. */
		NODE_USERCLASSID_3	= (14<<4),
		/** The fourth of the class IDs reserved to the user application. */
		NODE_USERCLASSID_4	= (15<<4),
	};

	/*
	 * Internal node state flags.
	 */
	enum NodeFlags //74
	{
		/** Node enabled flag. Exact usage semantics is dependent on derived class. */
		NODE_ENABLED				= 1, // bit 0
		/** Light type mask for Light class instances. */
		NODE_LIGHTTYPE				= (3<<2), // bits 2:3
		/** Shift needed to access light type. */
		NODE_LIGHTTYPE_SHIFT		= 2,
		/** NodeClassId of this Node. Default is NODE_OTHER. */
		NODE_CLASS					= (31<<4), // bits 4:8
		/** Set if Node's bounding volumes are stored in world space coordinates. */
		NODE_BOUNDWORLDSPACE		= (1<<9),
		/** Default type flags for Node. */
		NODE_DEFAULTS				= NODE_ENABLED + NODE_OTHER,
	};

	/** User data pointer base class. */
	class UserData //91
	{
	public:
	};

	/** 
	 * Creates non-parented node with identity as model transformation. 
	 */
	Node(); //99

	~Node(); //101

	/** 
	 * Copy by value. Clones child nodes.
	 */
	Node( const Node& other ); //106

	/**
	 * Returns clone of this node. Clones child nodes as well.
	 */
	virtual Node*			clone() const; //111

	virtual void					printHierarchy(); //117

	/** 
	 * Sets name of this node. 
	 */
	void					setName( const std::string& name ); //122

	/** 
	 * Sets model-to-parent node transform. Rotation can have scaling. 
	 */
	void					setTransform( const math::float3x4& transform ); //127

	/** 
	 * Sets model-to-parent node position. 
	 */
	void					setPosition( const math::float3& position ); //132

	/** 
	 * Sets model-to-parent node rotation. Rotation can have scaling. 
	 */
	void					setRotation( const math::float3x3& rotation ); //137

	/** 
	 * Makes this node rotation to point at other node in world space.
	 * @param target Node to look at.
	 * @param up Up direction in world space.
	 */
	void					lookAt( const Node* target, const math::float3& up = math::float3(0,1,0) ); //144

	/** 
	 * Makes this node rotation to point at target position in world space.
	 * @param target World space position to look at.
	 * @param up Up direction in world space.
	 */
	void					lookAt( const math::float3& target, const math::float3& up = math::float3(0,1,0) ); //151

	/** 
	 * Links this as a child to parent node. 
	 * Increments reference counts of both nodes.
	 */
	void					linkTo( Node* parent ); //157

	/** 
	 * Unlinks this from parent() node. 
	 * Decrements reference counts of both nodes.
	 */
	void					unlink(); //163

	/**
	 * Sets node enabled/disabled.
	 * Disabled nodes are ignored in rendering (both lights and visuals).
	 */
	void					setEnabled( bool enabled ); //169

	/**
	 * 
	 * 
	 */
	void					setEnabledHierarchy(bool enabled); //175

	/*
	 * IMPL ONLY.
	 * Sets node transform index. Used by rendering implementation 
	 * to keep track of cached world transforms.
	 */
	void					setTransformIndex( int  ); //182

	/**
	 * Sets user data pointer for this node. This pointer is not
	 * used by hgr lib for anything. Default is 0.
	 */
	void					setUserData( UserData* userdata ); //188

	/**
	 * Sets (user specified) ID of the node.
	 */
	void					setID( int id ); //193

	/**
	 * Returns user data pointer for this node. This pointer is not
	 * used by hgr lib for anything. Default is 0.
	 */
	UserData*				userData() const; //199

	/**
	 * Returns true if node is enabled.
	 */
	bool					enabled() const; //204

	/** 
	 * Returns name of this node. 
	 */
	const std::string&		name() const; //209

	/** 
	 * Returns current transform in parent space. Rotation can have scaling. 
	 */
	const math::float3x4&	transform() const; //214

	/** 
	 * Returns current rotation in parent space. Rotation can have scaling. 
	 */
	math::float3x3			rotation() const; //219
	
	/** 
	 * Returns current position in parent space. Rotation can have scaling. 
	 */
	math::float3			position() const; //224
	
	/** 
	 * Calculates current model-to-world transform. 
	 */
	math::float3x4			worldTransform() const; //229

	/**
	 * Returns cached (model-to-world) transform. 
	 * Can be used only during rendering.
	 */
	const math::float3x4&	getCachedTransform( gr::Context* context ) const; //240

	/** 
	 * Returns the parent of this node. Returns 0 if no parent set. 
	 */
	Node*					parent() const; //240
	
	/** 
	 * Returns the first child of this node. Returns 0 if no children. 
	 */
	Node*					firstChild() const; //245
	
	/** 
	 * Returns the next child of this node. Returns 0 if none. 
	 */
	Node*					getNextChild( const Node* child ) const; //250

	/** 
	 * Returns the root of the node hierarchy. 
	 */
	Node*					root() const; //255

	/** 
	 * Returns true if this node has the other node as some grand parent. 
	 */
	bool					hasParent( const Node* other ) const; //260

	/**
	 * Returns depth of the hierarchy at specified node.
	 * If the node has no parent then the depth if 0, if single parent then depth is 1, etc.
	 */
	int						depth() const; //366

	/** 
	 * Iterates through the scene graph hierarchy. 
	 * This function can be used to enumerate all objects in the scene graph under given root.
	 * Iteration is performed in child-first-then-sibling order.
	 * Note that to iterate throught the scene graph the return
	 * value of this function must be used to ask for next node.
	 * @param root Iteration root. Must be != 0.
	 */
	Node*					next( const Node* root ) const; //276

	/**
	 * Finds recursively node with specified name from the node hierarchy.
	 * @exception Exception If node not found.
	 */
	Node*					getNodeByName( const std::string& name ) const; //282

	/**
	 * Finds recursively node from subtree with specified name from the node hierarchy.
	 * @exception Exception If node not found.
	 */
	Node*					getNodeByNameFromSubtree( const std::string& name ); //288

	/**
	 * Tries to find node recursively with specified id from the node hierarchy.
	 * @return 0 if node not found.
	 */
	Node*					find( int id ) const; //294

	/**
	 * Tries to find node recursively with specified name from the node hierarchy.
	 * @return 0 if node not found.
	 */
	Node*					findNodeByName( const std::string& name ) const; //300

	/**
	 * Tries to find node recursively from subtree with specified name from the node hierarchy.
	 * @return 0 if node not found.
	 */
	Node*					findNodeByNameFromSubtree( const std::string& name ); //306

	/**
	 * Returns (user specified) ID of the node.
	 */
	int						id() const				{return m_id;} //311

	/**
	 * Returns true if Node's NodeClassID is between FIRST_VISUAL and LAST_VISUAL.
	 */
	bool					isVisualNode() const; //316

	/**
	 * Returns type of the node. Used by the implementation to 
	 * avoid depending on RTTI.
	 */
	NodeClassId				classId() const; //322

protected:
	/*
	 * Sets class id of the node.
	 * Warning: This is not RTTI checked.
	 */
	void	setClassId( NodeClassId type ); //329

	/*
	 * Sets node flags. Node flags are internal representation
	 * method of some node options. This method, along with flags(),
	 * is used only for loading/saving of nodes data.
	 */
	void	setFlags( int flags ); //335

	/*
	 * Sets a single flag enabled/disabled.
	 */
	void	setFlag( NodeFlags flag, bool enabled ); //341

	/* 
	 * Returns node flags. Node flags are internal representation
	 * method of some node options. This method, along with setFlags,
	 * is used only for loading/saving of node data.
	 */
	int		flags() const; //348

	/*
	 * Gets a single flag enabled/disabled state.
	 */
	bool	getFlag( NodeFlags flag ) const; //353

private:
	friend class Camera;
	friend class SceneInputStream;
	friend class SceneOutputStream;

	math::float3x4				m_modeltm; //360
	mutable short					m_flags; //361
	mutable short					m_tmindex; //362
	Node*							m_parent; //363
	P(Node)							m_child; //364
	P(Node)							m_next; //365
	Node*							m_previous; //366
	std::string					m_name; //367
	UserData*						m_userData; //368
	int								m_id; //369

	Node& operator=( const Node& ); //371
};


#include <hgr/Node.inl>


} // hgr


#endif // _HGR_NODE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
