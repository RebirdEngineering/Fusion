#include <math/Domain.h>

BEGIN_NAMESPACE(hgr) 

/*
 * IMPLEMENTATION CLASS. Used for calculating particle system property values.
 */
template <class T> class ParticleSystem_Integral //8
{
public:
	T		v; //11
	T		dv; //12

	void set( NS(math,Domain)& startdomain, NS(math,Domain)& enddomain, float invlife ) //14
	{
		startdomain.getRandom( &v );
		enddomain.getRandom( &dv );
		dv -= v;
		dv *= invlife;
	}

	void integrate( float dt ) //22
	{
		v += dv*dt;
	}
};


} // hgr
