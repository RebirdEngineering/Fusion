#ifndef _LANG_SIGNAL_H
#define _LANG_SIGNAL_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)

class Signal
{
public:
    Signal(bool set); //17

    ~Signal(); //23

    void set(); //28

    void reset(); //33

    void wait(); //48

    bool wait(uint32_t timeout_msec); //45

private:
    Signal(const Signal&); //48
    Signal& operator=(const Signal&); //49

    class Impl;
    Impl* m_impl; //52
};

}

#endif