#ifndef _LANG_DETAIL_EVENT_H
#define _LANG_DETAIL_EVENT_H

#include <lang/Event.h>

namespace lang
{
    namespace event
    {
        class Link;

        namespace detail
        {
            template <class Signature> class EventHandle : //33
                public Object
            {
            public:
                template <class Signature, class F> EventHandle(Link* link, F func) : //37
                    m_link(link),
                    m_func(func)
                {
                }

                ~EventHandle(); //43
                //{
                    //if (isActive()) //45
                        //delete this;
                //}

                bool isActive() const; //49
                //{
                    //return ?
                //}

                void disable(); //54

                //57?
                //58?

                Link* m_link; //60
                Signature m_func; //61


                //69 rhs
            };

        }
    }
}

#endif  