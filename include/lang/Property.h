#ifndef _LANG_PROPERTY_H
#define _LANG_PROPERTY_H

#include <lang/Object.h>
#include <lang/FastDelegate.h>
#include <lang/Event.h>

BEGIN_NAMESPACE(lang)

template <class T> class ValueAccessorModifier
{
public:
	ValueAccessorModifier();
	ValueAccessorModifier(const T&);
	void set(const T&);
	const T& get() const;
protected:
	T m_value;
};

template <class T, class Storage> class Property
{
public:
	//static const SourcedEvent<T, T, T> CHANGED;
	Property();

	~Property();

	Property(const T&);

	const T& get() const;

	void set(const T&) const;

	Property operator=(const T&);

	const T& operator=(const Property&);

	void setFunction(const FastDelegate<T>, ValueAccessorModifier<T>&);

	void attach();

	void detach();

	P(NS(event, Link)) listen(const FastDelegate<T>, ValueAccessorModifier<T>&);

	bool setFunctionSet(const FastDelegate<T>, ValueAccessorModifier<T>&);
private:
	ValueAccessorModifier<T> m_value;
	bool m_attached;
	NS(lang, FastDelegate)<void T> m_setFunction;
};

}

#endif