#ifndef _LANG_SIGNAL_H
#define _LANG_SIGNAL_H

#include <lang/Object.h>
#include <stdint.h>

BEGIN_NAMESPACE(lang)

class Signal
{
public:
    Signal(bool set);

    ~Signal();

    void set();

    void reset();

    void wait();

    bool wait(uint32_t timeout_msec);

private:
    class Impl;
    Impl* m_impl;

    Signal(const Signal&);
    Signal& operator=(const Signal&);
};

}

#endif