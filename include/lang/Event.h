#ifndef _LANG_EVENT_H
#define _LANG_EVENT_H

#include <lang/Object.h>
#include <functional>

namespace lang
{
    namespace event
    {
        typedef int event_id_t; //31

        template <class Signature> class Event //40
        {
        public:
            Event(); //42
            bool operator<(const Event& rhs) const; //43

            event_id_t id(); //45

        private:
            event_id_t m_id; //48
        };

        /*template <class Event, class Signature, float& A1, float& A2, float& A3, float& A4> void call()
        {
            //static StorageState storage;
        }*/

        namespace detail
        {
            enum CallState { Idle, Active, Dirty }; //98

            template <class Signature> struct StorageState //101
            {
            public:
                StorageState(); //103
                std::vector <P(Signature)> listeners; //104
                CallState state; //105
            };

            template <class EventType, class Signature> StorageState<Signature>* getStorage(Event<Signature> e, bool create); //109
            /*{
                typedef std::map<Event<Signature>, StorageState<Signature>> Storage; //111
                static Storage storage; //112

                Storage::iterator it = storage.find(e); //119

                Link* link; //224
                return it;
            }*/

            //template <class EventType, float& A1, float& A2, float& A3, float& A4> void call()
            //{
            //public: StorageState storage; private: operator();
            //}
            //template <class EventType, class Signature> void getStorage()

        }

        class Link : public Object //114
        {
        public:
            enum Status //148
            {
                CONNECTED,
                DISCONNECTED,
                DESTRUCTED,
            };

            ~Link(); //156

            void connect(); //163

            void disconnect(); //169

            Status status() const; //174

            Link(const std::function<Status(Link*, Status)>& func); //180

        private:
            std::function<Status(Link*, Status)> m_changeStatus; //185
            Status m_status; //186

            Link(const Link&); //188
            Link& operator=(const Link&); //189
        };

        template <class EventType, class Signature, class F> P(Link) listen() //196
        {
            //Status operator(Link* link, Status newstatus); //199
            
            //203
            
            //::iterator it //208
        }

        template <class EventType, class Signature, class A1> void call() //267
        {
            //StorageState<Signature> storage(); //269
        }

        template <class EventType, class Signature, class A1, class A2> void call() //274
        {
        }

        template <class EventType, class Signature, class A1, class A2, class A3> void call() //281
        {
            //StorageState<Signature> storage(); //283
        }

        template <class EventType, class Signature, class A1, class A2, class A3, class A4> void call() //288
        {
            //detail::StorageState<Signature> storage = detail::getStorage(); //290 size_t i?
        }

        template <class EventType, class Signature> void post(Event<Signature> e) //315
        {
        }

        template <class EventType, class Signature, class A1> void post(Event<Signature> e, A1 a1) //322
        {
            //324
        }

        template <class EventType, class Signature, class A1, class A2> void post() //329
        {
            //331
        }

        template <class EventType, class Signature, class A1, class A2, class A3> void post() //336
        {
            //338?
        }

        template <class EventType, class Signature, class A1, class A2, class A3, class A4> void post() //343
        {
            
        }

        template <class EventType, class Signature> void postDelay(float delay, Event<Signature> e) //368
        {
            //370
        }

        template <class EventType, class Signature, class A1> void postDelay(float delay, Event<Signature> e) //375
        {
            //377
        }
    }
}

#endif //_LANG_EVENT_H