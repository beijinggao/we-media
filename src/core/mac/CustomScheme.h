//
// Created by gaodong on 2018/10/19.
//

#ifndef WE_MEDIA_CUSTOMSCHEME_H
#define WE_MEDIA_CUSTOMSCHEME_H
#pragma once


#include <string>

void RegisterSchemeHandlers();


template<typename charT>
inline bool starts_with(const std::basic_string<charT> &big, const std::basic_string<charT> &small) {
    if (&big == &small) return true;
    const typename std::basic_string<charT>::size_type big_size = big.size();
    const typename std::basic_string<charT>::size_type small_size = small.size();
    const bool valid_ = (big_size >= small_size);
    const bool starts_with_ = (big.compare(0, small_size, small) == 0);
    return valid_ and starts_with_;
}

inline bool ends_with(std::string &big, std::string &small) {
    if (&big == &small) return true;
    std::string::size_type big_size = big.size();
    std::string::size_type small_size = small.size();
    bool valid_ = (big_size >= small_size);
    bool ends_with_ = (big.compare(big_size - small_size, small_size, small) == 0);
    return valid_ and ends_with_;
}

#endif //WE_MEDIA_CUSTOMSCHEME_H
