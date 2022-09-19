//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_IMPL_PARAMS_BASE_HPP
#define BOOST_URL_IMPL_PARAMS_BASE_HPP

#include <boost/url/grammar/recycled.hpp>
#include <boost/url/detail/params_iter_impl.hpp>
#include <iterator>

namespace boost {
namespace urls {

//------------------------------------------------

class params_base::iterator
{
    detail::params_iter_impl it_;

#ifndef BOOST_URL_ITERATOR_STRINGS
    mutable grammar::recycled_ptr<
        std::string> key_ = nullptr;
    mutable grammar::recycled_ptr<
        std::string> value_ = nullptr;
    mutable bool has_value_ = false;
    mutable bool valid_ = false;
#endif

    friend class params_base;
    friend class params_ref;

    iterator(detail::query_ref const& ref) noexcept;
    iterator(detail::query_ref const& impl, int) noexcept;

    iterator(
        detail::params_iter_impl const& it)
        : it_(it)
    {
    }

public:
    using value_type = param;
#ifndef BOOST_URL_ITERATOR_STRINGS
    using reference = param_view;
    using pointer = param_view;
#else
    using reference = param;
    using pointer = param;
#endif
    using difference_type =
        std::ptrdiff_t;
    using iterator_category =
        std::bidirectional_iterator_tag;

private:
    BOOST_URL_DECL
    reference
    dereference() const;
public:

    iterator() = default;

    BOOST_URL_DECL
    iterator(
        iterator const&) noexcept;

    BOOST_URL_DECL
    iterator& operator=(
        iterator const&) noexcept;

    iterator&
    operator++() noexcept
    {
#ifndef BOOST_URL_ITERATOR_STRINGS
        valid_ = false;
#endif
        it_.increment();
        return *this;
    }

    iterator
    operator++(int) noexcept
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    iterator&
    operator--() noexcept
    {
#ifndef BOOST_URL_ITERATOR_STRINGS
        valid_ = false;
#endif
        it_.decrement();
        return *this;
    }

    iterator
    operator--(int) noexcept
    {
        auto tmp = *this;
        --*this;
        return tmp;
    }

    reference
    operator*() const
    {
        return reference(dereference());
    }

    pointer
    operator->() const
    {
        return pointer(dereference());
    }

    bool
    operator==(
        iterator const& other) const noexcept
    {
        return it_.equal(other.it_);
    }

    bool
    operator!=(
        iterator const& other) const noexcept
    {
        return ! it_.equal(other.it_);
    }
};

//------------------------------------------------

inline
bool
params_base::
contains(
    string_view key,
    ignore_case_param ic) const noexcept
{
    return find(
        begin(),key, ic) != end();
}

inline
auto
params_base::
find(
    string_view key,
    ignore_case_param ic) const noexcept ->
        iterator
{
    return find_impl(
        begin().it_, key, ic);
}

inline
auto
params_base::
find(
    iterator it,
    string_view key,
    ignore_case_param ic) const noexcept ->
        iterator
{
    return find_impl(
        it.it_, key, ic);
}

inline
auto
params_base::
find_last(
    string_view key,
    ignore_case_param ic) const noexcept ->
        iterator
{
    return find_last_impl(
        end().it_, key, ic);
}

inline
auto
params_base::
find_last(
    iterator it,
    string_view key,
    ignore_case_param ic) const noexcept ->
        iterator
{
    return find_last_impl(
        it.it_, key, ic);
}

} // urls
} // boost

#endif
