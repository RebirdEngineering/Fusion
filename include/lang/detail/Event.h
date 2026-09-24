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
            template <class Signature> class EventHandle :
                public Object
            {
            public:
                //template <Signature F> void (Link* link, Signature func);
                EventHandle();
                ~EventHandle(); //43

                bool isActive() const; //49

                void disable(); //54

                Link* m_link; //60
                Signature m_func; //61
            private:
                event_id_t m_id; //48
            };

        }
    }
}

#endif  