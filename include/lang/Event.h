#ifndef _LANG_EVENT_H
#define _LANG_EVENT_H

#include <lang/Object.h>
#include <functional>

namespace lang
{
    namespace event
    {
        typedef int event_id_t;

        template <class Signature> class Event
        {
        public:
            Event();
            bool operator<(const Event& rhs) const;

            event_id_t id();
        private:
            event_id_t m_id;
        };

        /*template <class Event, class Signature, float& A1, float& A2, float& A3, float& A4> void call()
        {
            //static StorageState storage;
        }*/

        namespace detail
        {

            enum CallState
            {
                Idle,
                Active,
                Dirty
            };

            template <class Signature> struct StorageState
            {
            public:
                StorageState();
                std::vector <P(EventHandle<Signature>)> listeners;
                CallState state;
            };

            //template <class EventType, float& A1, float& A2, float& A3, float& A4> void call()
            //{
            //public: StorageState storage; private: operator();
            //}
            //template <class EventType, class Signature> void getStorage()

        }

        class Link : public Object
        {
        public:
            enum Status
            {
                CONNECTED,
                DISCONNECTED,
                DESTRUCTED,
            };
            ~Link();

            void connect();

            void disconnect();

            Status status() const;

        private:
            std::function<Status(Link*, Status)> m_changeStatus; //tr1
            Status m_status; //185

            Link(const std::function<Status(Link*, Status)>&);
            Link& operator=(const Link&);
        };
    }
}

#endif //_LANG_EVENT_H