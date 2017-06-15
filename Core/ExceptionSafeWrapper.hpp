#pragma once
#include <stdexcept>
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <list>



template<typename F>
class ExceptionSafe {
public:
    ExceptionSafe(F function, 
                  std::list<std::exception_ptr>& exceptions, 
                  std::mutex& exceptions_mutex):
        function {function}, exceptions {exceptions}, exceptions_mutex {exceptions_mutex} {
    }

    template<typename... Args>
    std::result_of_t<F(Args...)> operator()(Args&&... args) {
        try {
            function(std::forward<Args>(args)...);

        } catch(std::exception) {
            std::lock_guard<std::mutex> lock(exceptions_mutex);
            exceptions.push_back(std::current_exception());
        }
    }

private:
    F function;
    std::list<std::exception_ptr>& exceptions;
    std::mutex& exceptions_mutex;
};



template<typename F>
auto make_exception_safe(F f, 
                         std::list<std::exception_ptr>& exceptions, 
                         std::mutex& exceptions_mutex) {
    return ExceptionSafe<F>(f, exceptions, exceptions_mutex);
}
