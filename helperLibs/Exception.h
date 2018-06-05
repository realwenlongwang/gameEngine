//
// Created by Wenlong Wang on 5/06/18.
//

#ifndef WATERRENDERING_EXCEPTION_H
#define WATERRENDERING_EXCEPTION_H

#include <string>
#include <exception>

#define SOURCE_ERROR(...) make_source_error(__VA_ARGS__, __FILE__, __func__, __LINE__ )

inline std::string make_source_error( std::string msg,
                                      char const* file, char const* function,
                                      std::size_t line
) {
    return std::string{} + file + "(" + std::to_string(line) + "): [" +
           function + "] " + msg;
}


#endif //WATERRENDERING_EXCEPTION_H
