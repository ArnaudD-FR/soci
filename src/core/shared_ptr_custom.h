#ifndef _SOCI_CORE_SHARED_PTR_CUSTOM
#define _SOCI_CORE_SHARED_PTR_CUSTOM

#include <assert.h>

namespace soci
{

namespace details
{
namespace memory
{
template <typename T>
struct shared_ptr_counter
{
    shared_ptr_counter(T *t, const size_t c): ptr(t), counter(c) {}

    T       *ptr;
    size_t   counter;
};

template <typename T>
struct shared_ptr
{
    shared_ptr(): m_ptr(NULL) {}
    shared_ptr(T *t)
        : m_ptr(new shared_ptr_counter<T>(t, 1)) {}
    shared_ptr(const shared_ptr &sp): m_ptr(sp.m_ptr) { inc(); }

    ~shared_ptr() { dec(); }

    shared_ptr<T> &operator=(const shared_ptr &sp) { dec(); m_ptr = sp.m_ptr; inc(); return *this; }

    T &operator*() const { assert(m_ptr); return *m_ptr->ptr; }
    T *operator->() const { assert(m_ptr); return m_ptr->ptr; }

    T *get() const { assert(m_ptr); return m_ptr->ptr; }

    bool operator<(const shared_ptr<T> &sp) const { return m_ptr->ptr < sp.m_ptr->ptr; }
    bool operator<=(const shared_ptr<T> &sp) const { return m_ptr->ptr <= sp.m_ptr->ptr; }
    bool operator>(const shared_ptr<T> &sp) const { return m_ptr->ptr > sp.m_ptr->ptr; }
    bool operator>=(const shared_ptr<T> &sp) const { return m_ptr->ptr >= sp.m_ptr->ptr; }

    private:
        void inc() { if (m_ptr) m_ptr->counter++; }
        void dec() 
        { 
            if (!m_ptr) return;
            if (--m_ptr->counter == 0)
            {
                delete m_ptr->ptr;
                delete m_ptr;
            }
        }

    private:
        shared_ptr_counter<T> *m_ptr;
};

} // namespace memory

} // namespace details

} // namespace soci

#endif // _SOCI_CORE_SHARED_PTR_CUSTOM