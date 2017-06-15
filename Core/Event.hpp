#pragma once
#include <type_traits>
#include <typeinfo>
#include "StdTypes.hpp" 



class Event {
public:
    using Id = u64;

    virtual ~Event() = default;

    virtual Id getId() const{
        return 0;
    }

    static Id GenerateUniqueId() {
        static Id current = 0;
        return ++current;
    }

private:
    Id id {};

};



#define EVENT \
    public: static const Event::Id _id; Id getId() const override { return _id; }; private:

#define REGISTER_EVENT(name) const Event::Id name::_id = Event::GenerateUniqueId()

template<typename T>
bool is_of_type(const Event* event) {
    return event->getId() == T::_id;
}

template<typename T>
typename std::enable_if<std::is_base_of<Event, T>::value, T*>::type event_cast(Event* event) {
    if(is_of_type<T>(event)) {
        return dynamic_cast<T*>(event);
    } else {
        throw std::bad_cast();
    }
}
