﻿// -*- C++ -*-
//===--------------------------- regex ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_REGEX
#define _LIBCPP_REGEX

/*
    regex synopsis

#include <initializer_list>

namespace std
{

namespace regex_constants
{

emum syntax_option_type
{
    icase      = unspecified,
    nosubs     = unspecified,
    optimize   = unspecified,
    collate    = unspecified,
    ECMAScript = unspecified,
    basic      = unspecified,
    extended   = unspecified,
    awk        = unspecified,
    grep       = unspecified,
    egrep      = unspecified
};

constexpr syntax_option_type operator~(syntax_option_type f);
constexpr syntax_option_type operator&(syntax_option_type lhs, syntax_option_type rhs);
constexpr syntax_option_type operator|(syntax_option_type lhs, syntax_option_type rhs);

enum match_flag_type
{
    match_default     = 0,
    match_not_bol     = unspecified,
    match_not_eol     = unspecified,
    match_not_bow     = unspecified,
    match_not_eow     = unspecified,
    match_any         = unspecified,
    match_not_null    = unspecified,
    match_continuous  = unspecified,
    match_prev_avail  = unspecified,
    format_default    = 0,
    format_sed        = unspecified,
    format_no_copy    = unspecified,
    format_first_only = unspecified
};

constexpr match_flag_type operator~(match_flag_type f);
constexpr match_flag_type operator&(match_flag_type lhs, match_flag_type rhs);
constexpr match_flag_type operator|(match_flag_type lhs, match_flag_type rhs);

enum error_type
{
    error_collate    = unspecified,
    error_ctype      = unspecified,
    error_escape     = unspecified,
    error_backref    = unspecified,
    error_brack      = unspecified,
    error_paren      = unspecified,
    error_brace      = unspecified,
    error_badbrace   = unspecified,
    error_range      = unspecified,
    error_space      = unspecified,
    error_badrepeat  = unspecified,
    error_complexity = unspecified,
    error_stack      = unspecified
};

}  // regex_constants

class regex_error
    : public runtime_error
{
public:
    explicit regex_error(regex_constants::error_type ecode);
    regex_constants::error_type code() const;
};

template <class charT>
struct regex_traits
{
public:
    typedef charT                   char_type;
    typedef basic_string<char_type> string_type;
    typedef locale                  locale_type;
    typedef /bitmask_type/          char_class_type;

    regex_traits();

    static size_t length(const char_type* p);
    charT translate(charT c) const;
    charT translate_nocase(charT c) const;
    template <class ForwardIterator>
        string_type
        transform(ForwardIterator first, ForwardIterator last) const;
    template <class ForwardIterator>
        string_type
        transform_primary( ForwardIterator first, ForwardIterator last) const;
    template <class ForwardIterator>
        string_type
        lookup_collatename(ForwardIterator first, ForwardIterator last) const;
    template <class ForwardIterator>
        char_class_type
        lookup_classname(ForwardIterator first, ForwardIterator last,
                         bool icase = false) const;
    bool isctype(charT c, char_class_type f) const;
    int value(charT ch, int radix) const;
    locale_type imbue(locale_type l);
    locale_type getloc()const;
};

template <class charT, class traits = regex_traits<charT>>
class basic_regex
{
public:
    // types:
    typedef charT                               value_type;
    typedef traits                              traits_type;
    typedef typename traits::string_type        string_type;
    typedef regex_constants::syntax_option_type flag_type;
    typedef typename traits::locale_type        locale_type;

    // constants:
    static constexpr regex_constants::syntax_option_type icase = regex_constants::icase;
    static constexpr regex_constants::syntax_option_type nosubs = regex_constants::nosubs;
    static constexpr regex_constants::syntax_option_type optimize = regex_constants::optimize;
    static constexpr regex_constants::syntax_option_type collate = regex_constants::collate;
    static constexpr regex_constants::syntax_option_type ECMAScript = regex_constants::ECMAScript;
    static constexpr regex_constants::syntax_option_type basic = regex_constants::basic;
    static constexpr regex_constants::syntax_option_type extended = regex_constants::extended;
    static constexpr regex_constants::syntax_option_type awk = regex_constants::awk;
    static constexpr regex_constants::syntax_option_type grep = regex_constants::grep;
    static constexpr regex_constants::syntax_option_type egrep = regex_constants::egrep;

    // construct/copy/destroy:
    basic_regex();
    explicit basic_regex(const charT* p, flag_type f = regex_constants::ECMAScript);
    basic_regex(const charT* p, size_t len, flag_type f = regex_constants::ECMAScript);
    basic_regex(const basic_regex&);
    basic_regex(basic_regex&&) noexcept;
    template <class ST, class SA>
        explicit basic_regex(const basic_string<charT, ST, SA>& p,
                             flag_type f = regex_constants::ECMAScript);
    template <class ForwardIterator>
        basic_regex(ForwardIterator first, ForwardIterator last,
                    flag_type f = regex_constants::ECMAScript);
    basic_regex(initializer_list<charT>, flag_type = regex_constants::ECMAScript);

    ~basic_regex();

    basic_regex& operator=(const basic_regex&);
    basic_regex& operator=(basic_regex&&) noexcept;
    basic_regex& operator=(const charT* ptr);
    basic_regex& operator=(initializer_list<charT> il);
    template <class ST, class SA>
        basic_regex& operator=(const basic_string<charT, ST, SA>& p);

    // assign:
    basic_regex& assign(const basic_regex& that);
    basic_regex& assign(basic_regex&& that) noexcept;
    basic_regex& assign(const charT* ptr, flag_type f = regex_constants::ECMAScript);
    basic_regex& assign(const charT* p, size_t len, flag_type f);
    template <class string_traits, class A>
        basic_regex& assign(const basic_string<charT, string_traits, A>& s,
                            flag_type f = regex_constants::ECMAScript);
    template <class InputIterator>
        basic_regex& assign(InputIterator first, InputIterator last,
                            flag_type f = regex_constants::ECMAScript);
    basic_regex& assign(initializer_list<charT>, flag_type = regex_constants::ECMAScript);

    // const operations:
    unsigned mark_count() const;
    flag_type flags() const;

    // locale:
    locale_type imbue(locale_type loc);
    locale_type getloc() const;

    // swap:
    void swap(basic_regex&);
};

template<class ForwardIterator>
basic_regex(ForwardIterator, ForwardIterator,
            regex_constants::syntax_option_type = regex_constants::ECMAScript)
    -> basic_regex<typename iterator_traits<ForwardIterator>::value_type>; // C++17

typedef basic_regex<char>    regex;
typedef basic_regex<wchar_t> wregex;

template <class charT, class traits>
    void swap(basic_regex<charT, traits>& e1, basic_regex<charT, traits>& e2);

template <class BidirectionalIterator>
class sub_match
    : public pair<BidirectionalIterator, BidirectionalIterator>
{
public:
    typedef typename iterator_traits<BidirectionalIterator>::value_type value_type;
    typedef typename iterator_traits<BidirectionalIterator>::difference_type difference_type;
    typedef BidirectionalIterator                                      iterator;
    typedef basic_string<value_type>                                string_type;

    bool matched;

    constexpr sub_match();

    difference_type length() const;
    operator string_type() const;
    string_type str() const;

    int compare(const sub_match& s) const;
    int compare(const string_type& s) const;
    int compare(const value_type* s) const;
};

typedef sub_match<const char*>             csub_match;
typedef sub_match<const wchar_t*>          wcsub_match;
typedef sub_match<string::const_iterator>  ssub_match;
typedef sub_match<wstring::const_iterator> wssub_match;

template <class BiIter>
    bool
    operator==(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator!=(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<=(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>=(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>(const sub_match<BiIter>& lhs, const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator==(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator!=(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator<(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator>(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool operator>=(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
                    const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator<=(const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator==(const sub_match<BiIter>& lhs,
               const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator!=(const sub_match<BiIter>& lhs,
               const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator<(const sub_match<BiIter>& lhs,
              const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter, class ST, class SA>
    bool operator>(const sub_match<BiIter>& lhs,
                   const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator>=(const sub_match<BiIter>& lhs,
               const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter, class ST, class SA>
    bool
    operator<=(const sub_match<BiIter>& lhs,
               const basic_string<typename iterator_traits<BiIter>::value_type, ST, SA>& rhs);

template <class BiIter>
    bool
    operator==(typename iterator_traits<BiIter>::value_type const* lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator!=(typename iterator_traits<BiIter>::value_type const* lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<(typename iterator_traits<BiIter>::value_type const* lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>(typename iterator_traits<BiIter>::value_type const* lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>=(typename iterator_traits<BiIter>::value_type const* lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<=(typename iterator_traits<BiIter>::value_type const* lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator==(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator!=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator<(const sub_match<BiIter>& lhs,
              typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator>(const sub_match<BiIter>& lhs,
              typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator>=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator<=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const* rhs);

template <class BiIter>
    bool
    operator==(typename iterator_traits<BiIter>::value_type const& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator!=(typename iterator_traits<BiIter>::value_type const& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<(typename iterator_traits<BiIter>::value_type const& lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>(typename iterator_traits<BiIter>::value_type const& lhs,
              const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator>=(typename iterator_traits<BiIter>::value_type const& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator<=(typename iterator_traits<BiIter>::value_type const& lhs,
               const sub_match<BiIter>& rhs);

template <class BiIter>
    bool
    operator==(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const& rhs);

template <class BiIter>
    bool
    operator!=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const& rhs);

template <class BiIter>
    bool
    operator<(const sub_match<BiIter>& lhs,
              typename iterator_traits<BiIter>::value_type const& rhs);

template <class BiIter>
    bool
    operator>(const sub_match<BiIter>& lhs,
              typename iterator_traits<BiIter>::value_type const& rhs);

template <class BiIter>
    bool
    operator>=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const& rhs);

template <class BiIter>
    bool
    operator<=(const sub_match<BiIter>& lhs,
               typename iterator_traits<BiIter>::value_type const& rhs);

template <class charT, class ST, class BiIter>
    basic_ostream<charT, ST>&
    operator<<(basic_ostream<charT, ST>& os, const sub_match<BiIter>& m);

template <class BidirectionalIterator,
          class Allocator = allocator<sub_match<BidirectionalIterator>>>
class match_results
{
public:
    typedef sub_match<BidirectionalIterator>                  value_type;
    typedef const value_type&                                 const_reference;
    typedef value_type&                                       reference;
    typedef /implementation-defined/                          const_iterator;
    typedef const_iterator                                    iterator;
    typedef typename iterator_traits<BidirectionalIterator>::difference_type difference_type;
    typedef typename allocator_traits<Allocator>::size_type   size_type;
    typedef Allocator                                         allocator_type;
    typedef typename iterator_traits<BidirectionalIterator>::value_type char_type;
    typedef basic_string<char_type>                           string_type;

    // construct/copy/destroy:
    explicit match_results(const Allocator& a = Allocator());
    match_results(const match_results& m);
    match_results(match_results&& m) noexcept;
    match_results& operator=(const match_results& m);
    match_results& operator=(match_results&& m);
    ~match_results();

    bool ready() const;

    // size:
    size_type size() const;
    size_type max_size() const;
    bool empty() const;

    // element access:
    difference_type length(size_type sub = 0) const;
    difference_type position(size_type sub = 0) const;
    string_type str(size_type sub = 0) const;
    const_reference operator[](size_type n) const;

    const_reference prefix() const;
    const_reference suffix() const;

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    // format:
    template <class OutputIter>
        OutputIter
        format(OutputIter out, const char_type* fmt_first,
               const char_type* fmt_last,
               regex_constants::match_flag_type flags = regex_constants::format_default) const;
    template <class OutputIter, class ST, class SA>
        OutputIter
        format(OutputIter out, const basic_string<char_type, ST, SA>& fmt,
               regex_constants::match_flag_type flags = regex_constants::format_default) const;
    template <class ST, class SA>
        basic_string<char_type, ST, SA>
        format(const basic_string<char_type, ST, SA>& fmt,
               regex_constants::match_flag_type flags = regex_constants::format_default) const;
    string_type
        format(const char_type* fmt,
               regex_constants::match_flag_type flags = regex_constants::format_default) const;

    // allocator:
    allocator_type get_allocator() const;

    // swap:
    void swap(match_results& that);
};

typedef match_results<const char*>             cmatch;
typedef match_results<const wchar_t*>          wcmatch;
typedef match_results<string::const_iterator>  smatch;
typedef match_results<wstring::const_iterator> wsmatch;

template <class BidirectionalIterator, class Allocator>
    bool
    operator==(const match_results<BidirectionalIterator, Allocator>& m1,
               const match_results<BidirectionalIterator, Allocator>& m2);

template <class BidirectionalIterator, class Allocator>
    bool
    operator!=(const match_results<BidirectionalIterator, Allocator>& m1,
               const match_results<BidirectionalIterator, Allocator>& m2);

template <class BidirectionalIterator, class Allocator>
    void
    swap(match_results<BidirectionalIterator, Allocator>& m1,
         match_results<BidirectionalIterator, Allocator>& m2);

template <class BidirectionalIterator, class Allocator, class charT, class traits>
    bool
    regex_match(BidirectionalIterator first, BidirectionalIterator last,
                match_results<BidirectionalIterator, Allocator>& m,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class BidirectionalIterator, class charT, class traits>
    bool
    regex_match(BidirectionalIterator first, BidirectionalIterator last,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class charT, class Allocator, class traits>
    bool
    regex_match(const charT* str, match_results<const charT*, Allocator>& m,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class Allocator, class charT, class traits>
    bool
    regex_match(const basic_string<charT, ST, SA>& s,
                match_results<typename basic_string<charT, ST, SA>::const_iterator, Allocator>& m,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class Allocator, class charT, class traits>
    bool
    regex_match(const basic_string<charT, ST, SA>&& s,
                match_results<typename basic_string<charT, ST, SA>::const_iterator, Allocator>& m,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default) = delete; // C++14

template <class charT, class traits>
    bool
    regex_match(const charT* str, const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class charT, class traits>
    bool
    regex_match(const basic_string<charT, ST, SA>& s,
                const basic_regex<charT, traits>& e,
                regex_constants::match_flag_type flags = regex_constants::match_default);

template <class BidirectionalIterator, class Allocator, class charT, class traits>
    bool
    regex_search(BidirectionalIterator first, BidirectionalIterator last,
                 match_results<BidirectionalIterator, Allocator>& m,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class BidirectionalIterator, class charT, class traits>
    bool
    regex_search(BidirectionalIterator first, BidirectionalIterator last,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class charT, class Allocator, class traits>
    bool
    regex_search(const charT* str, match_results<const charT*, Allocator>& m,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class charT, class traits>
    bool
    regex_search(const charT* str, const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class charT, class traits>
    bool
    regex_search(const basic_string<charT, ST, SA>& s,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class Allocator, class charT, class traits>
    bool
    regex_search(const basic_string<charT, ST, SA>& s,
                 match_results<typename basic_string<charT, ST, SA>::const_iterator, Allocator>& m,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default);

template <class ST, class SA, class Allocator, class charT, class traits>
    bool
    regex_search(const basic_string<charT, ST, SA>&& s,
                 match_results<typename basic_string<charT, ST, SA>::const_iterator, Allocator>& m,
                 const basic_regex<charT, traits>& e,
                 regex_constants::match_flag_type flags = regex_constants::match_default) = delete; // C++14

template <class OutputIterator, class BidirectionalIterator,
          class traits, class charT, class ST, class SA>
    OutputIterator
    regex_replace(OutputIterator out,
                  BidirectionalIterator first, BidirectionalIterator last,
                  const basic_regex<charT, traits>& e,
                  const basic_string<charT, ST, SA>& fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class OutputIterator, class BidirectionalIterator,
          class traits, class charT>
    OutputIterator
    regex_replace(OutputIterator out,
                  BidirectionalIterator first, BidirectionalIterator last,
                  const basic_regex<charT, traits>& e, const charT* fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class traits, class charT, class ST, class SA, class FST, class FSA>>
    basic_string<charT, ST, SA>
    regex_replace(const basic_string<charT, ST, SA>& s,
                  const basic_regex<charT, traits>& e,
                  const basic_string<charT, FST, FSA>& fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class traits, class charT, class ST, class SA>
    basic_string<charT, ST, SA>
    regex_replace(const basic_string<charT, ST, SA>& s,
                  const basic_regex<charT, traits>& e, const charT* fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class traits, class charT, class ST, class SA>
    basic_string<charT>
    regex_replace(const charT* s,
                  const basic_regex<charT, traits>& e,
                  const basic_string<charT, ST, SA>& fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class traits, class charT>
    basic_string<charT>
    regex_replace(const charT* s,
                  const basic_regex<charT, traits>& e,
                  const charT* fmt,
                  regex_constants::match_flag_type flags = regex_constants::match_default);

template <class BidirectionalIterator,
          class charT = typename iterator_traits< BidirectionalIterator>::value_type,
          class traits = regex_traits<charT>>
class regex_iterator
{
public:
    typedef basic_regex<charT, traits>           regex_type;
    typedef match_results<BidirectionalIterator> value_type;
    typedef ptrdiff_t                            difference_type;
    typedef const value_type*                    pointer;
    typedef const value_type&                    reference;
    typedef forward_iterator_tag                 iterator_category;

    regex_iterator();
    regex_iterator(BidirectionalIterator a, BidirectionalIterator b,
                   const regex_type& re,
                   regex_constants::match_flag_type m = regex_constants::match_default);
    regex_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b,
                   const regex_type&& __re,
                   regex_constants::match_flag_type __m
                                     = regex_constants::match_default) = delete; // C++14
    regex_iterator(const regex_iterator&);
    regex_iterator& operator=(const regex_iterator&);

    bool operator==(const regex_iterator&) const;
    bool operator!=(const regex_iterator&) const;

    const value_type& operator*() const;
    const value_type* operator->() const;

    regex_iterator& operator++();
    regex_iterator operator++(int);
};

typedef regex_iterator<const char*>             cregex_iterator;
typedef regex_iterator<const wchar_t*>          wcregex_iterator;
typedef regex_iterator<string::const_iterator>  sregex_iterator;
typedef regex_iterator<wstring::const_iterator> wsregex_iterator;

template <class BidirectionalIterator,
          class charT = typename iterator_traits< BidirectionalIterator>::value_type,
          class traits = regex_traits<charT>>
class regex_token_iterator
{
public:
    typedef basic_regex<charT, traits>       regex_type;
    typedef sub_match<BidirectionalIterator> value_type;
    typedef ptrdiff_t                        difference_type;
    typedef const value_type*                pointer;
    typedef const value_type&                reference;
    typedef forward_iterator_tag             iterator_category;

    regex_token_iterator();
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type& re, int submatch = 0,
                         regex_constants::match_flag_type m = regex_constants::match_default);
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type&& re, int submatch = 0,
                         regex_constants::match_flag_type m = regex_constants::match_default) = delete; // C++14
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type& re, const vector<int>& submatches,
                         regex_constants::match_flag_type m = regex_constants::match_default);
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type&& re, const vector<int>& submatches,
                         regex_constants::match_flag_type m = regex_constants::match_default) = delete; // C++14
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type& re, initializer_list<int> submatches,
                         regex_constants::match_flag_type m = regex_constants::match_default);
    regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                         const regex_type&& re, initializer_list<int> submatches,
                         regex_constants::match_flag_type m = regex_constants::match_default) = delete; // C++14
    template <size_t N>
        regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                             const regex_type& re, const int (&submatches)[N],
                             regex_constants::match_flag_type m = regex_constants::match_default);
    template <size_t N>
        regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
                             const regex_type& re, const int (&submatches)[N],
                             regex_constants::match_flag_type m = regex_constants::match_default) = delete // C++14;
    regex_token_iterator(const regex_token_iterator&);
    regex_token_iterator& operator=(const regex_token_iterator&);

    bool operator==(const regex_token_iterator&) const;
    bool operator!=(const regex_token_iterator&) const;

    const value_type& operator*() const;
    const value_type* operator->() const;

    regex_token_iterator& operator++();
    regex_token_iterator operator++(int);
};

typedef regex_token_iterator<const char*>             cregex_token_iterator;
typedef regex_token_iterator<const wchar_t*>          wcregex_token_iterator;
typedef regex_token_iterator<string::const_iterator>  sregex_token_iterator;
typedef regex_token_iterator<wstring::const_iterator> wsregex_token_iterator;

} // std
*/

#include <__config>
#include <__locale>
#include <deque>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <version>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#    pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros>

#define _LIBCPP_REGEX_COMPLEXITY_FACTOR 4096

_LIBCPP_BEGIN_NAMESPACE_STD

namespace regex_constants {

    // syntax_option_type

    enum syntax_option_type { icase = 1 << 0, nosubs = 1 << 1, optimize = 1 << 2, collate = 1 << 3, ECMAScript = 0, basic = 1 << 4, extended = 1 << 5, awk = 1 << 6, grep = 1 << 7, egrep = 1 << 8 };

    inline _LIBCPP_CONSTEXPR syntax_option_type operator~(syntax_option_type __x) {
        return syntax_option_type(~int(__x) & 0x1FF);
    }

    inline _LIBCPP_CONSTEXPR syntax_option_type operator&(syntax_option_type __x, syntax_option_type __y) {
        return syntax_option_type(int(__x) & int(__y));
    }

    inline _LIBCPP_CONSTEXPR syntax_option_type operator|(syntax_option_type __x, syntax_option_type __y) {
        return syntax_option_type(int(__x) | int(__y));
    }

    inline _LIBCPP_CONSTEXPR syntax_option_type operator^(syntax_option_type __x, syntax_option_type __y) {
        return syntax_option_type(int(__x) ^ int(__y));
    }

    inline syntax_option_type& operator&=(syntax_option_type& __x, syntax_option_type __y) {
        __x = __x & __y;
        return __x;
    }

    inline syntax_option_type& operator|=(syntax_option_type& __x, syntax_option_type __y) {
        __x = __x | __y;
        return __x;
    }

    inline syntax_option_type& operator^=(syntax_option_type& __x, syntax_option_type __y) {
        __x = __x ^ __y;
        return __x;
    }

    // match_flag_type

    enum match_flag_type {
        match_default = 0,
        match_not_bol = 1 << 0,
        match_not_eol = 1 << 1,
        match_not_bow = 1 << 2,
        match_not_eow = 1 << 3,
        match_any = 1 << 4,
        match_not_null = 1 << 5,
        match_continuous = 1 << 6,
        match_prev_avail = 1 << 7,
        format_default = 0,
        format_sed = 1 << 8,
        format_no_copy = 1 << 9,
        format_first_only = 1 << 10,
        __no_update_pos = 1 << 11,
        __full_match = 1 << 12
    };

    inline _LIBCPP_CONSTEXPR match_flag_type operator~(match_flag_type __x) {
        return match_flag_type(~int(__x) & 0x0FFF);
    }

    inline _LIBCPP_CONSTEXPR match_flag_type operator&(match_flag_type __x, match_flag_type __y) {
        return match_flag_type(int(__x) & int(__y));
    }

    inline _LIBCPP_CONSTEXPR match_flag_type operator|(match_flag_type __x, match_flag_type __y) {
        return match_flag_type(int(__x) | int(__y));
    }

    inline _LIBCPP_CONSTEXPR match_flag_type operator^(match_flag_type __x, match_flag_type __y) {
        return match_flag_type(int(__x) ^ int(__y));
    }

    inline match_flag_type& operator&=(match_flag_type& __x, match_flag_type __y) {
        __x = __x & __y;
        return __x;
    }

    inline match_flag_type& operator|=(match_flag_type& __x, match_flag_type __y) {
        __x = __x | __y;
        return __x;
    }

    inline match_flag_type& operator^=(match_flag_type& __x, match_flag_type __y) {
        __x = __x ^ __y;
        return __x;
    }

    enum error_type {
        error_collate = 1,
        error_ctype,
        error_escape,
        error_backref,
        error_brack,
        error_paren,
        error_brace,
        error_badbrace,
        error_range,
        error_space,
        error_badrepeat,
        error_complexity,
        error_stack,
        __re_err_grammar,
        __re_err_empty,
        __re_err_unknown
    };

}  // namespace regex_constants

class _LIBCPP_EXCEPTION_ABI regex_error : public runtime_error {
    regex_constants::error_type __code_;

  public:
    explicit regex_error(regex_constants::error_type __ecode);
    virtual ~regex_error() throw();

    regex_constants::error_type code() const {
        return __code_;
    }
};

template <regex_constants::error_type _Ev>
_LIBCPP_NORETURN inline void __throw_regex_error() {
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw regex_error(_Ev);
#else
    _VSTD::abort();
#endif
}

template <class _CharT>
struct _LIBCPP_TEMPLATE_VIS regex_traits {
  public:
    typedef _CharT char_type;
    typedef basic_string<char_type> string_type;
    typedef locale locale_type;
    typedef ctype_base::mask char_class_type;

#if defined(__mips__) && defined(__GLIBC__)
    static const char_class_type __regex_word = static_cast<char_class_type>(_ISbit(15));
#elif defined(__NetBSD__)
    // NetBSD defines classes up to 0x2000
    // see sys/ctype_bits.h, _CTYPE_Q
    static const char_class_type __regex_word = 0x8000;
#else
    static const char_class_type __regex_word = 0x80;
#endif

  private:
    locale __loc_;
    const ctype<char_type>* __ct_;
    const collate<char_type>* __col_;

  public:
    regex_traits();

    static size_t length(const char_type* __p) {
        return char_traits<char_type>::length(__p);
    }

    char_type translate(char_type __c) const {
        return __c;
    }
    char_type translate_nocase(char_type __c) const;
    template <class _ForwardIterator>
    string_type transform(_ForwardIterator __f, _ForwardIterator __l) const;
    template <class _ForwardIterator>
    string_type transform_primary(_ForwardIterator __f, _ForwardIterator __l) const {
        return __transform_primary(__f, __l, char_type());
    }
    template <class _ForwardIterator>
    string_type lookup_collatename(_ForwardIterator __f, _ForwardIterator __l) const {
        return __lookup_collatename(__f, __l, char_type());
    }
    template <class _ForwardIterator>
    char_class_type lookup_classname(_ForwardIterator __f, _ForwardIterator __l, bool __icase = false) const {
        return __lookup_classname(__f, __l, __icase, char_type());
    }
    bool isctype(char_type __c, char_class_type __m) const;

    int value(char_type __ch, int __radix) const {
        return __regex_traits_value(__ch, __radix);
    }
    locale_type imbue(locale_type __l);

    locale_type getloc() const {
        return __loc_;
    }

  private:
    void __init();

    template <class _ForwardIterator>
    string_type __transform_primary(_ForwardIterator __f, _ForwardIterator __l, char) const;
    template <class _ForwardIterator>
    string_type __transform_primary(_ForwardIterator __f, _ForwardIterator __l, wchar_t) const;

    template <class _ForwardIterator>
    string_type __lookup_collatename(_ForwardIterator __f, _ForwardIterator __l, char) const;
    template <class _ForwardIterator>
    string_type __lookup_collatename(_ForwardIterator __f, _ForwardIterator __l, wchar_t) const;

    template <class _ForwardIterator>
    char_class_type __lookup_classname(_ForwardIterator __f, _ForwardIterator __l, bool __icase, char) const;
    template <class _ForwardIterator>
    char_class_type __lookup_classname(_ForwardIterator __f, _ForwardIterator __l, bool __icase, wchar_t) const;

    static int __regex_traits_value(unsigned char __ch, int __radix);

    int __regex_traits_value(char __ch, int __radix) const {
        return __regex_traits_value(static_cast<unsigned char>(__ch), __radix);
    }

    int __regex_traits_value(wchar_t __ch, int __radix) const;
};

template <class _CharT>
const typename regex_traits<_CharT>::char_class_type regex_traits<_CharT>::__regex_word;

template <class _CharT>
regex_traits<_CharT>::regex_traits() {
    __init();
}

template <class _CharT>
typename regex_traits<_CharT>::char_type regex_traits<_CharT>::translate_nocase(char_type __c) const {
    return __ct_->tolower(__c);
}

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::string_type regex_traits<_CharT>::transform(_ForwardIterator __f, _ForwardIterator __l) const {
    string_type __s(__f, __l);
    return __col_->transform(__s.data(), __s.data() + __s.size());
}

template <class _CharT>
void regex_traits<_CharT>::__init() {
    __ct_ = &use_facet<ctype<char_type> >(__loc_);
    __col_ = &use_facet<collate<char_type> >(__loc_);
}

template <class _CharT>
typename regex_traits<_CharT>::locale_type regex_traits<_CharT>::imbue(locale_type __l) {
    locale __r = __loc_;
    __loc_ = __l;
    __init();
    return __r;
}

// transform_primary is very FreeBSD-specific

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::string_type regex_traits<_CharT>::__transform_primary(_ForwardIterator __f, _ForwardIterator __l, char) const {
    const string_type __s(__f, __l);
    string_type __d = __col_->transform(__s.data(), __s.data() + __s.size());
    switch (__d.size()) {
        case 1:
            break;
        case 12:
            __d[11] = __d[3];
            break;
        default:
            __d.clear();
            break;
    }
    return __d;
}

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::string_type regex_traits<_CharT>::__transform_primary(_ForwardIterator __f, _ForwardIterator __l, wchar_t) const {
    const string_type __s(__f, __l);
    string_type __d = __col_->transform(__s.data(), __s.data() + __s.size());
    switch (__d.size()) {
        case 1:
            break;
        case 3:
            __d[2] = __d[0];
            break;
        default:
            __d.clear();
            break;
    }
    return __d;
}

// lookup_collatename is very FreeBSD-specific

_LIBCPP_FUNC_VIS string __get_collation_name(const char* __s);

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::string_type regex_traits<_CharT>::__lookup_collatename(_ForwardIterator __f, _ForwardIterator __l, char) const {
    string_type __s(__f, __l);
    string_type __r;
    if (!__s.empty()) {
        __r = __get_collation_name(__s.c_str());
        if (__r.empty() && __s.size() <= 2) {
            __r = __col_->transform(__s.data(), __s.data() + __s.size());
            if (__r.size() == 1 || __r.size() == 12)
                __r = __s;
            else
                __r.clear();
        }
    }
    return __r;
}

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::string_type regex_traits<_CharT>::__lookup_collatename(_ForwardIterator __f, _ForwardIterator __l, wchar_t) const {
    string_type __s(__f, __l);
    string __n;
    __n.reserve(__s.size());
    for (typename string_type::const_iterator __i = __s.begin(), __e = __s.end(); __i != __e; ++__i) {
        if (static_cast<unsigned>(*__i) >= 127)
            return string_type();
        __n.push_back(char(*__i));
    }
    string_type __r;
    if (!__s.empty()) {
        __n = __get_collation_name(__n.c_str());
        if (!__n.empty())
            __r.assign(__n.begin(), __n.end());
        else if (__s.size() <= 2) {
            __r = __col_->transform(__s.data(), __s.data() + __s.size());
            if (__r.size() == 1 || __r.size() == 3)
                __r = __s;
            else
                __r.clear();
        }
    }
    return __r;
}

// lookup_classname

regex_traits<char>::char_class_type _LIBCPP_FUNC_VIS __get_classname(const char* __s, bool __icase);

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::char_class_type regex_traits<_CharT>::__lookup_classname(_ForwardIterator __f, _ForwardIterator __l, bool __icase, char) const {
    string_type __s(__f, __l);
    __ct_->tolower(&__s[0], &__s[0] + __s.size());
    return __get_classname(__s.c_str(), __icase);
}

template <class _CharT>
template <class _ForwardIterator>
typename regex_traits<_CharT>::char_class_type regex_traits<_CharT>::__lookup_classname(_ForwardIterator __f, _ForwardIterator __l, bool __icase, wchar_t) const {
    string_type __s(__f, __l);
    __ct_->tolower(&__s[0], &__s[0] + __s.size());
    string __n;
    __n.reserve(__s.size());
    for (typename string_type::const_iterator __i = __s.begin(), __e = __s.end(); __i != __e; ++__i) {
        if (static_cast<unsigned>(*__i) >= 127)
            return char_class_type();
        __n.push_back(char(*__i));
    }
    return __get_classname(__n.c_str(), __icase);
}

template <class _CharT>
bool regex_traits<_CharT>::isctype(char_type __c, char_class_type __m) const {
    if (__ct_->is(__m, __c))
        return true;
    return (__c == '_' && (__m & __regex_word));
}

template <class _CharT>
int regex_traits<_CharT>::__regex_traits_value(unsigned char __ch, int __radix) {
    if ((__ch & 0xF8u) == 0x30)  // '0' <= __ch && __ch <= '7'
        return __ch - '0';
    if (__radix != 8) {
        if ((__ch & 0xFEu) == 0x38)  // '8' <= __ch && __ch <= '9'
            return __ch - '0';
        if (__radix == 16) {
            __ch |= 0x20;  // tolower
            if ('a' <= __ch && __ch <= 'f')
                return __ch - ('a' - 10);
        }
    }
    return -1;
}

template <class _CharT>
inline int regex_traits<_CharT>::__regex_traits_value(wchar_t __ch, int __radix) const {
    return __regex_traits_value(static_cast<unsigned char>(__ct_->narrow(__ch, char_type())), __radix);
}

template <class _CharT>
class __node;

template <class _BidirectionalIterator>
class _LIBCPP_TEMPLATE_VIS sub_match;

template <class _BidirectionalIterator, class _Allocator = allocator<sub_match<_BidirectionalIterator> > >
class _LIBCPP_TEMPLATE_VIS match_results;

template <class _CharT>
struct __state {
    enum {
        __end_state = -1000,
        __consume_input,           // -999
        __begin_marked_expr,       // -998
        __end_marked_expr,         // -997
        __pop_state,               // -996
        __accept_and_consume,      // -995
        __accept_but_not_consume,  // -994
        __reject,                  // -993
        __split,
        __repeat
    };

    int __do_;
    const _CharT* __first_;
    const _CharT* __current_;
    const _CharT* __last_;
    vector<sub_match<const _CharT*> > __sub_matches_;
    vector<pair<size_t, const _CharT*> > __loop_data_;
    const __node<_CharT>* __node_;
    regex_constants::match_flag_type __flags_;
    bool __at_first_;

    __state() : __do_(0), __first_(nullptr), __current_(nullptr), __last_(nullptr), __node_(nullptr), __flags_() {
    }
};

// __node

template <class _CharT>
class __node {
    __node(const __node&);
    __node& operator=(const __node&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __node() {
    }

    virtual ~__node() {
    }

    virtual void __exec(__state&) const {
    }

    virtual void __exec_split(bool, __state&) const {
    }
};

// __end_state

template <class _CharT>
class __end_state : public __node<_CharT> {
  public:
    typedef _VSTD::__state<_CharT> __state;

    __end_state() {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __end_state<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__end_state;
}

// __has_one_state

template <class _CharT>
class __has_one_state : public __node<_CharT> {
    __node<_CharT>* __first_;

  public:
    explicit __has_one_state(__node<_CharT>* __s) : __first_(__s) {
    }

    __node<_CharT>* first() const {
        return __first_;
    }

    __node<_CharT>*& first() {
        return __first_;
    }
};

// __owns_one_state

template <class _CharT>
class __owns_one_state : public __has_one_state<_CharT> {
    typedef __has_one_state<_CharT> base;

  public:
    explicit __owns_one_state(__node<_CharT>* __s) : base(__s) {
    }

    virtual ~__owns_one_state();
};

template <class _CharT>
__owns_one_state<_CharT>::~__owns_one_state() {
    delete this->first();
}

// __empty_state

template <class _CharT>
class __empty_state : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __empty_state(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __empty_state<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    __s.__node_ = this->first();
}

// __empty_non_own_state

template <class _CharT>
class __empty_non_own_state : public __has_one_state<_CharT> {
    typedef __has_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __empty_non_own_state(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __empty_non_own_state<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    __s.__node_ = this->first();
}

// __repeat_one_loop

template <class _CharT>
class __repeat_one_loop : public __has_one_state<_CharT> {
    typedef __has_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __repeat_one_loop(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __repeat_one_loop<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__repeat;
    __s.__node_ = this->first();
}

// __owns_two_states

template <class _CharT>
class __owns_two_states : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    base* __second_;

  public:
    explicit __owns_two_states(__node<_CharT>* __s1, base* __s2) : base(__s1), __second_(__s2) {
    }

    virtual ~__owns_two_states();

    base* second() const {
        return __second_;
    }

    base*& second() {
        return __second_;
    }
};

template <class _CharT>
__owns_two_states<_CharT>::~__owns_two_states() {
    delete __second_;
}

// __loop

template <class _CharT>
class __loop : public __owns_two_states<_CharT> {
    typedef __owns_two_states<_CharT> base;

    size_t __min_;
    size_t __max_;
    unsigned __loop_id_;
    unsigned __mexp_begin_;
    unsigned __mexp_end_;
    bool __greedy_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __loop(unsigned __loop_id, __node<_CharT>* __s1, __owns_one_state<_CharT>* __s2, unsigned __mexp_begin, unsigned __mexp_end, bool __greedy = true, size_t __min = 0,
                    size_t __max = numeric_limits<size_t>::max())
        : base(__s1, __s2), __min_(__min), __max_(__max), __loop_id_(__loop_id), __mexp_begin_(__mexp_begin), __mexp_end_(__mexp_end), __greedy_(__greedy) {
    }

    virtual void __exec(__state& __s) const;
    virtual void __exec_split(bool __second, __state& __s) const;

  private:
    void __init_repeat(__state& __s) const {
        __s.__loop_data_[__loop_id_].second = __s.__current_;
        for (size_t __i = __mexp_begin_ - 1; __i != __mexp_end_ - 1; ++__i) {
            __s.__sub_matches_[__i].first = __s.__last_;
            __s.__sub_matches_[__i].second = __s.__last_;
            __s.__sub_matches_[__i].matched = false;
        }
    }
};

template <class _CharT>
void __loop<_CharT>::__exec(__state& __s) const {
    if (__s.__do_ == __state::__repeat) {
        bool __do_repeat = ++__s.__loop_data_[__loop_id_].first < __max_;
        bool __do_alt = __s.__loop_data_[__loop_id_].first >= __min_;
        if (__do_repeat && __do_alt && __s.__loop_data_[__loop_id_].second == __s.__current_)
            __do_repeat = false;
        if (__do_repeat && __do_alt)
            __s.__do_ = __state::__split;
        else if (__do_repeat) {
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__node_ = this->first();
            __init_repeat(__s);
        } else {
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__node_ = this->second();
        }
    } else {
        __s.__loop_data_[__loop_id_].first = 0;
        bool __do_repeat = 0 < __max_;
        bool __do_alt = 0 >= __min_;
        if (__do_repeat && __do_alt)
            __s.__do_ = __state::__split;
        else if (__do_repeat) {
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__node_ = this->first();
            __init_repeat(__s);
        } else {
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__node_ = this->second();
        }
    }
}

template <class _CharT>
void __loop<_CharT>::__exec_split(bool __second, __state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    if (__greedy_ != __second) {
        __s.__node_ = this->first();
        __init_repeat(__s);
    } else
        __s.__node_ = this->second();
}

// __alternate

template <class _CharT>
class __alternate : public __owns_two_states<_CharT> {
    typedef __owns_two_states<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __alternate(__owns_one_state<_CharT>* __s1, __owns_one_state<_CharT>* __s2) : base(__s1, __s2) {
    }

    virtual void __exec(__state& __s) const;
    virtual void __exec_split(bool __second, __state& __s) const;
};

template <class _CharT>
void __alternate<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__split;
}

template <class _CharT>
void __alternate<_CharT>::__exec_split(bool __second, __state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    if (__second)
        __s.__node_ = this->second();
    else
        __s.__node_ = this->first();
}

// __begin_marked_subexpression

template <class _CharT>
class __begin_marked_subexpression : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    unsigned __mexp_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __begin_marked_subexpression(unsigned __mexp, __node<_CharT>* __s) : base(__s), __mexp_(__mexp) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __begin_marked_subexpression<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    __s.__sub_matches_[__mexp_ - 1].first = __s.__current_;
    __s.__node_ = this->first();
}

// __end_marked_subexpression

template <class _CharT>
class __end_marked_subexpression : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    unsigned __mexp_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __end_marked_subexpression(unsigned __mexp, __node<_CharT>* __s) : base(__s), __mexp_(__mexp) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __end_marked_subexpression<_CharT>::__exec(__state& __s) const {
    __s.__do_ = __state::__accept_but_not_consume;
    __s.__sub_matches_[__mexp_ - 1].second = __s.__current_;
    __s.__sub_matches_[__mexp_ - 1].matched = true;
    __s.__node_ = this->first();
}

// __back_ref

template <class _CharT>
class __back_ref : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    unsigned __mexp_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __back_ref(unsigned __mexp, __node<_CharT>* __s) : base(__s), __mexp_(__mexp) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __back_ref<_CharT>::__exec(__state& __s) const {
    if (__mexp_ > __s.__sub_matches_.size())
        __throw_regex_error<regex_constants::error_backref>();
    sub_match<const _CharT*>& __sm = __s.__sub_matches_[__mexp_ - 1];
    if (__sm.matched) {
        ptrdiff_t __len = __sm.second - __sm.first;
        if (__s.__last_ - __s.__current_ >= __len && _VSTD::equal(__sm.first, __sm.second, __s.__current_)) {
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__current_ += __len;
            __s.__node_ = this->first();
        } else {
            __s.__do_ = __state::__reject;
            __s.__node_ = nullptr;
        }
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __back_ref_icase

template <class _CharT, class _Traits>
class __back_ref_icase : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _Traits __traits_;
    unsigned __mexp_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __back_ref_icase(const _Traits& __traits, unsigned __mexp, __node<_CharT>* __s) : base(__s), __traits_(__traits), __mexp_(__mexp) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __back_ref_icase<_CharT, _Traits>::__exec(__state& __s) const {
    sub_match<const _CharT*>& __sm = __s.__sub_matches_[__mexp_ - 1];
    if (__sm.matched) {
        ptrdiff_t __len = __sm.second - __sm.first;
        if (__s.__last_ - __s.__current_ >= __len) {
            for (ptrdiff_t __i = 0; __i < __len; ++__i) {
                if (__traits_.translate_nocase(__sm.first[__i]) != __traits_.translate_nocase(__s.__current_[__i]))
                    goto __not_equal;
            }
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__current_ += __len;
            __s.__node_ = this->first();
        } else {
            __s.__do_ = __state::__reject;
            __s.__node_ = nullptr;
        }
    } else {
    __not_equal:
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __back_ref_collate

template <class _CharT, class _Traits>
class __back_ref_collate : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _Traits __traits_;
    unsigned __mexp_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __back_ref_collate(const _Traits& __traits, unsigned __mexp, __node<_CharT>* __s) : base(__s), __traits_(__traits), __mexp_(__mexp) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __back_ref_collate<_CharT, _Traits>::__exec(__state& __s) const {
    sub_match<const _CharT*>& __sm = __s.__sub_matches_[__mexp_ - 1];
    if (__sm.matched) {
        ptrdiff_t __len = __sm.second - __sm.first;
        if (__s.__last_ - __s.__current_ >= __len) {
            for (ptrdiff_t __i = 0; __i < __len; ++__i) {
                if (__traits_.translate(__sm.first[__i]) != __traits_.translate(__s.__current_[__i]))
                    goto __not_equal;
            }
            __s.__do_ = __state::__accept_but_not_consume;
            __s.__current_ += __len;
            __s.__node_ = this->first();
        } else {
            __s.__do_ = __state::__reject;
            __s.__node_ = nullptr;
        }
    } else {
    __not_equal:
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __word_boundary

template <class _CharT, class _Traits>
class __word_boundary : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _Traits __traits_;
    bool __invert_;

  public:
    typedef _VSTD::__state<_CharT> __state;

    explicit __word_boundary(const _Traits& __traits, bool __invert, __node<_CharT>* __s) : base(__s), __traits_(__traits), __invert_(__invert) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __word_boundary<_CharT, _Traits>::__exec(__state& __s) const {
    bool __is_word_b = false;
    if (__s.__first_ != __s.__last_) {
        if (__s.__current_ == __s.__last_) {
            if (!(__s.__flags_ & regex_constants::match_not_eow)) {
                _CharT __c = __s.__current_[-1];
                __is_word_b = __c == '_' || __traits_.isctype(__c, ctype_base::alnum);
            }
        } else if (__s.__current_ == __s.__first_ && !(__s.__flags_ & regex_constants::match_prev_avail)) {
            if (!(__s.__flags_ & regex_constants::match_not_bow)) {
                _CharT __c = *__s.__current_;
                __is_word_b = __c == '_' || __traits_.isctype(__c, ctype_base::alnum);
            }
        } else {
            _CharT __c1 = __s.__current_[-1];
            _CharT __c2 = *__s.__current_;
            bool __is_c1_b = __c1 == '_' || __traits_.isctype(__c1, ctype_base::alnum);
            bool __is_c2_b = __c2 == '_' || __traits_.isctype(__c2, ctype_base::alnum);
            __is_word_b = __is_c1_b != __is_c2_b;
        }
    }
    if (__is_word_b != __invert_) {
        __s.__do_ = __state::__accept_but_not_consume;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __l_anchor

template <class _CharT>
class __l_anchor : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    __l_anchor(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __l_anchor<_CharT>::__exec(__state& __s) const {
    if (__s.__at_first_ && __s.__current_ == __s.__first_ && !(__s.__flags_ & regex_constants::match_not_bol)) {
        __s.__do_ = __state::__accept_but_not_consume;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __r_anchor

template <class _CharT>
class __r_anchor : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    __r_anchor(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __r_anchor<_CharT>::__exec(__state& __s) const {
    if (__s.__current_ == __s.__last_ && !(__s.__flags_ & regex_constants::match_not_eol)) {
        __s.__do_ = __state::__accept_but_not_consume;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __match_any

template <class _CharT>
class __match_any : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    __match_any(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __match_any<_CharT>::__exec(__state& __s) const {
    if (__s.__current_ != __s.__last_ && *__s.__current_ != 0) {
        __s.__do_ = __state::__accept_and_consume;
        ++__s.__current_;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __match_any_but_newline

template <class _CharT>
class __match_any_but_newline : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

  public:
    typedef _VSTD::__state<_CharT> __state;

    __match_any_but_newline(__node<_CharT>* __s) : base(__s) {
    }

    virtual void __exec(__state&) const;
};

template <>
_LIBCPP_FUNC_VIS void __match_any_but_newline<char>::__exec(__state&) const;
template <>
_LIBCPP_FUNC_VIS void __match_any_but_newline<wchar_t>::__exec(__state&) const;

// __match_char

template <class _CharT>
class __match_char : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _CharT __c_;

    __match_char(const __match_char&);
    __match_char& operator=(const __match_char&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __match_char(_CharT __c, __node<_CharT>* __s) : base(__s), __c_(__c) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT>
void __match_char<_CharT>::__exec(__state& __s) const {
    if (__s.__current_ != __s.__last_ && *__s.__current_ == __c_) {
        __s.__do_ = __state::__accept_and_consume;
        ++__s.__current_;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __match_char_icase

template <class _CharT, class _Traits>
class __match_char_icase : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _Traits __traits_;
    _CharT __c_;

    __match_char_icase(const __match_char_icase&);
    __match_char_icase& operator=(const __match_char_icase&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __match_char_icase(const _Traits& __traits, _CharT __c, __node<_CharT>* __s) : base(__s), __traits_(__traits), __c_(__traits.translate_nocase(__c)) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __match_char_icase<_CharT, _Traits>::__exec(__state& __s) const {
    if (__s.__current_ != __s.__last_ && __traits_.translate_nocase(*__s.__current_) == __c_) {
        __s.__do_ = __state::__accept_and_consume;
        ++__s.__current_;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __match_char_collate

template <class _CharT, class _Traits>
class __match_char_collate : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    _Traits __traits_;
    _CharT __c_;

    __match_char_collate(const __match_char_collate&);
    __match_char_collate& operator=(const __match_char_collate&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __match_char_collate(const _Traits& __traits, _CharT __c, __node<_CharT>* __s) : base(__s), __traits_(__traits), __c_(__traits.translate(__c)) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __match_char_collate<_CharT, _Traits>::__exec(__state& __s) const {
    if (__s.__current_ != __s.__last_ && __traits_.translate(*__s.__current_) == __c_) {
        __s.__do_ = __state::__accept_and_consume;
        ++__s.__current_;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

// __bracket_expression

template <class _CharT, class _Traits>
class __bracket_expression : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;
    typedef typename _Traits::string_type string_type;

    _Traits __traits_;
    vector<_CharT> __chars_;
    vector<_CharT> __neg_chars_;
    vector<pair<string_type, string_type> > __ranges_;
    vector<pair<_CharT, _CharT> > __digraphs_;
    vector<string_type> __equivalences_;
    typename regex_traits<_CharT>::char_class_type __mask_;
    typename regex_traits<_CharT>::char_class_type __neg_mask_;
    bool __negate_;
    bool __icase_;
    bool __collate_;
    bool __might_have_digraph_;

    __bracket_expression(const __bracket_expression&);
    __bracket_expression& operator=(const __bracket_expression&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __bracket_expression(const _Traits& __traits, __node<_CharT>* __s, bool __negate, bool __icase, bool __collate)
        : base(__s), __traits_(__traits), __mask_(), __neg_mask_(), __negate_(__negate), __icase_(__icase), __collate_(__collate), __might_have_digraph_(__traits_.getloc().name() != "C") {
    }

    virtual void __exec(__state&) const;

    bool __negated() const {
        return __negate_;
    }

    void __add_char(_CharT __c) {
        if (__icase_)
            __chars_.push_back(__traits_.translate_nocase(__c));
        else if (__collate_)
            __chars_.push_back(__traits_.translate(__c));
        else
            __chars_.push_back(__c);
    }

    void __add_neg_char(_CharT __c) {
        if (__icase_)
            __neg_chars_.push_back(__traits_.translate_nocase(__c));
        else if (__collate_)
            __neg_chars_.push_back(__traits_.translate(__c));
        else
            __neg_chars_.push_back(__c);
    }

    void __add_range(string_type __b, string_type __e) {
        if (__collate_) {
            if (__icase_) {
                for (size_t __i = 0; __i < __b.size(); ++__i) __b[__i] = __traits_.translate_nocase(__b[__i]);
                for (size_t __i = 0; __i < __e.size(); ++__i) __e[__i] = __traits_.translate_nocase(__e[__i]);
            } else {
                for (size_t __i = 0; __i < __b.size(); ++__i) __b[__i] = __traits_.translate(__b[__i]);
                for (size_t __i = 0; __i < __e.size(); ++__i) __e[__i] = __traits_.translate(__e[__i]);
            }
            __ranges_.push_back(make_pair(__traits_.transform(__b.begin(), __b.end()), __traits_.transform(__e.begin(), __e.end())));
        } else {
            if (__b.size() != 1 || __e.size() != 1)
                __throw_regex_error<regex_constants::error_collate>();
            if (__icase_) {
                __b[0] = __traits_.translate_nocase(__b[0]);
                __e[0] = __traits_.translate_nocase(__e[0]);
            }
            __ranges_.push_back(make_pair(_VSTD::move(__b), _VSTD::move(__e)));
        }
    }

    void __add_digraph(_CharT __c1, _CharT __c2) {
        if (__icase_)
            __digraphs_.push_back(make_pair(__traits_.translate_nocase(__c1), __traits_.translate_nocase(__c2)));
        else if (__collate_)
            __digraphs_.push_back(make_pair(__traits_.translate(__c1), __traits_.translate(__c2)));
        else
            __digraphs_.push_back(make_pair(__c1, __c2));
    }

    void __add_equivalence(const string_type& __s) {
        __equivalences_.push_back(__s);
    }

    void __add_class(typename regex_traits<_CharT>::char_class_type __mask) {
        __mask_ |= __mask;
    }

    void __add_neg_class(typename regex_traits<_CharT>::char_class_type __mask) {
        __neg_mask_ |= __mask;
    }
};

template <class _CharT, class _Traits>
void __bracket_expression<_CharT, _Traits>::__exec(__state& __s) const {
    bool __found = false;
    unsigned __consumed = 0;
    if (__s.__current_ != __s.__last_) {
        ++__consumed;
        if (__might_have_digraph_) {
            const _CharT* __next = _VSTD::next(__s.__current_);
            if (__next != __s.__last_) {
                pair<_CharT, _CharT> __ch2(*__s.__current_, *__next);
                if (__icase_) {
                    __ch2.first = __traits_.translate_nocase(__ch2.first);
                    __ch2.second = __traits_.translate_nocase(__ch2.second);
                } else if (__collate_) {
                    __ch2.first = __traits_.translate(__ch2.first);
                    __ch2.second = __traits_.translate(__ch2.second);
                }
                if (!__traits_.lookup_collatename(&__ch2.first, &__ch2.first + 2).empty()) {
                    // __ch2 is a digraph in this locale
                    ++__consumed;
                    for (size_t __i = 0; __i < __digraphs_.size(); ++__i) {
                        if (__ch2 == __digraphs_[__i]) {
                            __found = true;
                            goto __exit;
                        }
                    }
                    if (__collate_ && !__ranges_.empty()) {
                        string_type __s2 = __traits_.transform(&__ch2.first, &__ch2.first + 2);
                        for (size_t __i = 0; __i < __ranges_.size(); ++__i) {
                            if (__ranges_[__i].first <= __s2 && __s2 <= __ranges_[__i].second) {
                                __found = true;
                                goto __exit;
                            }
                        }
                    }
                    if (!__equivalences_.empty()) {
                        string_type __s2 = __traits_.transform_primary(&__ch2.first, &__ch2.first + 2);
                        for (size_t __i = 0; __i < __equivalences_.size(); ++__i) {
                            if (__s2 == __equivalences_[__i]) {
                                __found = true;
                                goto __exit;
                            }
                        }
                    }
                    if (__traits_.isctype(__ch2.first, __mask_) && __traits_.isctype(__ch2.second, __mask_)) {
                        __found = true;
                        goto __exit;
                    }
                    if (!__traits_.isctype(__ch2.first, __neg_mask_) && !__traits_.isctype(__ch2.second, __neg_mask_)) {
                        __found = true;
                        goto __exit;
                    }
                    goto __exit;
                }
            }
        }
        // test *__s.__current_ as not a digraph
        _CharT __ch = *__s.__current_;
        if (__icase_)
            __ch = __traits_.translate_nocase(__ch);
        else if (__collate_)
            __ch = __traits_.translate(__ch);
        for (size_t __i = 0; __i < __chars_.size(); ++__i) {
            if (__ch == __chars_[__i]) {
                __found = true;
                goto __exit;
            }
        }
        // When there's at least one of __neg_chars_ and __neg_mask_, the set
        // of "__found" chars is
        //   union(complement(union(__neg_chars_, __neg_mask_)),
        //         other cases...)
        //
        // It doesn't make sense to check this when there are no __neg_chars_
        // and no __neg_mask_.
        if (!(__neg_mask_ == 0 && __neg_chars_.empty())) {
            const bool __in_neg_mask = __traits_.isctype(__ch, __neg_mask_);
            const bool __in_neg_chars = std::find(__neg_chars_.begin(), __neg_chars_.end(), __ch) != __neg_chars_.end();
            if (!(__in_neg_mask || __in_neg_chars)) {
                __found = true;
                goto __exit;
            }
        }
        if (!__ranges_.empty()) {
            string_type __s2 = __collate_ ? __traits_.transform(&__ch, &__ch + 1) : string_type(1, __ch);
            for (size_t __i = 0; __i < __ranges_.size(); ++__i) {
                if (__ranges_[__i].first <= __s2 && __s2 <= __ranges_[__i].second) {
                    __found = true;
                    goto __exit;
                }
            }
        }
        if (!__equivalences_.empty()) {
            string_type __s2 = __traits_.transform_primary(&__ch, &__ch + 1);
            for (size_t __i = 0; __i < __equivalences_.size(); ++__i) {
                if (__s2 == __equivalences_[__i]) {
                    __found = true;
                    goto __exit;
                }
            }
        }
        if (__traits_.isctype(__ch, __mask_)) {
            __found = true;
            goto __exit;
        }
    } else
        __found = __negate_;  // force reject
__exit:
    if (__found != __negate_) {
        __s.__do_ = __state::__accept_and_consume;
        __s.__current_ += __consumed;
        __s.__node_ = this->first();
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

template <class _CharT, class _Traits>
class __lookahead;

template <class _CharT, class _Traits = regex_traits<_CharT> >
class _LIBCPP_TEMPLATE_VIS basic_regex {
  public:
    // types:
    typedef _CharT value_type;
    typedef _Traits traits_type;
    typedef typename _Traits::string_type string_type;
    typedef regex_constants::syntax_option_type flag_type;
    typedef typename _Traits::locale_type locale_type;

  private:
    _Traits __traits_;
    flag_type __flags_;
    unsigned __marked_count_;
    unsigned __loop_count_;
    int __open_count_;
    shared_ptr<__empty_state<_CharT> > __start_;
    __owns_one_state<_CharT>* __end_;

    typedef _VSTD::__state<_CharT> __state;
    typedef _VSTD::__node<_CharT> __node;

  public:
    // constants:
    static const regex_constants::syntax_option_type icase = regex_constants::icase;
    static const regex_constants::syntax_option_type nosubs = regex_constants::nosubs;
    static const regex_constants::syntax_option_type optimize = regex_constants::optimize;
    static const regex_constants::syntax_option_type collate = regex_constants::collate;
    static const regex_constants::syntax_option_type ECMAScript = regex_constants::ECMAScript;
    static const regex_constants::syntax_option_type basic = regex_constants::basic;
    static const regex_constants::syntax_option_type extended = regex_constants::extended;
    static const regex_constants::syntax_option_type awk = regex_constants::awk;
    static const regex_constants::syntax_option_type grep = regex_constants::grep;
    static const regex_constants::syntax_option_type egrep = regex_constants::egrep;

    // construct/copy/destroy:

    basic_regex() : __flags_(), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
    }

    explicit basic_regex(const value_type* __p, flag_type __f = regex_constants::ECMAScript) : __flags_(__f), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
        __parse(__p, __p + __traits_.length(__p));
    }

    basic_regex(const value_type* __p, size_t __len, flag_type __f = regex_constants::ECMAScript) : __flags_(__f), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
        __parse(__p, __p + __len);
    }
    //     basic_regex(const basic_regex&) = default;
    //     basic_regex(basic_regex&&) = default;
    template <class _ST, class _SA>
    explicit basic_regex(const basic_string<value_type, _ST, _SA>& __p, flag_type __f = regex_constants::ECMAScript)
        : __flags_(__f), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
        __parse(__p.begin(), __p.end());
    }
    template <class _ForwardIterator>
    basic_regex(_ForwardIterator __first, _ForwardIterator __last, flag_type __f = regex_constants::ECMAScript) : __flags_(__f), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
        __parse(__first, __last);
    }
#ifndef _LIBCPP_CXX03_LANG

    basic_regex(initializer_list<value_type> __il, flag_type __f = regex_constants::ECMAScript) : __flags_(__f), __marked_count_(0), __loop_count_(0), __open_count_(0), __end_(0) {
        __parse(__il.begin(), __il.end());
    }
#endif  // _LIBCPP_CXX03_LANG

    //    ~basic_regex() = default;

    //     basic_regex& operator=(const basic_regex&) = default;
    //     basic_regex& operator=(basic_regex&&) = default;

    basic_regex& operator=(const value_type* __p) {
        return assign(__p);
    }
#ifndef _LIBCPP_CXX03_LANG

    basic_regex& operator=(initializer_list<value_type> __il) {
        return assign(__il);
    }
#endif  // _LIBCPP_CXX03_LANG
    template <class _ST, class _SA>
    basic_regex& operator=(const basic_string<value_type, _ST, _SA>& __p) {
        return assign(__p);
    }

    // assign:

    basic_regex& assign(const basic_regex& __that) {
        return *this = __that;
    }
#ifndef _LIBCPP_CXX03_LANG

    basic_regex& assign(basic_regex&& __that) _NOEXCEPT {
        return *this = _VSTD::move(__that);
    }
#endif

    basic_regex& assign(const value_type* __p, flag_type __f = regex_constants::ECMAScript) {
        return assign(__p, __p + __traits_.length(__p), __f);
    }

    basic_regex& assign(const value_type* __p, size_t __len, flag_type __f) {
        return assign(__p, __p + __len, __f);
    }
    template <class _ST, class _SA>
    basic_regex& assign(const basic_string<value_type, _ST, _SA>& __s, flag_type __f = regex_constants::ECMAScript) {
        return assign(__s.begin(), __s.end(), __f);
    }

    template <class _InputIterator>

    typename enable_if<__is_input_iterator<_InputIterator>::value && !__is_forward_iterator<_InputIterator>::value, basic_regex&>::type assign(_InputIterator __first, _InputIterator __last,
                                                                                                                                               flag_type __f = regex_constants::ECMAScript) {
        basic_string<_CharT> __t(__first, __last);
        return assign(__t.begin(), __t.end(), __f);
    }

  private:
    void __member_init(flag_type __f) {
        __flags_ = __f;
        __marked_count_ = 0;
        __loop_count_ = 0;
        __open_count_ = 0;
        __end_ = nullptr;
    }

  public:
    template <class _ForwardIterator>
    typename enable_if<__is_forward_iterator<_ForwardIterator>::value, basic_regex&>::type assign(_ForwardIterator __first, _ForwardIterator __last, flag_type __f = regex_constants::ECMAScript) {
        return assign(basic_regex(__first, __last, __f));
    }

#ifndef _LIBCPP_CXX03_LANG

    basic_regex& assign(initializer_list<value_type> __il, flag_type __f = regex_constants::ECMAScript) {
        return assign(__il.begin(), __il.end(), __f);
    }

#endif  // _LIBCPP_CXX03_LANG

    // const operations:

    unsigned mark_count() const {
        return __marked_count_;
    }

    flag_type flags() const {
        return __flags_;
    }

    // locale:

    locale_type imbue(locale_type __loc) {
        __member_init(ECMAScript);
        __start_.reset();
        return __traits_.imbue(__loc);
    }

    locale_type getloc() const {
        return __traits_.getloc();
    }

    // swap:
    void swap(basic_regex& __r);

  private:
    unsigned __loop_count() const {
        return __loop_count_;
    }

    template <class _ForwardIterator>
    _ForwardIterator __parse(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_basic_reg_exp(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_RE_expression(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_simple_RE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_nondupl_RE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_one_char_or_coll_elem_RE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_Back_open_paren(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_Back_close_paren(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_Back_open_brace(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_Back_close_brace(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_BACKREF(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ORD_CHAR(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_QUOTED_CHAR(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_RE_dupl_symbol(_ForwardIterator __first, _ForwardIterator __last, __owns_one_state<_CharT>* __s, unsigned __mexp_begin, unsigned __mexp_end);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ERE_dupl_symbol(_ForwardIterator __first, _ForwardIterator __last, __owns_one_state<_CharT>* __s, unsigned __mexp_begin, unsigned __mexp_end);
    template <class _ForwardIterator>
    _ForwardIterator __parse_bracket_expression(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_follow_list(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml);
    template <class _ForwardIterator>
    _ForwardIterator __parse_expression_term(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml);
    template <class _ForwardIterator>
    _ForwardIterator __parse_equivalence_class(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml);
    template <class _ForwardIterator>
    _ForwardIterator __parse_character_class(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml);
    template <class _ForwardIterator>
    _ForwardIterator __parse_collating_symbol(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>& __col_sym);
    template <class _ForwardIterator>
    _ForwardIterator __parse_DUP_COUNT(_ForwardIterator __first, _ForwardIterator __last, int& __c);
    template <class _ForwardIterator>
    _ForwardIterator __parse_extended_reg_exp(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ERE_branch(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ERE_expression(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_one_char_or_coll_elem_ERE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ORD_CHAR_ERE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_QUOTED_CHAR_ERE(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_ecma_exp(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_alternative(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_term(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_assertion(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_atom(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_atom_escape(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_decimal_escape(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_character_class_escape(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_character_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>* __str = nullptr);
    template <class _ForwardIterator>
    _ForwardIterator __parse_pattern_character(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_grep(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_egrep(_ForwardIterator __first, _ForwardIterator __last);
    template <class _ForwardIterator>
    _ForwardIterator __parse_class_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>& __str, __bracket_expression<_CharT, _Traits>* __ml);
    template <class _ForwardIterator>
    _ForwardIterator __parse_awk_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>* __str = nullptr);

    void __push_l_anchor();
    void __push_r_anchor();
    void __push_match_any();
    void __push_match_any_but_newline();

    void __push_greedy_inf_repeat(size_t __min, __owns_one_state<_CharT>* __s, unsigned __mexp_begin = 0, unsigned __mexp_end = 0) {
        __push_loop(__min, numeric_limits<size_t>::max(), __s, __mexp_begin, __mexp_end);
    }

    void __push_nongreedy_inf_repeat(size_t __min, __owns_one_state<_CharT>* __s, unsigned __mexp_begin = 0, unsigned __mexp_end = 0) {
        __push_loop(__min, numeric_limits<size_t>::max(), __s, __mexp_begin, __mexp_end, false);
    }
    void __push_loop(size_t __min, size_t __max, __owns_one_state<_CharT>* __s, size_t __mexp_begin = 0, size_t __mexp_end = 0, bool __greedy = true);
    __bracket_expression<_CharT, _Traits>* __start_matching_list(bool __negate);
    void __push_char(value_type __c);
    void __push_back_ref(int __i);
    void __push_alternation(__owns_one_state<_CharT>* __sa, __owns_one_state<_CharT>* __sb);
    void __push_begin_marked_subexpression();
    void __push_end_marked_subexpression(unsigned);
    void __push_empty();
    void __push_word_boundary(bool);
    void __push_lookahead(const basic_regex&, bool, unsigned);

    template <class _Allocator>
    bool __search(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags) const;

    template <class _Allocator>
    bool __match_at_start(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags, bool) const;
    template <class _Allocator>
    bool __match_at_start_ecma(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags, bool) const;
    template <class _Allocator>
    bool __match_at_start_posix_nosubs(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags, bool) const;
    template <class _Allocator>
    bool __match_at_start_posix_subs(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags, bool) const;

    template <class _Bp, class _Ap, class _Cp, class _Tp>
    friend bool regex_search(_Bp, _Bp, match_results<_Bp, _Ap>&, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _Ap, class _Cp, class _Tp>
    friend bool regex_search(const _Cp*, const _Cp*, match_results<const _Cp*, _Ap>&, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _Bp, class _Cp, class _Tp>
    friend bool regex_search(_Bp, _Bp, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _Cp, class _Tp>
    friend bool regex_search(const _Cp*, const _Cp*, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _Cp, class _Ap, class _Tp>
    friend bool regex_search(const _Cp*, match_results<const _Cp*, _Ap>&, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _ST, class _SA, class _Cp, class _Tp>
    friend bool regex_search(const basic_string<_Cp, _ST, _SA>& __s, const basic_regex<_Cp, _Tp>& __e, regex_constants::match_flag_type __flags);

    template <class _ST, class _SA, class _Ap, class _Cp, class _Tp>
    friend bool regex_search(const basic_string<_Cp, _ST, _SA>& __s, match_results<typename basic_string<_Cp, _ST, _SA>::const_iterator, _Ap>&, const basic_regex<_Cp, _Tp>& __e,
                             regex_constants::match_flag_type __flags);

    template <class _Iter, class _Ap, class _Cp, class _Tp>
    friend bool regex_search(__wrap_iter<_Iter> __first, __wrap_iter<_Iter> __last, match_results<__wrap_iter<_Iter>, _Ap>& __m, const basic_regex<_Cp, _Tp>& __e,
                             regex_constants::match_flag_type __flags);

    template <class, class>
    friend class __lookahead;
};

#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
template <class _ForwardIterator, class = typename enable_if<__is_forward_iterator<_ForwardIterator>::value, nullptr_t>::type>
basic_regex(_ForwardIterator, _ForwardIterator, regex_constants::syntax_option_type = regex_constants::ECMAScript)->basic_regex<typename iterator_traits<_ForwardIterator>::value_type>;
#endif

template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::icase;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::nosubs;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::optimize;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::collate;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::ECMAScript;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::basic;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::extended;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::awk;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::grep;
template <class _CharT, class _Traits>
const regex_constants::syntax_option_type basic_regex<_CharT, _Traits>::egrep;

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::swap(basic_regex& __r) {
    using _VSTD::swap;
    swap(__traits_, __r.__traits_);
    swap(__flags_, __r.__flags_);
    swap(__marked_count_, __r.__marked_count_);
    swap(__loop_count_, __r.__loop_count_);
    swap(__open_count_, __r.__open_count_);
    swap(__start_, __r.__start_);
    swap(__end_, __r.__end_);
}

template <class _CharT, class _Traits>
inline void swap(basic_regex<_CharT, _Traits>& __x, basic_regex<_CharT, _Traits>& __y) {
    return __x.swap(__y);
}

// __lookahead

template <class _CharT, class _Traits>
class __lookahead : public __owns_one_state<_CharT> {
    typedef __owns_one_state<_CharT> base;

    basic_regex<_CharT, _Traits> __exp_;
    unsigned __mexp_;
    bool __invert_;

    __lookahead(const __lookahead&);
    __lookahead& operator=(const __lookahead&);

  public:
    typedef _VSTD::__state<_CharT> __state;

    __lookahead(const basic_regex<_CharT, _Traits>& __exp, bool __invert, __node<_CharT>* __s, unsigned __mexp) : base(__s), __exp_(__exp), __mexp_(__mexp), __invert_(__invert) {
    }

    virtual void __exec(__state&) const;
};

template <class _CharT, class _Traits>
void __lookahead<_CharT, _Traits>::__exec(__state& __s) const {
    match_results<const _CharT*> __m;
    __m.__init(1 + __exp_.mark_count(), __s.__current_, __s.__last_);
    bool __matched = __exp_.__match_at_start_ecma(__s.__current_, __s.__last_, __m, (__s.__flags_ | regex_constants::match_continuous) & ~regex_constants::__full_match,
                                                  __s.__at_first_ && __s.__current_ == __s.__first_);
    if (__matched != __invert_) {
        __s.__do_ = __state::__accept_but_not_consume;
        __s.__node_ = this->first();
        for (unsigned __i = 1; __i < __m.size(); ++__i) {
            __s.__sub_matches_[__mexp_ + __i - 1] = __m.__matches_[__i];
        }
    } else {
        __s.__do_ = __state::__reject;
        __s.__node_ = nullptr;
    }
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse(_ForwardIterator __first, _ForwardIterator __last) {
    {
        unique_ptr<__node> __h(new __end_state<_CharT>);
        __start_.reset(new __empty_state<_CharT>(__h.get()));
        __h.release();
        __end_ = __start_.get();
    }
    switch (__flags_ & 0x1F0) {
        case ECMAScript:
            __first = __parse_ecma_exp(__first, __last);
            break;
        case basic:
            __first = __parse_basic_reg_exp(__first, __last);
            break;
        case extended:
        case awk:
            __first = __parse_extended_reg_exp(__first, __last);
            break;
        case grep:
            __first = __parse_grep(__first, __last);
            break;
        case egrep:
            __first = __parse_egrep(__first, __last);
            break;
        default:
            __throw_regex_error<regex_constants::__re_err_grammar>();
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_basic_reg_exp(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        if (*__first == '^') {
            __push_l_anchor();
            ++__first;
        }
        if (__first != __last) {
            __first = __parse_RE_expression(__first, __last);
            if (__first != __last) {
                _ForwardIterator __temp = _VSTD::next(__first);
                if (__temp == __last && *__first == '$') {
                    __push_r_anchor();
                    ++__first;
                }
            }
        }
        if (__first != __last)
            __throw_regex_error<regex_constants::__re_err_empty>();
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_extended_reg_exp(_ForwardIterator __first, _ForwardIterator __last) {
    __owns_one_state<_CharT>* __sa = __end_;
    _ForwardIterator __temp = __parse_ERE_branch(__first, __last);
    if (__temp == __first)
        __throw_regex_error<regex_constants::__re_err_empty>();
    __first = __temp;
    while (__first != __last && *__first == '|') {
        __owns_one_state<_CharT>* __sb = __end_;
        __temp = __parse_ERE_branch(++__first, __last);
        if (__temp == __first)
            __throw_regex_error<regex_constants::__re_err_empty>();
        __push_alternation(__sa, __sb);
        __first = __temp;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ERE_branch(_ForwardIterator __first, _ForwardIterator __last) {
    _ForwardIterator __temp = __parse_ERE_expression(__first, __last);
    if (__temp == __first)
        __throw_regex_error<regex_constants::__re_err_empty>();
    do {
        __first = __temp;
        __temp = __parse_ERE_expression(__first, __last);
    } while (__temp != __first);
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ERE_expression(_ForwardIterator __first, _ForwardIterator __last) {
    __owns_one_state<_CharT>* __e = __end_;
    unsigned __mexp_begin = __marked_count_;
    _ForwardIterator __temp = __parse_one_char_or_coll_elem_ERE(__first, __last);
    if (__temp == __first && __temp != __last) {
        switch (*__temp) {
            case '^':
                __push_l_anchor();
                ++__temp;
                break;
            case '$':
                __push_r_anchor();
                ++__temp;
                break;
            case '(':
                __push_begin_marked_subexpression();
                unsigned __temp_count = __marked_count_;
                ++__open_count_;
                __temp = __parse_extended_reg_exp(++__temp, __last);
                if (__temp == __last || *__temp != ')')
                    __throw_regex_error<regex_constants::error_paren>();
                __push_end_marked_subexpression(__temp_count);
                --__open_count_;
                ++__temp;
                break;
        }
    }
    if (__temp != __first)
        __temp = __parse_ERE_dupl_symbol(__temp, __last, __e, __mexp_begin + 1, __marked_count_ + 1);
    __first = __temp;
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_RE_expression(_ForwardIterator __first, _ForwardIterator __last) {
    while (true) {
        _ForwardIterator __temp = __parse_simple_RE(__first, __last);
        if (__temp == __first)
            break;
        __first = __temp;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_simple_RE(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        __owns_one_state<_CharT>* __e = __end_;
        unsigned __mexp_begin = __marked_count_;
        _ForwardIterator __temp = __parse_nondupl_RE(__first, __last);
        if (__temp != __first)
            __first = __parse_RE_dupl_symbol(__temp, __last, __e, __mexp_begin + 1, __marked_count_ + 1);
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_nondupl_RE(_ForwardIterator __first, _ForwardIterator __last) {
    _ForwardIterator __temp = __first;
    __first = __parse_one_char_or_coll_elem_RE(__first, __last);
    if (__temp == __first) {
        __temp = __parse_Back_open_paren(__first, __last);
        if (__temp != __first) {
            __push_begin_marked_subexpression();
            unsigned __temp_count = __marked_count_;
            __first = __parse_RE_expression(__temp, __last);
            __temp = __parse_Back_close_paren(__first, __last);
            if (__temp == __first)
                __throw_regex_error<regex_constants::error_paren>();
            __push_end_marked_subexpression(__temp_count);
            __first = __temp;
        } else
            __first = __parse_BACKREF(__first, __last);
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_one_char_or_coll_elem_RE(_ForwardIterator __first, _ForwardIterator __last) {
    _ForwardIterator __temp = __parse_ORD_CHAR(__first, __last);
    if (__temp == __first) {
        __temp = __parse_QUOTED_CHAR(__first, __last);
        if (__temp == __first) {
            if (__temp != __last && *__temp == '.') {
                __push_match_any();
                ++__temp;
            } else
                __temp = __parse_bracket_expression(__first, __last);
        }
    }
    __first = __temp;
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_one_char_or_coll_elem_ERE(_ForwardIterator __first, _ForwardIterator __last) {
    _ForwardIterator __temp = __parse_ORD_CHAR_ERE(__first, __last);
    if (__temp == __first) {
        __temp = __parse_QUOTED_CHAR_ERE(__first, __last);
        if (__temp == __first) {
            if (__temp != __last && *__temp == '.') {
                __push_match_any();
                ++__temp;
            } else
                __temp = __parse_bracket_expression(__first, __last);
        }
    }
    __first = __temp;
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_Back_open_paren(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\' && *__temp == '(')
                __first = ++__temp;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_Back_close_paren(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\' && *__temp == ')')
                __first = ++__temp;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_Back_open_brace(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\' && *__temp == '{')
                __first = ++__temp;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_Back_close_brace(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\' && *__temp == '}')
                __first = ++__temp;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_BACKREF(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\') {
                int __val = __traits_.value(*__temp, 10);
                if (__val >= 1 && __val <= 9) {
                    __push_back_ref(__val);
                    __first = ++__temp;
                }
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ORD_CHAR(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp == __last && *__first == '$')
            return __first;
        // Not called inside a bracket
        if (*__first == '.' || *__first == '\\' || *__first == '[')
            return __first;
        __push_char(*__first);
        ++__first;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ORD_CHAR_ERE(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        switch (*__first) {
            case '^':
            case '.':
            case '[':
            case '$':
            case '(':
            case '|':
            case '*':
            case '+':
            case '?':
            case '{':
            case '\\':
                break;
            case ')':
                if (__open_count_ == 0) {
                    __push_char(*__first);
                    ++__first;
                }
                break;
            default:
                __push_char(*__first);
                ++__first;
                break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_QUOTED_CHAR(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\') {
                switch (*__temp) {
                    case '^':
                    case '.':
                    case '*':
                    case '[':
                    case '$':
                    case '\\':
                        __push_char(*__temp);
                        __first = ++__temp;
                        break;
                }
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_QUOTED_CHAR_ERE(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        _ForwardIterator __temp = _VSTD::next(__first);
        if (__temp != __last) {
            if (*__first == '\\') {
                switch (*__temp) {
                    case '^':
                    case '.':
                    case '*':
                    case '[':
                    case '$':
                    case '\\':
                    case '(':
                    case ')':
                    case '|':
                    case '+':
                    case '?':
                    case '{':
                    case '}':
                        __push_char(*__temp);
                        __first = ++__temp;
                        break;
                    default:
                        if ((__flags_ & 0x1F0) == awk)
                            __first = __parse_awk_escape(++__first, __last);
                        break;
                }
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_RE_dupl_symbol(_ForwardIterator __first, _ForwardIterator __last, __owns_one_state<_CharT>* __s, unsigned __mexp_begin, unsigned __mexp_end) {
    if (__first != __last) {
        if (*__first == '*') {
            __push_greedy_inf_repeat(0, __s, __mexp_begin, __mexp_end);
            ++__first;
        } else {
            _ForwardIterator __temp = __parse_Back_open_brace(__first, __last);
            if (__temp != __first) {
                int __min = 0;
                __first = __temp;
                __temp = __parse_DUP_COUNT(__first, __last, __min);
                if (__temp == __first)
                    __throw_regex_error<regex_constants::error_badbrace>();
                __first = __temp;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_brace>();
                if (*__first != ',') {
                    __temp = __parse_Back_close_brace(__first, __last);
                    if (__temp == __first)
                        __throw_regex_error<regex_constants::error_brace>();
                    __push_loop(__min, __min, __s, __mexp_begin, __mexp_end, true);
                    __first = __temp;
                } else {
                    ++__first;  // consume ','
                    int __max = -1;
                    __first = __parse_DUP_COUNT(__first, __last, __max);
                    __temp = __parse_Back_close_brace(__first, __last);
                    if (__temp == __first)
                        __throw_regex_error<regex_constants::error_brace>();
                    if (__max == -1)
                        __push_greedy_inf_repeat(__min, __s, __mexp_begin, __mexp_end);
                    else {
                        if (__max < __min)
                            __throw_regex_error<regex_constants::error_badbrace>();
                        __push_loop(__min, __max, __s, __mexp_begin, __mexp_end, true);
                    }
                    __first = __temp;
                }
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ERE_dupl_symbol(_ForwardIterator __first, _ForwardIterator __last, __owns_one_state<_CharT>* __s, unsigned __mexp_begin, unsigned __mexp_end) {
    if (__first != __last) {
        unsigned __grammar = __flags_ & 0x1F0;
        switch (*__first) {
            case '*':
                ++__first;
                if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                    ++__first;
                    __push_nongreedy_inf_repeat(0, __s, __mexp_begin, __mexp_end);
                } else
                    __push_greedy_inf_repeat(0, __s, __mexp_begin, __mexp_end);
                break;
            case '+':
                ++__first;
                if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                    ++__first;
                    __push_nongreedy_inf_repeat(1, __s, __mexp_begin, __mexp_end);
                } else
                    __push_greedy_inf_repeat(1, __s, __mexp_begin, __mexp_end);
                break;
            case '?':
                ++__first;
                if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                    ++__first;
                    __push_loop(0, 1, __s, __mexp_begin, __mexp_end, false);
                } else
                    __push_loop(0, 1, __s, __mexp_begin, __mexp_end);
                break;
            case '{': {
                int __min;
                _ForwardIterator __temp = __parse_DUP_COUNT(++__first, __last, __min);
                if (__temp == __first)
                    __throw_regex_error<regex_constants::error_badbrace>();
                __first = __temp;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_brace>();
                switch (*__first) {
                    case '}':
                        ++__first;
                        if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                            ++__first;
                            __push_loop(__min, __min, __s, __mexp_begin, __mexp_end, false);
                        } else
                            __push_loop(__min, __min, __s, __mexp_begin, __mexp_end);
                        break;
                    case ',':
                        ++__first;
                        if (__first == __last)
                            __throw_regex_error<regex_constants::error_badbrace>();
                        if (*__first == '}') {
                            ++__first;
                            if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                                ++__first;
                                __push_nongreedy_inf_repeat(__min, __s, __mexp_begin, __mexp_end);
                            } else
                                __push_greedy_inf_repeat(__min, __s, __mexp_begin, __mexp_end);
                        } else {
                            int __max = -1;
                            __temp = __parse_DUP_COUNT(__first, __last, __max);
                            if (__temp == __first)
                                __throw_regex_error<regex_constants::error_brace>();
                            __first = __temp;
                            if (__first == __last || *__first != '}')
                                __throw_regex_error<regex_constants::error_brace>();
                            ++__first;
                            if (__max < __min)
                                __throw_regex_error<regex_constants::error_badbrace>();
                            if (__grammar == ECMAScript && __first != __last && *__first == '?') {
                                ++__first;
                                __push_loop(__min, __max, __s, __mexp_begin, __mexp_end, false);
                            } else
                                __push_loop(__min, __max, __s, __mexp_begin, __mexp_end);
                        }
                        break;
                    default:
                        __throw_regex_error<regex_constants::error_badbrace>();
                }
            } break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_bracket_expression(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last && *__first == '[') {
        ++__first;
        if (__first == __last)
            __throw_regex_error<regex_constants::error_brack>();
        bool __negate = false;
        if (*__first == '^') {
            ++__first;
            __negate = true;
        }
        __bracket_expression<_CharT, _Traits>* __ml = __start_matching_list(__negate);
        // __ml owned by *this
        if (__first == __last)
            __throw_regex_error<regex_constants::error_brack>();
        if ((__flags_ & 0x1F0) != ECMAScript && *__first == ']') {
            __ml->__add_char(']');
            ++__first;
        }
        __first = __parse_follow_list(__first, __last, __ml);
        if (__first == __last)
            __throw_regex_error<regex_constants::error_brack>();
        if (*__first == '-') {
            __ml->__add_char('-');
            ++__first;
        }
        if (__first == __last || *__first != ']')
            __throw_regex_error<regex_constants::error_brack>();
        ++__first;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_follow_list(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml) {
    if (__first != __last) {
        while (true) {
            _ForwardIterator __temp = __parse_expression_term(__first, __last, __ml);
            if (__temp == __first)
                break;
            __first = __temp;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_expression_term(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml) {
    if (__first != __last && *__first != ']') {
        _ForwardIterator __temp = _VSTD::next(__first);
        basic_string<_CharT> __start_range;
        if (__temp != __last && *__first == '[') {
            if (*__temp == '=')
                return __parse_equivalence_class(++__temp, __last, __ml);
            else if (*__temp == ':')
                return __parse_character_class(++__temp, __last, __ml);
            else if (*__temp == '.')
                __first = __parse_collating_symbol(++__temp, __last, __start_range);
        }
        unsigned __grammar = __flags_ & 0x1F0;
        if (__start_range.empty()) {
            if ((__grammar == ECMAScript || __grammar == awk) && *__first == '\\') {
                if (__grammar == ECMAScript)
                    __first = __parse_class_escape(++__first, __last, __start_range, __ml);
                else
                    __first = __parse_awk_escape(++__first, __last, &__start_range);
            } else {
                __start_range = *__first;
                ++__first;
            }
        }
        if (__first != __last && *__first != ']') {
            __temp = _VSTD::next(__first);
            if (__temp != __last && *__first == '-' && *__temp != ']') {
                // parse a range
                basic_string<_CharT> __end_range;
                __first = __temp;
                ++__temp;
                if (__temp != __last && *__first == '[' && *__temp == '.')
                    __first = __parse_collating_symbol(++__temp, __last, __end_range);
                else {
                    if ((__grammar == ECMAScript || __grammar == awk) && *__first == '\\') {
                        if (__grammar == ECMAScript)
                            __first = __parse_class_escape(++__first, __last, __end_range, __ml);
                        else
                            __first = __parse_awk_escape(++__first, __last, &__end_range);
                    } else {
                        __end_range = *__first;
                        ++__first;
                    }
                }
                __ml->__add_range(_VSTD::move(__start_range), _VSTD::move(__end_range));
            } else if (!__start_range.empty()) {
                if (__start_range.size() == 1)
                    __ml->__add_char(__start_range[0]);
                else
                    __ml->__add_digraph(__start_range[0], __start_range[1]);
            }
        } else if (!__start_range.empty()) {
            if (__start_range.size() == 1)
                __ml->__add_char(__start_range[0]);
            else
                __ml->__add_digraph(__start_range[0], __start_range[1]);
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_class_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>& __str, __bracket_expression<_CharT, _Traits>* __ml) {
    if (__first == __last)
        __throw_regex_error<regex_constants::error_escape>();
    switch (*__first) {
        case 0:
            __str = *__first;
            return ++__first;
        case 'b':
            __str = _CharT(8);
            return ++__first;
        case 'd':
            __ml->__add_class(ctype_base::digit);
            return ++__first;
        case 'D':
            __ml->__add_neg_class(ctype_base::digit);
            return ++__first;
        case 's':
            __ml->__add_class(ctype_base::space);
            return ++__first;
        case 'S':
            __ml->__add_neg_class(ctype_base::space);
            return ++__first;
        case 'w':
            __ml->__add_class(ctype_base::alnum);
            __ml->__add_char('_');
            return ++__first;
        case 'W':
            __ml->__add_neg_class(ctype_base::alnum);
            __ml->__add_neg_char('_');
            return ++__first;
    }
    __first = __parse_character_escape(__first, __last, &__str);
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_awk_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>* __str) {
    if (__first == __last)
        __throw_regex_error<regex_constants::error_escape>();
    switch (*__first) {
        case '\\':
        case '"':
        case '/':
            if (__str)
                *__str = *__first;
            else
                __push_char(*__first);
            return ++__first;
        case 'a':
            if (__str)
                *__str = _CharT(7);
            else
                __push_char(_CharT(7));
            return ++__first;
        case 'b':
            if (__str)
                *__str = _CharT(8);
            else
                __push_char(_CharT(8));
            return ++__first;
        case 'f':
            if (__str)
                *__str = _CharT(0xC);
            else
                __push_char(_CharT(0xC));
            return ++__first;
        case 'n':
            if (__str)
                *__str = _CharT(0xA);
            else
                __push_char(_CharT(0xA));
            return ++__first;
        case 'r':
            if (__str)
                *__str = _CharT(0xD);
            else
                __push_char(_CharT(0xD));
            return ++__first;
        case 't':
            if (__str)
                *__str = _CharT(0x9);
            else
                __push_char(_CharT(0x9));
            return ++__first;
        case 'v':
            if (__str)
                *__str = _CharT(0xB);
            else
                __push_char(_CharT(0xB));
            return ++__first;
    }
    if ('0' <= *__first && *__first <= '7') {
        unsigned __val = *__first - '0';
        if (++__first != __last && ('0' <= *__first && *__first <= '7')) {
            __val = 8 * __val + *__first - '0';
            if (++__first != __last && ('0' <= *__first && *__first <= '7'))
                __val = 8 * __val + *__first++ - '0';
        }
        if (__str)
            *__str = _CharT(__val);
        else
            __push_char(_CharT(__val));
    } else
        __throw_regex_error<regex_constants::error_escape>();
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_equivalence_class(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml) {
    // Found [=
    //   This means =] must exist
    value_type _Equal_close[2] = {'=', ']'};
    _ForwardIterator __temp = _VSTD::search(__first, __last, _Equal_close, _Equal_close + 2);
    if (__temp == __last)
        __throw_regex_error<regex_constants::error_brack>();
    // [__first, __temp) contains all text in [= ... =]
    string_type __collate_name = __traits_.lookup_collatename(__first, __temp);
    if (__collate_name.empty())
        __throw_regex_error<regex_constants::error_collate>();
    string_type __equiv_name = __traits_.transform_primary(__collate_name.begin(), __collate_name.end());
    if (!__equiv_name.empty())
        __ml->__add_equivalence(__equiv_name);
    else {
        switch (__collate_name.size()) {
            case 1:
                __ml->__add_char(__collate_name[0]);
                break;
            case 2:
                __ml->__add_digraph(__collate_name[0], __collate_name[1]);
                break;
            default:
                __throw_regex_error<regex_constants::error_collate>();
        }
    }
    __first = _VSTD::next(__temp, 2);
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_character_class(_ForwardIterator __first, _ForwardIterator __last, __bracket_expression<_CharT, _Traits>* __ml) {
    // Found [:
    //   This means :] must exist
    value_type _Colon_close[2] = {':', ']'};
    _ForwardIterator __temp = _VSTD::search(__first, __last, _Colon_close, _Colon_close + 2);
    if (__temp == __last)
        __throw_regex_error<regex_constants::error_brack>();
    // [__first, __temp) contains all text in [: ... :]
    typedef typename _Traits::char_class_type char_class_type;
    char_class_type __class_type = __traits_.lookup_classname(__first, __temp, __flags_ & icase);
    if (__class_type == 0)
        __throw_regex_error<regex_constants::error_ctype>();
    __ml->__add_class(__class_type);
    __first = _VSTD::next(__temp, 2);
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_collating_symbol(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>& __col_sym) {
    // Found [.
    //   This means .] must exist
    value_type _Dot_close[2] = {'.', ']'};
    _ForwardIterator __temp = _VSTD::search(__first, __last, _Dot_close, _Dot_close + 2);
    if (__temp == __last)
        __throw_regex_error<regex_constants::error_brack>();
    // [__first, __temp) contains all text in [. ... .]
    __col_sym = __traits_.lookup_collatename(__first, __temp);
    switch (__col_sym.size()) {
        case 1:
        case 2:
            break;
        default:
            __throw_regex_error<regex_constants::error_collate>();
    }
    __first = _VSTD::next(__temp, 2);
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_DUP_COUNT(_ForwardIterator __first, _ForwardIterator __last, int& __c) {
    if (__first != __last) {
        int __val = __traits_.value(*__first, 10);
        if (__val != -1) {
            __c = __val;
            for (++__first; __first != __last && (__val = __traits_.value(*__first, 10)) != -1; ++__first) {
                if (__c >= std::numeric_limits<int>::max() / 10)
                    __throw_regex_error<regex_constants::error_badbrace>();
                __c *= 10;
                __c += __val;
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_ecma_exp(_ForwardIterator __first, _ForwardIterator __last) {
    __owns_one_state<_CharT>* __sa = __end_;
    _ForwardIterator __temp = __parse_alternative(__first, __last);
    if (__temp == __first)
        __push_empty();
    __first = __temp;
    while (__first != __last && *__first == '|') {
        __owns_one_state<_CharT>* __sb = __end_;
        __temp = __parse_alternative(++__first, __last);
        if (__temp == __first)
            __push_empty();
        __push_alternation(__sa, __sb);
        __first = __temp;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_alternative(_ForwardIterator __first, _ForwardIterator __last) {
    while (true) {
        _ForwardIterator __temp = __parse_term(__first, __last);
        if (__temp == __first)
            break;
        __first = __temp;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_term(_ForwardIterator __first, _ForwardIterator __last) {
    _ForwardIterator __temp = __parse_assertion(__first, __last);
    if (__temp == __first) {
        __owns_one_state<_CharT>* __e = __end_;
        unsigned __mexp_begin = __marked_count_;
        __temp = __parse_atom(__first, __last);
        if (__temp != __first)
            __first = __parse_ERE_dupl_symbol(__temp, __last, __e, __mexp_begin + 1, __marked_count_ + 1);
    } else
        __first = __temp;
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_assertion(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        switch (*__first) {
            case '^':
                __push_l_anchor();
                ++__first;
                break;
            case '$':
                __push_r_anchor();
                ++__first;
                break;
            case '\\': {
                _ForwardIterator __temp = _VSTD::next(__first);
                if (__temp != __last) {
                    if (*__temp == 'b') {
                        __push_word_boundary(false);
                        __first = ++__temp;
                    } else if (*__temp == 'B') {
                        __push_word_boundary(true);
                        __first = ++__temp;
                    }
                }
            } break;
            case '(': {
                _ForwardIterator __temp = _VSTD::next(__first);
                if (__temp != __last && *__temp == '?') {
                    if (++__temp != __last) {
                        switch (*__temp) {
                            case '=': {
                                basic_regex __exp;
                                __exp.__flags_ = __flags_;
                                __temp = __exp.__parse(++__temp, __last);
                                unsigned __mexp = __exp.__marked_count_;
                                __push_lookahead(_VSTD::move(__exp), false, __marked_count_);
                                __marked_count_ += __mexp;
                                if (__temp == __last || *__temp != ')')
                                    __throw_regex_error<regex_constants::error_paren>();
                                __first = ++__temp;
                            } break;
                            case '!': {
                                basic_regex __exp;
                                __exp.__flags_ = __flags_;
                                __temp = __exp.__parse(++__temp, __last);
                                unsigned __mexp = __exp.__marked_count_;
                                __push_lookahead(_VSTD::move(__exp), true, __marked_count_);
                                __marked_count_ += __mexp;
                                if (__temp == __last || *__temp != ')')
                                    __throw_regex_error<regex_constants::error_paren>();
                                __first = ++__temp;
                            } break;
                        }
                    }
                }
            } break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_atom(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        switch (*__first) {
            case '.':
                __push_match_any_but_newline();
                ++__first;
                break;
            case '\\':
                __first = __parse_atom_escape(__first, __last);
                break;
            case '[':
                __first = __parse_bracket_expression(__first, __last);
                break;
            case '(': {
                ++__first;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_paren>();
                _ForwardIterator __temp = _VSTD::next(__first);
                if (__temp != __last && *__first == '?' && *__temp == ':') {
                    ++__open_count_;
                    __first = __parse_ecma_exp(++__temp, __last);
                    if (__first == __last || *__first != ')')
                        __throw_regex_error<regex_constants::error_paren>();
                    --__open_count_;
                    ++__first;
                } else {
                    __push_begin_marked_subexpression();
                    unsigned __temp_count = __marked_count_;
                    ++__open_count_;
                    __first = __parse_ecma_exp(__first, __last);
                    if (__first == __last || *__first != ')')
                        __throw_regex_error<regex_constants::error_paren>();
                    __push_end_marked_subexpression(__temp_count);
                    --__open_count_;
                    ++__first;
                }
            } break;
            case '*':
            case '+':
            case '?':
            case '{':
                __throw_regex_error<regex_constants::error_badrepeat>();
                break;
            default:
                __first = __parse_pattern_character(__first, __last);
                break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_atom_escape(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last && *__first == '\\') {
        _ForwardIterator __t1 = _VSTD::next(__first);
        if (__t1 == __last)
            __throw_regex_error<regex_constants::error_escape>();

        _ForwardIterator __t2 = __parse_decimal_escape(__t1, __last);
        if (__t2 != __t1)
            __first = __t2;
        else {
            __t2 = __parse_character_class_escape(__t1, __last);
            if (__t2 != __t1)
                __first = __t2;
            else {
                __t2 = __parse_character_escape(__t1, __last);
                if (__t2 != __t1)
                    __first = __t2;
            }
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_decimal_escape(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        if (*__first == '0') {
            __push_char(_CharT());
            ++__first;
        } else if ('1' <= *__first && *__first <= '9') {
            unsigned __v = *__first - '0';
            for (++__first; __first != __last && '0' <= *__first && *__first <= '9'; ++__first) {
                if (__v >= std::numeric_limits<unsigned>::max() / 10)
                    __throw_regex_error<regex_constants::error_backref>();
                __v = 10 * __v + *__first - '0';
            }
            if (__v == 0 || __v > mark_count())
                __throw_regex_error<regex_constants::error_backref>();
            __push_back_ref(__v);
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_character_class_escape(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        __bracket_expression<_CharT, _Traits>* __ml;
        switch (*__first) {
            case 'd':
                __ml = __start_matching_list(false);
                __ml->__add_class(ctype_base::digit);
                ++__first;
                break;
            case 'D':
                __ml = __start_matching_list(true);
                __ml->__add_class(ctype_base::digit);
                ++__first;
                break;
            case 's':
                __ml = __start_matching_list(false);
                __ml->__add_class(ctype_base::space);
                ++__first;
                break;
            case 'S':
                __ml = __start_matching_list(true);
                __ml->__add_class(ctype_base::space);
                ++__first;
                break;
            case 'w':
                __ml = __start_matching_list(false);
                __ml->__add_class(ctype_base::alnum);
                __ml->__add_char('_');
                ++__first;
                break;
            case 'W':
                __ml = __start_matching_list(true);
                __ml->__add_class(ctype_base::alnum);
                __ml->__add_char('_');
                ++__first;
                break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_character_escape(_ForwardIterator __first, _ForwardIterator __last, basic_string<_CharT>* __str) {
    if (__first != __last) {
        _ForwardIterator __t;
        unsigned __sum = 0;
        int __hd;
        switch (*__first) {
            case 'f':
                if (__str)
                    *__str = _CharT(0xC);
                else
                    __push_char(_CharT(0xC));
                ++__first;
                break;
            case 'n':
                if (__str)
                    *__str = _CharT(0xA);
                else
                    __push_char(_CharT(0xA));
                ++__first;
                break;
            case 'r':
                if (__str)
                    *__str = _CharT(0xD);
                else
                    __push_char(_CharT(0xD));
                ++__first;
                break;
            case 't':
                if (__str)
                    *__str = _CharT(0x9);
                else
                    __push_char(_CharT(0x9));
                ++__first;
                break;
            case 'v':
                if (__str)
                    *__str = _CharT(0xB);
                else
                    __push_char(_CharT(0xB));
                ++__first;
                break;
            case 'c':
                if ((__t = _VSTD::next(__first)) != __last) {
                    if (('A' <= *__t && *__t <= 'Z') || ('a' <= *__t && *__t <= 'z')) {
                        if (__str)
                            *__str = _CharT(*__t % 32);
                        else
                            __push_char(_CharT(*__t % 32));
                        __first = ++__t;
                    } else
                        __throw_regex_error<regex_constants::error_escape>();
                } else
                    __throw_regex_error<regex_constants::error_escape>();
                break;
            case 'u':
                ++__first;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_escape>();
                __hd = __traits_.value(*__first, 16);
                if (__hd == -1)
                    __throw_regex_error<regex_constants::error_escape>();
                __sum = 16 * __sum + static_cast<unsigned>(__hd);
                ++__first;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_escape>();
                __hd = __traits_.value(*__first, 16);
                if (__hd == -1)
                    __throw_regex_error<regex_constants::error_escape>();
                __sum = 16 * __sum + static_cast<unsigned>(__hd);
                // drop through
            case 'x':
                ++__first;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_escape>();
                __hd = __traits_.value(*__first, 16);
                if (__hd == -1)
                    __throw_regex_error<regex_constants::error_escape>();
                __sum = 16 * __sum + static_cast<unsigned>(__hd);
                ++__first;
                if (__first == __last)
                    __throw_regex_error<regex_constants::error_escape>();
                __hd = __traits_.value(*__first, 16);
                if (__hd == -1)
                    __throw_regex_error<regex_constants::error_escape>();
                __sum = 16 * __sum + static_cast<unsigned>(__hd);
                if (__str)
                    *__str = _CharT(__sum);
                else
                    __push_char(_CharT(__sum));
                ++__first;
                break;
            case '0':
                if (__str)
                    *__str = _CharT(0);
                else
                    __push_char(_CharT(0));
                ++__first;
                break;
            default:
                if (*__first != '_' && !__traits_.isctype(*__first, ctype_base::alnum)) {
                    if (__str)
                        *__str = *__first;
                    else
                        __push_char(*__first);
                    ++__first;
                } else
                    __throw_regex_error<regex_constants::error_escape>();
                break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_pattern_character(_ForwardIterator __first, _ForwardIterator __last) {
    if (__first != __last) {
        switch (*__first) {
            case '^':
            case '$':
            case '\\':
            case '.':
            case '*':
            case '+':
            case '?':
            case '(':
            case ')':
            case '[':
            case ']':
            case '{':
            case '}':
            case '|':
                break;
            default:
                __push_char(*__first);
                ++__first;
                break;
        }
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_grep(_ForwardIterator __first, _ForwardIterator __last) {
    __owns_one_state<_CharT>* __sa = __end_;
    _ForwardIterator __t1 = _VSTD::find(__first, __last, _CharT('\n'));
    if (__t1 != __first)
        __parse_basic_reg_exp(__first, __t1);
    else
        __push_empty();
    __first = __t1;
    if (__first != __last)
        ++__first;
    while (__first != __last) {
        __t1 = _VSTD::find(__first, __last, _CharT('\n'));
        __owns_one_state<_CharT>* __sb = __end_;
        if (__t1 != __first)
            __parse_basic_reg_exp(__first, __t1);
        else
            __push_empty();
        __push_alternation(__sa, __sb);
        __first = __t1;
        if (__first != __last)
            ++__first;
    }
    return __first;
}

template <class _CharT, class _Traits>
template <class _ForwardIterator>
_ForwardIterator basic_regex<_CharT, _Traits>::__parse_egrep(_ForwardIterator __first, _ForwardIterator __last) {
    __owns_one_state<_CharT>* __sa = __end_;
    _ForwardIterator __t1 = _VSTD::find(__first, __last, _CharT('\n'));
    if (__t1 != __first)
        __parse_extended_reg_exp(__first, __t1);
    else
        __push_empty();
    __first = __t1;
    if (__first != __last)
        ++__first;
    while (__first != __last) {
        __t1 = _VSTD::find(__first, __last, _CharT('\n'));
        __owns_one_state<_CharT>* __sb = __end_;
        if (__t1 != __first)
            __parse_extended_reg_exp(__first, __t1);
        else
            __push_empty();
        __push_alternation(__sa, __sb);
        __first = __t1;
        if (__first != __last)
            ++__first;
    }
    return __first;
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_loop(size_t __min, size_t __max, __owns_one_state<_CharT>* __s, size_t __mexp_begin, size_t __mexp_end, bool __greedy) {
    unique_ptr<__empty_state<_CharT> > __e1(new __empty_state<_CharT>(__end_->first()));
    __end_->first() = nullptr;
    unique_ptr<__loop<_CharT> > __e2(new __loop<_CharT>(__loop_count_, __s->first(), __e1.get(), __mexp_begin, __mexp_end, __greedy, __min, __max));
    __s->first() = nullptr;
    __e1.release();
    __end_->first() = new __repeat_one_loop<_CharT>(__e2.get());
    __end_ = __e2->second();
    __s->first() = __e2.release();
    ++__loop_count_;
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_char(value_type __c) {
    if (flags() & icase)
        __end_->first() = new __match_char_icase<_CharT, _Traits>(__traits_, __c, __end_->first());
    else if (flags() & collate)
        __end_->first() = new __match_char_collate<_CharT, _Traits>(__traits_, __c, __end_->first());
    else
        __end_->first() = new __match_char<_CharT>(__c, __end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_begin_marked_subexpression() {
    if (!(__flags_ & nosubs)) {
        __end_->first() = new __begin_marked_subexpression<_CharT>(++__marked_count_, __end_->first());
        __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
    }
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_end_marked_subexpression(unsigned __sub) {
    if (!(__flags_ & nosubs)) {
        __end_->first() = new __end_marked_subexpression<_CharT>(__sub, __end_->first());
        __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
    }
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_l_anchor() {
    __end_->first() = new __l_anchor<_CharT>(__end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_r_anchor() {
    __end_->first() = new __r_anchor<_CharT>(__end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_match_any() {
    __end_->first() = new __match_any<_CharT>(__end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_match_any_but_newline() {
    __end_->first() = new __match_any_but_newline<_CharT>(__end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_empty() {
    __end_->first() = new __empty_state<_CharT>(__end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_word_boundary(bool __invert) {
    __end_->first() = new __word_boundary<_CharT, _Traits>(__traits_, __invert, __end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_back_ref(int __i) {
    if (flags() & icase)
        __end_->first() = new __back_ref_icase<_CharT, _Traits>(__traits_, __i, __end_->first());
    else if (flags() & collate)
        __end_->first() = new __back_ref_collate<_CharT, _Traits>(__traits_, __i, __end_->first());
    else
        __end_->first() = new __back_ref<_CharT>(__i, __end_->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_alternation(__owns_one_state<_CharT>* __sa, __owns_one_state<_CharT>* __ea) {
    __sa->first() = new __alternate<_CharT>(static_cast<__owns_one_state<_CharT>*>(__sa->first()), static_cast<__owns_one_state<_CharT>*>(__ea->first()));
    __ea->first() = nullptr;
    __ea->first() = new __empty_state<_CharT>(__end_->first());
    __end_->first() = nullptr;
    __end_->first() = new __empty_non_own_state<_CharT>(__ea->first());
    __end_ = static_cast<__owns_one_state<_CharT>*>(__ea->first());
}

template <class _CharT, class _Traits>
__bracket_expression<_CharT, _Traits>* basic_regex<_CharT, _Traits>::__start_matching_list(bool __negate) {
    __bracket_expression<_CharT, _Traits>* __r = new __bracket_expression<_CharT, _Traits>(__traits_, __end_->first(), __negate, __flags_ & icase, __flags_ & collate);
    __end_->first() = __r;
    __end_ = __r;
    return __r;
}

template <class _CharT, class _Traits>
void basic_regex<_CharT, _Traits>::__push_lookahead(const basic_regex& __exp, bool __invert, unsigned __mexp) {
    __end_->first() = new __lookahead<_CharT, _Traits>(__exp, __invert, __end_->first(), __mexp);
    __end_ = static_cast<__owns_one_state<_CharT>*>(__end_->first());
}

typedef basic_regex<char> regex;
typedef basic_regex<wchar_t> wregex;

// sub_match

template <class _BidirectionalIterator>
class _LIBCPP_TEMPLATE_VIS sub_match : public pair<_BidirectionalIterator, _BidirectionalIterator> {
  public:
    typedef _BidirectionalIterator iterator;
    typedef typename iterator_traits<iterator>::value_type value_type;
    typedef typename iterator_traits<iterator>::difference_type difference_type;
    typedef basic_string<value_type> string_type;

    bool matched;

    _LIBCPP_CONSTEXPR sub_match() : matched() {
    }

    difference_type length() const {
        return matched ? _VSTD::distance(this->first, this->second) : 0;
    }

    string_type str() const {
        return matched ? string_type(this->first, this->second) : string_type();
    }

    operator string_type() const {
        return str();
    }

    int compare(const sub_match& __s) const {
        return str().compare(__s.str());
    }

    int compare(const string_type& __s) const {
        return str().compare(__s);
    }

    int compare(const value_type* __s) const {
        return str().compare(__s);
    }
};

typedef sub_match<const char*> csub_match;
typedef sub_match<const wchar_t*> wcsub_match;
typedef sub_match<string::const_iterator> ssub_match;
typedef sub_match<wstring::const_iterator> wssub_match;

template <class _BiIter>
inline bool operator==(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return __x.compare(__y) == 0;
}

template <class _BiIter>
inline bool operator!=(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return !(__x == __y);
}

template <class _BiIter>
inline bool operator<(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return __x.compare(__y) < 0;
}

template <class _BiIter>
inline bool operator<=(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return !(__y < __x);
}

template <class _BiIter>
inline bool operator>=(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return !(__x < __y);
}

template <class _BiIter>
inline bool operator>(const sub_match<_BiIter>& __x, const sub_match<_BiIter>& __y) {
    return __y < __x;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator==(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return __y.compare(typename sub_match<_BiIter>::string_type(__x.data(), __x.size())) == 0;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator!=(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return !(__x == __y);
}

template <class _BiIter, class _ST, class _SA>
inline bool operator<(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return __y.compare(typename sub_match<_BiIter>::string_type(__x.data(), __x.size())) > 0;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator>(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return __y < __x;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator>=(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return !(__x < __y);
}

template <class _BiIter, class _ST, class _SA>
inline bool operator<=(const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __x, const sub_match<_BiIter>& __y) {
    return !(__y < __x);
}

template <class _BiIter, class _ST, class _SA>
inline bool operator==(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return __x.compare(typename sub_match<_BiIter>::string_type(__y.data(), __y.size())) == 0;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator!=(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return !(__x == __y);
}

template <class _BiIter, class _ST, class _SA>
inline bool operator<(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return __x.compare(typename sub_match<_BiIter>::string_type(__y.data(), __y.size())) < 0;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator>(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return __y < __x;
}

template <class _BiIter, class _ST, class _SA>
inline bool operator>=(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return !(__x < __y);
}

template <class _BiIter, class _ST, class _SA>
inline bool operator<=(const sub_match<_BiIter>& __x, const basic_string<typename iterator_traits<_BiIter>::value_type, _ST, _SA>& __y) {
    return !(__y < __x);
}

template <class _BiIter>
inline bool operator==(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return __y.compare(__x) == 0;
}

template <class _BiIter>
inline bool operator!=(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return !(__x == __y);
}

template <class _BiIter>
inline bool operator<(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return __y.compare(__x) > 0;
}

template <class _BiIter>
inline bool operator>(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return __y < __x;
}

template <class _BiIter>
inline bool operator>=(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return !(__x < __y);
}

template <class _BiIter>
inline bool operator<=(typename iterator_traits<_BiIter>::value_type const* __x, const sub_match<_BiIter>& __y) {
    return !(__y < __x);
}

template <class _BiIter>
inline bool operator==(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return __x.compare(__y) == 0;
}

template <class _BiIter>
inline bool operator!=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return !(__x == __y);
}

template <class _BiIter>
inline bool operator<(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return __x.compare(__y) < 0;
}

template <class _BiIter>
inline bool operator>(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return __y < __x;
}

template <class _BiIter>
inline bool operator>=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return !(__x < __y);
}

template <class _BiIter>
inline bool operator<=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const* __y) {
    return !(__y < __x);
}

template <class _BiIter>
inline bool operator==(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    typedef basic_string<typename iterator_traits<_BiIter>::value_type> string_type;
    return __y.compare(string_type(1, __x)) == 0;
}

template <class _BiIter>
inline bool operator!=(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    return !(__x == __y);
}

template <class _BiIter>
inline bool operator<(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    typedef basic_string<typename iterator_traits<_BiIter>::value_type> string_type;
    return __y.compare(string_type(1, __x)) > 0;
}

template <class _BiIter>
inline bool operator>(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    return __y < __x;
}

template <class _BiIter>
inline bool operator>=(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    return !(__x < __y);
}

template <class _BiIter>
inline bool operator<=(typename iterator_traits<_BiIter>::value_type const& __x, const sub_match<_BiIter>& __y) {
    return !(__y < __x);
}

template <class _BiIter>
inline bool operator==(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    typedef basic_string<typename iterator_traits<_BiIter>::value_type> string_type;
    return __x.compare(string_type(1, __y)) == 0;
}

template <class _BiIter>
inline bool operator!=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    return !(__x == __y);
}

template <class _BiIter>
inline bool operator<(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    typedef basic_string<typename iterator_traits<_BiIter>::value_type> string_type;
    return __x.compare(string_type(1, __y)) < 0;
}

template <class _BiIter>
inline bool operator>(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    return __y < __x;
}

template <class _BiIter>
inline bool operator>=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    return !(__x < __y);
}

template <class _BiIter>
inline bool operator<=(const sub_match<_BiIter>& __x, typename iterator_traits<_BiIter>::value_type const& __y) {
    return !(__y < __x);
}

template <class _CharT, class _ST, class _BiIter>
inline basic_ostream<_CharT, _ST>& operator<<(basic_ostream<_CharT, _ST>& __os, const sub_match<_BiIter>& __m) {
    return __os << __m.str();
}

template <class _BidirectionalIterator, class _Allocator>
class _LIBCPP_TEMPLATE_VIS match_results {
  public:
    typedef _Allocator allocator_type;
    typedef sub_match<_BidirectionalIterator> value_type;

  private:
    typedef vector<value_type, allocator_type> __container_type;

    __container_type __matches_;
    value_type __unmatched_;
    value_type __prefix_;
    value_type __suffix_;
    bool __ready_;

  public:
    _BidirectionalIterator __position_start_;
    typedef const value_type& const_reference;
    typedef value_type& reference;
    typedef typename __container_type::const_iterator const_iterator;
    typedef const_iterator iterator;
    typedef typename iterator_traits<_BidirectionalIterator>::difference_type difference_type;
    typedef typename allocator_traits<allocator_type>::size_type size_type;
    typedef typename iterator_traits<_BidirectionalIterator>::value_type char_type;
    typedef basic_string<char_type> string_type;

    // construct/copy/destroy:
    explicit match_results(const allocator_type& __a = allocator_type());
    //    match_results(const match_results&) = default;
    //    match_results& operator=(const match_results&) = default;
    //    match_results(match_results&& __m) = default;
    //    match_results& operator=(match_results&& __m) = default;
    //    ~match_results() = default;

    bool ready() const {
        return __ready_;
    }

    // size:

    size_type size() const _NOEXCEPT {
        return __matches_.size();
    }

    size_type max_size() const _NOEXCEPT {
        return __matches_.max_size();
    }
    _LIBCPP_NODISCARD_AFTER_CXX17 bool empty() const _NOEXCEPT {
        return size() == 0;
    }

    // element access:

    difference_type length(size_type __sub = 0) const {
        return (*this)[__sub].length();
    }

    difference_type position(size_type __sub = 0) const {
        return _VSTD::distance(__position_start_, (*this)[__sub].first);
    }

    string_type str(size_type __sub = 0) const {
        return (*this)[__sub].str();
    }

    const_reference operator[](size_type __n) const {
        return __n < __matches_.size() ? __matches_[__n] : __unmatched_;
    }

    const_reference prefix() const {
        return __prefix_;
    }

    const_reference suffix() const {
        return __suffix_;
    }

    const_iterator begin() const {
        return empty() ? __matches_.end() : __matches_.begin();
    }

    const_iterator end() const {
        return __matches_.end();
    }

    const_iterator cbegin() const {
        return empty() ? __matches_.end() : __matches_.begin();
    }

    const_iterator cend() const {
        return __matches_.end();
    }

    // format:
    template <class _OutputIter>
    _OutputIter format(_OutputIter __output_iter, const char_type* __fmt_first, const char_type* __fmt_last, regex_constants::match_flag_type __flags = regex_constants::format_default) const;
    template <class _OutputIter, class _ST, class _SA>
    _OutputIter format(_OutputIter __output_iter, const basic_string<char_type, _ST, _SA>& __fmt, regex_constants::match_flag_type __flags = regex_constants::format_default) const {
        return format(__output_iter, __fmt.data(), __fmt.data() + __fmt.size(), __flags);
    }
    template <class _ST, class _SA>
    basic_string<char_type, _ST, _SA> format(const basic_string<char_type, _ST, _SA>& __fmt, regex_constants::match_flag_type __flags = regex_constants::format_default) const {
        basic_string<char_type, _ST, _SA> __r;
        format(back_inserter(__r), __fmt.data(), __fmt.data() + __fmt.size(), __flags);
        return __r;
    }

    string_type format(const char_type* __fmt, regex_constants::match_flag_type __flags = regex_constants::format_default) const {
        string_type __r;
        format(back_inserter(__r), __fmt, __fmt + char_traits<char_type>::length(__fmt), __flags);
        return __r;
    }

    // allocator:

    allocator_type get_allocator() const {
        return __matches_.get_allocator();
    }

    // swap:
    void swap(match_results& __m);

    template <class _Bp, class _Ap>
    void __assign(_BidirectionalIterator __f, _BidirectionalIterator __l, const match_results<_Bp, _Ap>& __m, bool __no_update_pos) {
        _Bp __mf = __m.prefix().first;
        __matches_.resize(__m.size());
        for (size_type __i = 0; __i < __matches_.size(); ++__i) {
            __matches_[__i].first = _VSTD::next(__f, _VSTD::distance(__mf, __m[__i].first));
            __matches_[__i].second = _VSTD::next(__f, _VSTD::distance(__mf, __m[__i].second));
            __matches_[__i].matched = __m[__i].matched;
        }
        __unmatched_.first = __l;
        __unmatched_.second = __l;
        __unmatched_.matched = false;
        __prefix_.first = _VSTD::next(__f, _VSTD::distance(__mf, __m.prefix().first));
        __prefix_.second = _VSTD::next(__f, _VSTD::distance(__mf, __m.prefix().second));
        __prefix_.matched = __m.prefix().matched;
        __suffix_.first = _VSTD::next(__f, _VSTD::distance(__mf, __m.suffix().first));
        __suffix_.second = _VSTD::next(__f, _VSTD::distance(__mf, __m.suffix().second));
        __suffix_.matched = __m.suffix().matched;
        if (!__no_update_pos)
            __position_start_ = __prefix_.first;
        __ready_ = __m.ready();
    }

  private:
    void __init(unsigned __s, _BidirectionalIterator __f, _BidirectionalIterator __l, bool __no_update_pos = false);

    template <class, class>
    friend class basic_regex;

    template <class _Bp, class _Ap, class _Cp, class _Tp>
    friend bool regex_match(_Bp, _Bp, match_results<_Bp, _Ap>&, const basic_regex<_Cp, _Tp>&, regex_constants::match_flag_type);

    template <class _Bp, class _Ap>
    friend bool operator==(const match_results<_Bp, _Ap>&, const match_results<_Bp, _Ap>&);

    template <class, class>
    friend class __lookahead;
};

template <class _BidirectionalIterator, class _Allocator>
match_results<_BidirectionalIterator, _Allocator>::match_results(const allocator_type& __a) : __matches_(__a), __unmatched_(), __prefix_(), __suffix_(), __ready_(false), __position_start_() {
}

template <class _BidirectionalIterator, class _Allocator>
void match_results<_BidirectionalIterator, _Allocator>::__init(unsigned __s, _BidirectionalIterator __f, _BidirectionalIterator __l, bool __no_update_pos) {
    __unmatched_.first = __l;
    __unmatched_.second = __l;
    __unmatched_.matched = false;
    __matches_.assign(__s, __unmatched_);
    __prefix_.first = __f;
    __prefix_.second = __f;
    __prefix_.matched = false;
    __suffix_ = __unmatched_;
    if (!__no_update_pos)
        __position_start_ = __prefix_.first;
    __ready_ = true;
}

template <class _BidirectionalIterator, class _Allocator>
template <class _OutputIter>
_OutputIter match_results<_BidirectionalIterator, _Allocator>::format(_OutputIter __output_iter, const char_type* __fmt_first, const char_type* __fmt_last,
                                                                      regex_constants::match_flag_type __flags) const {
    if (__flags & regex_constants::format_sed) {
        for (; __fmt_first != __fmt_last; ++__fmt_first) {
            if (*__fmt_first == '&')
                __output_iter = _VSTD::copy(__matches_[0].first, __matches_[0].second, __output_iter);
            else if (*__fmt_first == '\\' && __fmt_first + 1 != __fmt_last) {
                ++__fmt_first;
                if ('0' <= *__fmt_first && *__fmt_first <= '9') {
                    size_t __i = *__fmt_first - '0';
                    __output_iter = _VSTD::copy((*this)[__i].first, (*this)[__i].second, __output_iter);
                } else {
                    *__output_iter = *__fmt_first;
                    ++__output_iter;
                }
            } else {
                *__output_iter = *__fmt_first;
                ++__output_iter;
            }
        }
    } else {
        for (; __fmt_first != __fmt_last; ++__fmt_first) {
            if (*__fmt_first == '$' && __fmt_first + 1 != __fmt_last) {
                switch (__fmt_first[1]) {
                    case '$':
                        *__output_iter = *++__fmt_first;
                        ++__output_iter;
                        break;
                    case '&':
                        ++__fmt_first;
                        __output_iter = _VSTD::copy(__matches_[0].first, __matches_[0].second, __output_iter);
                        break;
                    case '`':
                        ++__fmt_first;
                        __output_iter = _VSTD::copy(__prefix_.first, __prefix_.second, __output_iter);
                        break;
                    case '\'':
                        ++__fmt_first;
                        __output_iter = _VSTD::copy(__suffix_.first, __suffix_.second, __output_iter);
                        break;
                    default:
                        if ('0' <= __fmt_first[1] && __fmt_first[1] <= '9') {
                            ++__fmt_first;
                            size_t __idx = *__fmt_first - '0';
                            if (__fmt_first + 1 != __fmt_last && '0' <= __fmt_first[1] && __fmt_first[1] <= '9') {
                                ++__fmt_first;
                                if (__idx >= std::numeric_limits<size_t>::max() / 10)
                                    __throw_regex_error<regex_constants::error_escape>();
                                __idx = 10 * __idx + *__fmt_first - '0';
                            }
                            __output_iter = _VSTD::copy((*this)[__idx].first, (*this)[__idx].second, __output_iter);
                        } else {
                            *__output_iter = *__fmt_first;
                            ++__output_iter;
                        }
                        break;
                }
            } else {
                *__output_iter = *__fmt_first;
                ++__output_iter;
            }
        }
    }
    return __output_iter;
}

template <class _BidirectionalIterator, class _Allocator>
void match_results<_BidirectionalIterator, _Allocator>::swap(match_results& __m) {
    using _VSTD::swap;
    swap(__matches_, __m.__matches_);
    swap(__unmatched_, __m.__unmatched_);
    swap(__prefix_, __m.__prefix_);
    swap(__suffix_, __m.__suffix_);
    swap(__position_start_, __m.__position_start_);
    swap(__ready_, __m.__ready_);
}

typedef match_results<const char*> cmatch;
typedef match_results<const wchar_t*> wcmatch;
typedef match_results<string::const_iterator> smatch;
typedef match_results<wstring::const_iterator> wsmatch;

template <class _BidirectionalIterator, class _Allocator>
bool operator==(const match_results<_BidirectionalIterator, _Allocator>& __x, const match_results<_BidirectionalIterator, _Allocator>& __y) {
    if (__x.__ready_ != __y.__ready_)
        return false;
    if (!__x.__ready_)
        return true;
    return __x.__matches_ == __y.__matches_ && __x.__prefix_ == __y.__prefix_ && __x.__suffix_ == __y.__suffix_;
}

template <class _BidirectionalIterator, class _Allocator>
inline bool operator!=(const match_results<_BidirectionalIterator, _Allocator>& __x, const match_results<_BidirectionalIterator, _Allocator>& __y) {
    return !(__x == __y);
}

template <class _BidirectionalIterator, class _Allocator>
inline void swap(match_results<_BidirectionalIterator, _Allocator>& __x, match_results<_BidirectionalIterator, _Allocator>& __y) {
    __x.swap(__y);
}

// regex_search

template <class _CharT, class _Traits>
template <class _Allocator>
bool basic_regex<_CharT, _Traits>::__match_at_start_ecma(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags,
                                                         bool __at_first) const {
    vector<__state> __states;
    __node* __st = __start_.get();
    if (__st) {
        sub_match<const _CharT*> __unmatched;
        __unmatched.first = __last;
        __unmatched.second = __last;
        __unmatched.matched = false;

        __states.push_back(__state());
        __states.back().__do_ = 0;
        __states.back().__first_ = __first;
        __states.back().__current_ = __first;
        __states.back().__last_ = __last;
        __states.back().__sub_matches_.resize(mark_count(), __unmatched);
        __states.back().__loop_data_.resize(__loop_count());
        __states.back().__node_ = __st;
        __states.back().__flags_ = __flags;
        __states.back().__at_first_ = __at_first;
        int __counter = 0;
        int __length = __last - __first;
        do {
            ++__counter;
            if (__counter % _LIBCPP_REGEX_COMPLEXITY_FACTOR == 0 && __counter / _LIBCPP_REGEX_COMPLEXITY_FACTOR >= __length)
                __throw_regex_error<regex_constants::error_complexity>();
            __state& __s = __states.back();
            if (__s.__node_)
                __s.__node_->__exec(__s);
            switch (__s.__do_) {
                case __state::__end_state:
                    if ((__flags & regex_constants::match_not_null) && __s.__current_ == __first) {
                        __states.pop_back();
                        break;
                    }
                    if ((__flags & regex_constants::__full_match) && __s.__current_ != __last) {
                        __states.pop_back();
                        break;
                    }
                    __m.__matches_[0].first = __first;
                    __m.__matches_[0].second = _VSTD::next(__first, __s.__current_ - __first);
                    __m.__matches_[0].matched = true;
                    for (unsigned __i = 0; __i < __s.__sub_matches_.size(); ++__i) __m.__matches_[__i + 1] = __s.__sub_matches_[__i];
                    return true;
                case __state::__accept_and_consume:
                case __state::__repeat:
                case __state::__accept_but_not_consume:
                    break;
                case __state::__split: {
                    __state __snext = __s;
                    __s.__node_->__exec_split(true, __s);
                    __snext.__node_->__exec_split(false, __snext);
                    __states.push_back(_VSTD::move(__snext));
                } break;
                case __state::__reject:
                    __states.pop_back();
                    break;
                default:
                    __throw_regex_error<regex_constants::__re_err_unknown>();
                    break;
            }
        } while (!__states.empty());
    }
    return false;
}

template <class _CharT, class _Traits>
template <class _Allocator>
bool basic_regex<_CharT, _Traits>::__match_at_start_posix_nosubs(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags,
                                                                 bool __at_first) const {
    deque<__state> __states;
    ptrdiff_t __highest_j = 0;
    ptrdiff_t _Np = _VSTD::distance(__first, __last);
    __node* __st = __start_.get();
    if (__st) {
        __states.push_back(__state());
        __states.back().__do_ = 0;
        __states.back().__first_ = __first;
        __states.back().__current_ = __first;
        __states.back().__last_ = __last;
        __states.back().__loop_data_.resize(__loop_count());
        __states.back().__node_ = __st;
        __states.back().__flags_ = __flags;
        __states.back().__at_first_ = __at_first;
        bool __matched = false;
        int __counter = 0;
        int __length = __last - __first;
        do {
            ++__counter;
            if (__counter % _LIBCPP_REGEX_COMPLEXITY_FACTOR == 0 && __counter / _LIBCPP_REGEX_COMPLEXITY_FACTOR >= __length)
                __throw_regex_error<regex_constants::error_complexity>();
            __state& __s = __states.back();
            if (__s.__node_)
                __s.__node_->__exec(__s);
            switch (__s.__do_) {
                case __state::__end_state:
                    if ((__flags & regex_constants::match_not_null) && __s.__current_ == __first) {
                        __states.pop_back();
                        break;
                    }
                    if ((__flags & regex_constants::__full_match) && __s.__current_ != __last) {
                        __states.pop_back();
                        break;
                    }
                    if (!__matched || __highest_j < __s.__current_ - __s.__first_)
                        __highest_j = __s.__current_ - __s.__first_;
                    __matched = true;
                    if (__highest_j == _Np)
                        __states.clear();
                    else
                        __states.pop_back();
                    break;
                case __state::__consume_input:
                    break;
                case __state::__accept_and_consume:
                    __states.push_front(_VSTD::move(__s));
                    __states.pop_back();
                    break;
                case __state::__repeat:
                case __state::__accept_but_not_consume:
                    break;
                case __state::__split: {
                    __state __snext = __s;
                    __s.__node_->__exec_split(true, __s);
                    __snext.__node_->__exec_split(false, __snext);
                    __states.push_back(_VSTD::move(__snext));
                } break;
                case __state::__reject:
                    __states.pop_back();
                    break;
                default:
                    __throw_regex_error<regex_constants::__re_err_unknown>();
                    break;
            }
        } while (!__states.empty());
        if (__matched) {
            __m.__matches_[0].first = __first;
            __m.__matches_[0].second = _VSTD::next(__first, __highest_j);
            __m.__matches_[0].matched = true;
            return true;
        }
    }
    return false;
}

template <class _CharT, class _Traits>
template <class _Allocator>
bool basic_regex<_CharT, _Traits>::__match_at_start_posix_subs(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags,
                                                               bool __at_first) const {
    vector<__state> __states;
    __state __best_state;
    ptrdiff_t __j = 0;
    ptrdiff_t __highest_j = 0;
    ptrdiff_t _Np = _VSTD::distance(__first, __last);
    __node* __st = __start_.get();
    if (__st) {
        sub_match<const _CharT*> __unmatched;
        __unmatched.first = __last;
        __unmatched.second = __last;
        __unmatched.matched = false;

        __states.push_back(__state());
        __states.back().__do_ = 0;
        __states.back().__first_ = __first;
        __states.back().__current_ = __first;
        __states.back().__last_ = __last;
        __states.back().__sub_matches_.resize(mark_count(), __unmatched);
        __states.back().__loop_data_.resize(__loop_count());
        __states.back().__node_ = __st;
        __states.back().__flags_ = __flags;
        __states.back().__at_first_ = __at_first;
        const _CharT* __current = __first;
        bool __matched = false;
        int __counter = 0;
        int __length = __last - __first;
        do {
            ++__counter;
            if (__counter % _LIBCPP_REGEX_COMPLEXITY_FACTOR == 0 && __counter / _LIBCPP_REGEX_COMPLEXITY_FACTOR >= __length)
                __throw_regex_error<regex_constants::error_complexity>();
            __state& __s = __states.back();
            if (__s.__node_)
                __s.__node_->__exec(__s);
            switch (__s.__do_) {
                case __state::__end_state:
                    if ((__flags & regex_constants::match_not_null) && __s.__current_ == __first) {
                        __states.pop_back();
                        break;
                    }
                    if ((__flags & regex_constants::__full_match) && __s.__current_ != __last) {
                        __states.pop_back();
                        break;
                    }
                    if (!__matched || __highest_j < __s.__current_ - __s.__first_) {
                        __highest_j = __s.__current_ - __s.__first_;
                        __best_state = __s;
                    }
                    __matched = true;
                    if (__highest_j == _Np)
                        __states.clear();
                    else
                        __states.pop_back();
                    break;
                case __state::__accept_and_consume:
                    __j += __s.__current_ - __current;
                    __current = __s.__current_;
                    break;
                case __state::__repeat:
                case __state::__accept_but_not_consume:
                    break;
                case __state::__split: {
                    __state __snext = __s;
                    __s.__node_->__exec_split(true, __s);
                    __snext.__node_->__exec_split(false, __snext);
                    __states.push_back(_VSTD::move(__snext));
                } break;
                case __state::__reject:
                    __states.pop_back();
                    break;
                default:
                    __throw_regex_error<regex_constants::__re_err_unknown>();
                    break;
            }
        } while (!__states.empty());
        if (__matched) {
            __m.__matches_[0].first = __first;
            __m.__matches_[0].second = _VSTD::next(__first, __highest_j);
            __m.__matches_[0].matched = true;
            for (unsigned __i = 0; __i < __best_state.__sub_matches_.size(); ++__i) __m.__matches_[__i + 1] = __best_state.__sub_matches_[__i];
            return true;
        }
    }
    return false;
}

template <class _CharT, class _Traits>
template <class _Allocator>
bool basic_regex<_CharT, _Traits>::__match_at_start(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags,
                                                    bool __at_first) const {
    if ((__flags_ & 0x1F0) == ECMAScript)
        return __match_at_start_ecma(__first, __last, __m, __flags, __at_first);
    if (mark_count() == 0)
        return __match_at_start_posix_nosubs(__first, __last, __m, __flags, __at_first);
    return __match_at_start_posix_subs(__first, __last, __m, __flags, __at_first);
}

template <class _CharT, class _Traits>
template <class _Allocator>
bool basic_regex<_CharT, _Traits>::__search(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, regex_constants::match_flag_type __flags) const {
    __m.__init(1 + mark_count(), __first, __last, __flags & regex_constants::__no_update_pos);
    if (__match_at_start(__first, __last, __m, __flags, !(__flags & regex_constants::__no_update_pos))) {
        __m.__prefix_.second = __m[0].first;
        __m.__prefix_.matched = __m.__prefix_.first != __m.__prefix_.second;
        __m.__suffix_.first = __m[0].second;
        __m.__suffix_.matched = __m.__suffix_.first != __m.__suffix_.second;
        return true;
    }
    if (__first != __last && !(__flags & regex_constants::match_continuous)) {
        __flags |= regex_constants::match_prev_avail;
        for (++__first; __first != __last; ++__first) {
            __m.__matches_.assign(__m.size(), __m.__unmatched_);
            if (__match_at_start(__first, __last, __m, __flags, false)) {
                __m.__prefix_.second = __m[0].first;
                __m.__prefix_.matched = __m.__prefix_.first != __m.__prefix_.second;
                __m.__suffix_.first = __m[0].second;
                __m.__suffix_.matched = __m.__suffix_.first != __m.__suffix_.second;
                return true;
            }
            __m.__matches_.assign(__m.size(), __m.__unmatched_);
        }
    }
    __m.__matches_.clear();
    return false;
}

template <class _BidirectionalIterator, class _Allocator, class _CharT, class _Traits>
inline bool regex_search(_BidirectionalIterator __first, _BidirectionalIterator __last, match_results<_BidirectionalIterator, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    int __offset = (__flags & regex_constants::match_prev_avail) ? 1 : 0;
    basic_string<_CharT> __s(_VSTD::prev(__first, __offset), __last);
    match_results<const _CharT*> __mc;
    bool __r = __e.__search(__s.data() + __offset, __s.data() + __s.size(), __mc, __flags);
    __m.__assign(__first, __last, __mc, __flags & regex_constants::__no_update_pos);
    return __r;
}

template <class _Iter, class _Allocator, class _CharT, class _Traits>
inline bool regex_search(__wrap_iter<_Iter> __first, __wrap_iter<_Iter> __last, match_results<__wrap_iter<_Iter>, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<const _CharT*> __mc;
    bool __r = __e.__search(__first.base(), __last.base(), __mc, __flags);
    __m.__assign(__first, __last, __mc, __flags & regex_constants::__no_update_pos);
    return __r;
}

template <class _Allocator, class _CharT, class _Traits>
inline bool regex_search(const _CharT* __first, const _CharT* __last, match_results<const _CharT*, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return __e.__search(__first, __last, __m, __flags);
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
inline bool regex_search(_BidirectionalIterator __first, _BidirectionalIterator __last, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    basic_string<_CharT> __s(__first, __last);
    match_results<const _CharT*> __mc;
    return __e.__search(__s.data(), __s.data() + __s.size(), __mc, __flags);
}

template <class _CharT, class _Traits>
inline bool regex_search(const _CharT* __first, const _CharT* __last, const basic_regex<_CharT, _Traits>& __e, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<const _CharT*> __mc;
    return __e.__search(__first, __last, __mc, __flags);
}

template <class _CharT, class _Allocator, class _Traits>
inline bool regex_search(const _CharT* __str, match_results<const _CharT*, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return __e.__search(__str, __str + _Traits::length(__str), __m, __flags);
}

template <class _CharT, class _Traits>
inline bool regex_search(const _CharT* __str, const basic_regex<_CharT, _Traits>& __e, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<const _CharT*> __m;
    return _VSTD::regex_search(__str, __m, __e, __flags);
}

template <class _ST, class _SA, class _CharT, class _Traits>
inline bool regex_search(const basic_string<_CharT, _ST, _SA>& __s, const basic_regex<_CharT, _Traits>& __e, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<const _CharT*> __mc;
    return __e.__search(__s.data(), __s.data() + __s.size(), __mc, __flags);
}

template <class _ST, class _SA, class _Allocator, class _CharT, class _Traits>
inline bool regex_search(const basic_string<_CharT, _ST, _SA>& __s, match_results<typename basic_string<_CharT, _ST, _SA>::const_iterator, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                         regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<const _CharT*> __mc;
    bool __r = __e.__search(__s.data(), __s.data() + __s.size(), __mc, __flags);
    __m.__assign(__s.begin(), __s.end(), __mc, __flags & regex_constants::__no_update_pos);
    return __r;
}

#if _LIBCPP_STD_VER > 11
template <class _ST, class _SA, class _Ap, class _Cp, class _Tp>
bool regex_search(const basic_string<_Cp, _ST, _SA>&& __s, match_results<typename basic_string<_Cp, _ST, _SA>::const_iterator, _Ap>&, const basic_regex<_Cp, _Tp>& __e,
                  regex_constants::match_flag_type __flags = regex_constants::match_default) = delete;
#endif

// regex_match

template <class _BidirectionalIterator, class _Allocator, class _CharT, class _Traits>
bool regex_match(_BidirectionalIterator __first, _BidirectionalIterator __last, match_results<_BidirectionalIterator, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                 regex_constants::match_flag_type __flags = regex_constants::match_default) {
    bool __r = _VSTD::regex_search(__first, __last, __m, __e, __flags | regex_constants::match_continuous | regex_constants::__full_match);
    if (__r) {
        __r = !__m.suffix().matched;
        if (!__r)
            __m.__matches_.clear();
    }
    return __r;
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
inline bool regex_match(_BidirectionalIterator __first, _BidirectionalIterator __last, const basic_regex<_CharT, _Traits>& __e,
                        regex_constants::match_flag_type __flags = regex_constants::match_default) {
    match_results<_BidirectionalIterator> __m;
    return _VSTD::regex_match(__first, __last, __m, __e, __flags);
}

template <class _CharT, class _Allocator, class _Traits>
inline bool regex_match(const _CharT* __str, match_results<const _CharT*, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                        regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return _VSTD::regex_match(__str, __str + _Traits::length(__str), __m, __e, __flags);
}

template <class _ST, class _SA, class _Allocator, class _CharT, class _Traits>
inline bool regex_match(const basic_string<_CharT, _ST, _SA>& __s, match_results<typename basic_string<_CharT, _ST, _SA>::const_iterator, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                        regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return _VSTD::regex_match(__s.begin(), __s.end(), __m, __e, __flags);
}

#if _LIBCPP_STD_VER > 11
template <class _ST, class _SA, class _Allocator, class _CharT, class _Traits>
inline bool regex_match(const basic_string<_CharT, _ST, _SA>&& __s, match_results<typename basic_string<_CharT, _ST, _SA>::const_iterator, _Allocator>& __m, const basic_regex<_CharT, _Traits>& __e,
                        regex_constants::match_flag_type __flags = regex_constants::match_default) = delete;
#endif

template <class _CharT, class _Traits>
inline bool regex_match(const _CharT* __str, const basic_regex<_CharT, _Traits>& __e, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return _VSTD::regex_match(__str, __str + _Traits::length(__str), __e, __flags);
}

template <class _ST, class _SA, class _CharT, class _Traits>
inline bool regex_match(const basic_string<_CharT, _ST, _SA>& __s, const basic_regex<_CharT, _Traits>& __e, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return _VSTD::regex_match(__s.begin(), __s.end(), __e, __flags);
}

// regex_iterator

template <class _BidirectionalIterator, class _CharT = typename iterator_traits<_BidirectionalIterator>::value_type, class _Traits = regex_traits<_CharT> >
class _LIBCPP_TEMPLATE_VIS regex_iterator {
  public:
    typedef basic_regex<_CharT, _Traits> regex_type;
    typedef match_results<_BidirectionalIterator> value_type;
    typedef ptrdiff_t difference_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;
    typedef forward_iterator_tag iterator_category;

  private:
    _BidirectionalIterator __begin_;
    _BidirectionalIterator __end_;
    const regex_type* __pregex_;
    regex_constants::match_flag_type __flags_;
    value_type __match_;

  public:
    regex_iterator();
    regex_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, regex_constants::match_flag_type __m = regex_constants::match_default);
#if _LIBCPP_STD_VER > 11
    regex_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type&& __re, regex_constants::match_flag_type __m = regex_constants::match_default) = delete;
#endif

    bool operator==(const regex_iterator& __x) const;

    bool operator!=(const regex_iterator& __x) const {
        return !(*this == __x);
    }

    reference operator*() const {
        return __match_;
    }

    pointer operator->() const {
        return &__match_;
    }

    regex_iterator& operator++();

    regex_iterator operator++(int) {
        regex_iterator __t(*this);
        ++(*this);
        return __t;
    }
};

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_iterator() : __begin_(), __end_(), __pregex_(nullptr), __flags_(), __match_() {
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, regex_constants::match_flag_type __m)
    : __begin_(__a), __end_(__b), __pregex_(&__re), __flags_(__m) {
    _VSTD::regex_search(__begin_, __end_, __match_, *__pregex_, __flags_);
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
bool regex_iterator<_BidirectionalIterator, _CharT, _Traits>::operator==(const regex_iterator& __x) const {
    if (__match_.empty() && __x.__match_.empty())
        return true;
    if (__match_.empty() || __x.__match_.empty())
        return false;
    return __begin_ == __x.__begin_ && __end_ == __x.__end_ && __pregex_ == __x.__pregex_ && __flags_ == __x.__flags_ && __match_[0] == __x.__match_[0];
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_iterator<_BidirectionalIterator, _CharT, _Traits>& regex_iterator<_BidirectionalIterator, _CharT, _Traits>::operator++() {
    __flags_ |= regex_constants::__no_update_pos;
    _BidirectionalIterator __start = __match_[0].second;
    if (__match_[0].first == __match_[0].second) {
        if (__start == __end_) {
            __match_ = value_type();
            return *this;
        } else if (_VSTD::regex_search(__start, __end_, __match_, *__pregex_, __flags_ | regex_constants::match_not_null | regex_constants::match_continuous))
            return *this;
        else
            ++__start;
    }
    __flags_ |= regex_constants::match_prev_avail;
    if (!_VSTD::regex_search(__start, __end_, __match_, *__pregex_, __flags_))
        __match_ = value_type();
    return *this;
}

typedef regex_iterator<const char*> cregex_iterator;
typedef regex_iterator<const wchar_t*> wcregex_iterator;
typedef regex_iterator<string::const_iterator> sregex_iterator;
typedef regex_iterator<wstring::const_iterator> wsregex_iterator;

// regex_token_iterator

template <class _BidirectionalIterator, class _CharT = typename iterator_traits<_BidirectionalIterator>::value_type, class _Traits = regex_traits<_CharT> >
class _LIBCPP_TEMPLATE_VIS regex_token_iterator {
  public:
    typedef basic_regex<_CharT, _Traits> regex_type;
    typedef sub_match<_BidirectionalIterator> value_type;
    typedef ptrdiff_t difference_type;
    typedef const value_type* pointer;
    typedef const value_type& reference;
    typedef forward_iterator_tag iterator_category;

  private:
    typedef regex_iterator<_BidirectionalIterator, _CharT, _Traits> _Position;

    _Position __position_;
    const value_type* __result_;
    value_type __suffix_;
    ptrdiff_t __n_;
    vector<int> __subs_;

  public:
    regex_token_iterator();
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, int __submatch = 0, regex_constants::match_flag_type __m = regex_constants::match_default);
#if _LIBCPP_STD_VER > 11
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type&& __re, int __submatch = 0,
                         regex_constants::match_flag_type __m = regex_constants::match_default) = delete;
#endif

    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, const vector<int>& __submatches,
                         regex_constants::match_flag_type __m = regex_constants::match_default);
#if _LIBCPP_STD_VER > 11
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type&& __re, const vector<int>& __submatches,
                         regex_constants::match_flag_type __m = regex_constants::match_default) = delete;
#endif

#ifndef _LIBCPP_CXX03_LANG
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, initializer_list<int> __submatches,
                         regex_constants::match_flag_type __m = regex_constants::match_default);

#    if _LIBCPP_STD_VER > 11
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type&& __re, initializer_list<int> __submatches,
                         regex_constants::match_flag_type __m = regex_constants::match_default) = delete;
#    endif
#endif  // _LIBCPP_CXX03_LANG
    template <size_t _Np>
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, const int (&__submatches)[_Np],
                         regex_constants::match_flag_type __m = regex_constants::match_default);
#if _LIBCPP_STD_VER > 11
    template <std::size_t _Np>
    regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type&& __re, const int (&__submatches)[_Np],
                         regex_constants::match_flag_type __m = regex_constants::match_default) = delete;
#endif

    regex_token_iterator(const regex_token_iterator&);
    regex_token_iterator& operator=(const regex_token_iterator&);

    bool operator==(const regex_token_iterator& __x) const;

    bool operator!=(const regex_token_iterator& __x) const {
        return !(*this == __x);
    }

    const value_type& operator*() const {
        return *__result_;
    }

    const value_type* operator->() const {
        return __result_;
    }

    regex_token_iterator& operator++();

    regex_token_iterator operator++(int) {
        regex_token_iterator __t(*this);
        ++(*this);
        return __t;
    }

  private:
    void __init(_BidirectionalIterator __a, _BidirectionalIterator __b);
    void __establish_result() {
        if (__subs_[__n_] == -1)
            __result_ = &__position_->prefix();
        else
            __result_ = &(*__position_)[__subs_[__n_]];
    }
};

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator() : __result_(nullptr), __suffix_(), __n_(0) {
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
void regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::__init(_BidirectionalIterator __a, _BidirectionalIterator __b) {
    if (__position_ != _Position())
        __establish_result();
    else if (__subs_[__n_] == -1) {
        __suffix_.matched = true;
        __suffix_.first = __a;
        __suffix_.second = __b;
        __result_ = &__suffix_;
    } else
        __result_ = nullptr;
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, int __submatch,
                                                                                    regex_constants::match_flag_type __m)
    : __position_(__a, __b, __re, __m), __n_(0), __subs_(1, __submatch) {
    __init(__a, __b);
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, const vector<int>& __submatches,
                                                                                    regex_constants::match_flag_type __m)
    : __position_(__a, __b, __re, __m), __n_(0), __subs_(__submatches) {
    __init(__a, __b);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, initializer_list<int> __submatches,
                                                                                    regex_constants::match_flag_type __m)
    : __position_(__a, __b, __re, __m), __n_(0), __subs_(__submatches) {
    __init(__a, __b);
}

#endif  // _LIBCPP_CXX03_LANG

template <class _BidirectionalIterator, class _CharT, class _Traits>
template <size_t _Np>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator(_BidirectionalIterator __a, _BidirectionalIterator __b, const regex_type& __re, const int (&__submatches)[_Np],
                                                                                    regex_constants::match_flag_type __m)
    : __position_(__a, __b, __re, __m), __n_(0), __subs_(__submatches, __submatches + _Np) {
    __init(__a, __b);
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::regex_token_iterator(const regex_token_iterator& __x)
    : __position_(__x.__position_), __result_(__x.__result_), __suffix_(__x.__suffix_), __n_(__x.__n_), __subs_(__x.__subs_) {
    if (__x.__result_ == &__x.__suffix_)
        __result_ = &__suffix_;
    else if (__result_ != nullptr)
        __establish_result();
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>& regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::operator=(const regex_token_iterator& __x) {
    if (this != &__x) {
        __position_ = __x.__position_;
        if (__x.__result_ == &__x.__suffix_)
            __result_ = &__suffix_;
        else
            __result_ = __x.__result_;
        __suffix_ = __x.__suffix_;
        __n_ = __x.__n_;
        __subs_ = __x.__subs_;

        if (__result_ != nullptr && __result_ != &__suffix_)
            __establish_result();
    }
    return *this;
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
bool regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::operator==(const regex_token_iterator& __x) const {
    if (__result_ == nullptr && __x.__result_ == nullptr)
        return true;
    if (__result_ == &__suffix_ && __x.__result_ == &__x.__suffix_ && __suffix_ == __x.__suffix_)
        return true;
    if (__result_ == nullptr || __x.__result_ == nullptr)
        return false;
    if (__result_ == &__suffix_ || __x.__result_ == &__x.__suffix_)
        return false;
    return __position_ == __x.__position_ && __n_ == __x.__n_ && __subs_ == __x.__subs_;
}

template <class _BidirectionalIterator, class _CharT, class _Traits>
regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>& regex_token_iterator<_BidirectionalIterator, _CharT, _Traits>::operator++() {
    _Position __prev = __position_;
    if (__result_ == &__suffix_)
        __result_ = nullptr;
    else if (static_cast<size_t>(__n_ + 1) < __subs_.size()) {
        ++__n_;
        __establish_result();
    } else {
        __n_ = 0;
        ++__position_;
        if (__position_ != _Position())
            __establish_result();
        else {
            if (_VSTD::find(__subs_.begin(), __subs_.end(), -1) != __subs_.end() && __prev->suffix().length() != 0) {
                __suffix_.matched = true;
                __suffix_.first = __prev->suffix().first;
                __suffix_.second = __prev->suffix().second;
                __result_ = &__suffix_;
            } else
                __result_ = nullptr;
        }
    }
    return *this;
}

typedef regex_token_iterator<const char*> cregex_token_iterator;
typedef regex_token_iterator<const wchar_t*> wcregex_token_iterator;
typedef regex_token_iterator<string::const_iterator> sregex_token_iterator;
typedef regex_token_iterator<wstring::const_iterator> wsregex_token_iterator;

// regex_replace

template <class _OutputIterator, class _BidirectionalIterator, class _Traits, class _CharT>
_OutputIterator regex_replace(_OutputIterator __output_iter, _BidirectionalIterator __first, _BidirectionalIterator __last, const basic_regex<_CharT, _Traits>& __e, const _CharT* __fmt,
                              regex_constants::match_flag_type __flags = regex_constants::match_default) {
    typedef regex_iterator<_BidirectionalIterator, _CharT, _Traits> _Iter;
    _Iter __i(__first, __last, __e, __flags);
    _Iter __eof;
    if (__i == __eof) {
        if (!(__flags & regex_constants::format_no_copy))
            __output_iter = _VSTD::copy(__first, __last, __output_iter);
    } else {
        sub_match<_BidirectionalIterator> __lm;
        for (size_t __len = char_traits<_CharT>::length(__fmt); __i != __eof; ++__i) {
            if (!(__flags & regex_constants::format_no_copy))
                __output_iter = _VSTD::copy(__i->prefix().first, __i->prefix().second, __output_iter);
            __output_iter = __i->format(__output_iter, __fmt, __fmt + __len, __flags);
            __lm = __i->suffix();
            if (__flags & regex_constants::format_first_only)
                break;
        }
        if (!(__flags & regex_constants::format_no_copy))
            __output_iter = _VSTD::copy(__lm.first, __lm.second, __output_iter);
    }
    return __output_iter;
}

template <class _OutputIterator, class _BidirectionalIterator, class _Traits, class _CharT, class _ST, class _SA>
inline _OutputIterator regex_replace(_OutputIterator __output_iter, _BidirectionalIterator __first, _BidirectionalIterator __last, const basic_regex<_CharT, _Traits>& __e,
                                     const basic_string<_CharT, _ST, _SA>& __fmt, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    return _VSTD::regex_replace(__output_iter, __first, __last, __e, __fmt.c_str(), __flags);
}

template <class _Traits, class _CharT, class _ST, class _SA, class _FST, class _FSA>
inline basic_string<_CharT, _ST, _SA> regex_replace(const basic_string<_CharT, _ST, _SA>& __s, const basic_regex<_CharT, _Traits>& __e, const basic_string<_CharT, _FST, _FSA>& __fmt,
                                                    regex_constants::match_flag_type __flags = regex_constants::match_default) {
    basic_string<_CharT, _ST, _SA> __r;
    _VSTD::regex_replace(back_inserter(__r), __s.begin(), __s.end(), __e, __fmt.c_str(), __flags);
    return __r;
}

template <class _Traits, class _CharT, class _ST, class _SA>
inline basic_string<_CharT, _ST, _SA> regex_replace(const basic_string<_CharT, _ST, _SA>& __s, const basic_regex<_CharT, _Traits>& __e, const _CharT* __fmt,
                                                    regex_constants::match_flag_type __flags = regex_constants::match_default) {
    basic_string<_CharT, _ST, _SA> __r;
    _VSTD::regex_replace(back_inserter(__r), __s.begin(), __s.end(), __e, __fmt, __flags);
    return __r;
}

template <class _Traits, class _CharT, class _ST, class _SA>
inline basic_string<_CharT> regex_replace(const _CharT* __s, const basic_regex<_CharT, _Traits>& __e, const basic_string<_CharT, _ST, _SA>& __fmt,
                                          regex_constants::match_flag_type __flags = regex_constants::match_default) {
    basic_string<_CharT> __r;
    _VSTD::regex_replace(back_inserter(__r), __s, __s + char_traits<_CharT>::length(__s), __e, __fmt.c_str(), __flags);
    return __r;
}

template <class _Traits, class _CharT>
inline basic_string<_CharT> regex_replace(const _CharT* __s, const basic_regex<_CharT, _Traits>& __e, const _CharT* __fmt, regex_constants::match_flag_type __flags = regex_constants::match_default) {
    basic_string<_CharT> __r;
    _VSTD::regex_replace(back_inserter(__r), __s, __s + char_traits<_CharT>::length(__s), __e, __fmt, __flags);
    return __r;
}

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

#endif  // _LIBCPP_REGEX
