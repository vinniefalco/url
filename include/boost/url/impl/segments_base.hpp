//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2022 Alan de Freitas (alandefreitas@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//

#ifndef BOOST_URL_IMPL_SEGMENTS_BASE_HPP
#define BOOST_URL_IMPL_SEGMENTS_BASE_HPP

#include <boost/url/grammar/recycled.hpp>
#include <boost/url/detail/segments_iter_impl.hpp>
#include <boost/assert.hpp>
#include <iterator>

namespace boost {
namespace urls {

class segments_base::iterator
{
    detail::segments_iter_impl it_;

#ifndef BOOST_URL_ITERATOR_STRINGS
    mutable grammar::recycled_ptr<
        std::string> s_ = nullptr;
    mutable std::size_t n_ = 0;
    mutable bool valid_ = false;
#endif

    friend class segments_base;
    friend class segments_ref;

    BOOST_URL_DECL
    segments_base::reference
    dereference() const;

    iterator(detail::path_ref const&) noexcept;
    iterator(detail::path_ref const&, int) noexcept;

    iterator(
        detail::segments_iter_impl const& it) noexcept
        : it_(it)
    {
    }

public:
    using value_type = std::string;
#ifndef BOOST_URL_ITERATOR_STRINGS
    using reference = string_view;
#else
    using reference = std::string;
#endif
    using difference_type = std::ptrdiff_t;
    using iterator_category =
        std::bidirectional_iterator_tag;

#ifndef BOOST_URL_ITERATOR_STRINGS
    struct pointer
    {
        string_view s;

        string_view const*
        operator->()
        {
            return &s;
        }
    };
#else
    using pointer = void const*;
#endif

    iterator() = default;

    BOOST_URL_DECL
    iterator(
        iterator const&) noexcept;

    BOOST_URL_DECL
    iterator& operator=(
        iterator const&) noexcept;

    reference
    operator*() const
    {
        return dereference();
    }

#ifndef BOOST_URL_ITERATOR_STRINGS
    pointer
    operator->() const
    {
        return {dereference()};
    }
#endif

    iterator&
    operator++() noexcept
    {
#ifndef BOOST_URL_ITERATOR_STRINGS
        valid_ = false;
#endif
        it_.increment();
        return *this;
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
    operator++(int) noexcept
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    iterator
    operator--(int) noexcept
    {
        auto tmp = *this;
        --*this;
        return tmp;
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
std::string
segments_base::
front() const noexcept
{
    BOOST_ASSERT(! empty());
    return *begin();
}

inline
std::string
segments_base::
back() const noexcept
{
    BOOST_ASSERT(! empty());
    return *--end();
}

} // urls
} // boost

#endif
