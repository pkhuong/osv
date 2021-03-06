/*
 * Copyright (C) 2013 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */

#ifndef SEMAPHORE_HH_
#define SEMAPHORE_HH_

#include <osv/mutex.h>
#include <boost/intrusive/list.hpp>
#include <sched.hh>

class semaphore {
public:
    explicit semaphore(unsigned val);
    void post(unsigned units = 1);
    bool wait(unsigned units = 1, sched::timer* tmr = nullptr);
    bool trywait(unsigned units = 1);
private:
    unsigned _val;
    mutex _mtx;
    struct wait_record : boost::intrusive::list_base_hook<> {
        sched::thread* owner;
        unsigned units;
    };
    boost::intrusive::list<wait_record,
                          boost::intrusive::base_hook<wait_record>,
                          boost::intrusive::constant_time_size<false>> _waiters;
};

#endif /* SEMAPHORE_HH_ */
