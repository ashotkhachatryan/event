#ifndef EVENT_H
#define EVENT_H

#include <list>

template <typename T>
struct Event;

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}

template <typename R, typename ...Args>
struct Event<std::function<R(Args...)>>
{
    typedef std::function<R(Args...)> F;
public:
    void operator()(Args... arg) const
    {
        for (auto m : m_funcs)
        {
            (m)(arg...);
        }
    }
    void operator+=(const F f)
    {
        m_funcs.push_back(f);
    }
    void operator-=(const F f)
    {
        m_funcs.erase(std::remove_if
                (m_funcs.begin(), m_funcs.end(),
                [f](F x) {
                    return getAddress(x) == getAddress(f);
                }), m_funcs.end());
    }
private:
    std::list<F> m_funcs;
};

#endif // EVENT_H
