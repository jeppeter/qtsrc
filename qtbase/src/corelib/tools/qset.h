/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSET_H
#define QSET_H

#include <QtCore/qhash.h>
#ifdef Q_COMPILER_INITIALIZER_LISTS
#include <initializer_list>
#endif

#include <iterator>

QT_BEGIN_NAMESPACE


template <class T>
class QSet
{
    typedef QHash<T, QHashDummyValue> Hash;

public:
    inline QSet() Q_DECL_NOTHROW {}
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline QSet(std::initializer_list<T> list)
    {
        reserve(int(list.size()));
        for (typename std::initializer_list<T>::const_iterator it = list.begin(); it != list.end(); ++it)
            insert(*it);
    }
#endif
    // compiler-generated copy/move ctor/assignment operators are fine!
    // compiler-generated destructor is fine!

    inline void swap(QSet<T> &other) Q_DECL_NOTHROW { q_hash.swap(other.q_hash); }

    inline bool operator==(const QSet<T> &other) const
        { return q_hash == other.q_hash; }
    inline bool operator!=(const QSet<T> &other) const
        { return q_hash != other.q_hash; }

    inline int size() const { return q_hash.size(); }

    inline bool isEmpty() const { return q_hash.isEmpty(); }

    inline int capacity() const { return q_hash.capacity(); }
    inline void reserve(int size);
    inline void squeeze() { q_hash.squeeze(); }

    inline void detach() { q_hash.detach(); }
    inline bool isDetached() const { return q_hash.isDetached(); }
#if !defined(QT_NO_UNSHARABLE_CONTAINERS)
    inline void setSharable(bool sharable) { q_hash.setSharable(sharable); }
#endif

    inline void clear() { q_hash.clear(); }

    inline bool remove(const T &value) { return q_hash.remove(value) != 0; }

    inline bool contains(const T &value) const { return q_hash.contains(value); }

    bool contains(const QSet<T> &set) const;

    class const_iterator;

    class iterator
    {
        typedef QHash<T, QHashDummyValue> Hash;
        typename Hash::iterator i;
        friend class const_iterator;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

        inline iterator() {}
        inline iterator(typename Hash::iterator o) : i(o) {}
        inline iterator(const iterator &o) : i(o.i) {}
        inline iterator &operator=(const iterator &o) { i = o.i; return *this; }
        inline const T &operator*() const { return i.key(); }
        inline const T *operator->() const { return &i.key(); }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator==(const const_iterator &o) const
            { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const
            { return i != o.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline iterator operator++(int) { iterator r = *this; ++i; return r; }
        inline iterator &operator--() { --i; return *this; }
        inline iterator operator--(int) { iterator r = *this; --i; return r; }
        inline iterator operator+(int j) const { return i + j; }
        inline iterator operator-(int j) const { return i - j; }
        inline iterator &operator+=(int j) { i += j; return *this; }
        inline iterator &operator-=(int j) { i -= j; return *this; }
    };

    class const_iterator
    {
        typedef QHash<T, QHashDummyValue> Hash;
        typename Hash::const_iterator i;
        friend class iterator;
        friend class QSet<T>;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef qptrdiff difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

        inline const_iterator() {}
        inline const_iterator(typename Hash::const_iterator o) : i(o) {}
        inline const_iterator(const const_iterator &o) : i(o.i) {}
        inline const_iterator(const iterator &o)
            : i(o.i) {}
        inline const_iterator &operator=(const const_iterator &o) { i = o.i; return *this; }
        inline const T &operator*() const { return i.key(); }
        inline const T *operator->() const { return &i.key(); }
        inline bool operator==(const const_iterator &o) const { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const { return i != o.i; }
        inline const_iterator &operator++() { ++i; return *this; }
        inline const_iterator operator++(int) { const_iterator r = *this; ++i; return r; }
        inline const_iterator &operator--() { --i; return *this; }
        inline const_iterator operator--(int) { const_iterator r = *this; --i; return r; }
        inline const_iterator operator+(int j) const { return i + j; }
        inline const_iterator operator-(int j) const { return i - j; }
        inline const_iterator &operator+=(int j) { i += j; return *this; }
        inline const_iterator &operator-=(int j) { i -= j; return *this; }
    };

    // STL style
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    inline iterator begin() { return q_hash.begin(); }
    inline const_iterator begin() const Q_DECL_NOTHROW { return q_hash.begin(); }
    inline const_iterator cbegin() const Q_DECL_NOTHROW { return q_hash.begin(); }
    inline const_iterator constBegin() const Q_DECL_NOTHROW { return q_hash.constBegin(); }
    inline iterator end() { return q_hash.end(); }
    inline const_iterator end() const Q_DECL_NOTHROW { return q_hash.end(); }
    inline const_iterator cend() const Q_DECL_NOTHROW { return q_hash.end(); }
    inline const_iterator constEnd() const Q_DECL_NOTHROW { return q_hash.constEnd(); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const Q_DECL_NOTHROW { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const Q_DECL_NOTHROW { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const Q_DECL_NOTHROW { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const Q_DECL_NOTHROW { return const_reverse_iterator(begin()); }

    iterator erase(iterator i)
    {
        Q_ASSERT_X(isValidIterator(i), "QSet::erase", "The specified const_iterator argument 'i' is invalid");
        return q_hash.erase(reinterpret_cast<typename Hash::iterator &>(i));
    }

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return q_hash.count(); }
    inline iterator insert(const T &value)
        { return static_cast<typename Hash::iterator>(q_hash.insert(value, QHashDummyValue())); }
    iterator find(const T &value) { return q_hash.find(value); }
    const_iterator find(const T &value) const { return q_hash.find(value); }
    inline const_iterator constFind(const T &value) const { return find(value); }
    QSet<T> &unite(const QSet<T> &other);
    QSet<T> &intersect(const QSet<T> &other);
    bool intersects(const QSet<T> &other) const;
    QSet<T> &subtract(const QSet<T> &other);

    // STL compatibility
    typedef T key_type;
    typedef T value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef qptrdiff difference_type;
    typedef int size_type;

    inline bool empty() const { return isEmpty(); }
    // comfort
    inline QSet<T> &operator<<(const T &value) { insert(value); return *this; }
    inline QSet<T> &operator|=(const QSet<T> &other) { unite(other); return *this; }
    inline QSet<T> &operator|=(const T &value) { insert(value); return *this; }
    inline QSet<T> &operator&=(const QSet<T> &other) { intersect(other); return *this; }
    inline QSet<T> &operator&=(const T &value)
        { QSet<T> result; if (contains(value)) result.insert(value); return (*this = result); }
    inline QSet<T> &operator+=(const QSet<T> &other) { unite(other); return *this; }
    inline QSet<T> &operator+=(const T &value) { insert(value); return *this; }
    inline QSet<T> &operator-=(const QSet<T> &other) { subtract(other); return *this; }
    inline QSet<T> &operator-=(const T &value) { remove(value); return *this; }
    inline QSet<T> operator|(const QSet<T> &other) const
        { QSet<T> result = *this; result |= other; return result; }
    inline QSet<T> operator&(const QSet<T> &other) const
        { QSet<T> result = *this; result &= other; return result; }
    inline QSet<T> operator+(const QSet<T> &other) const
        { QSet<T> result = *this; result += other; return result; }
    inline QSet<T> operator-(const QSet<T> &other) const
        { QSet<T> result = *this; result -= other; return result; }

    QList<T> toList() const;
    inline QList<T> values() const { return toList(); }

    static QSet<T> fromList(const QList<T> &list);

private:
    Hash q_hash;
    bool isValidIterator(const iterator &i) const
    {
        return q_hash.isValidIterator(reinterpret_cast<const typename Hash::iterator&>(i));
    }
};

template <typename T>
uint qHash(const QSet<T> &key, uint seed = 0)
Q_DECL_NOEXCEPT_EXPR(noexcept(qHashRangeCommutative(key.begin(), key.end(), seed)))
{
    return qHashRangeCommutative(key.begin(), key.end(), seed);
}

// inline function implementations

template <class T>
Q_INLINE_TEMPLATE void QSet<T>::reserve(int asize) { q_hash.reserve(asize); }

template <class T>
Q_INLINE_TEMPLATE QSet<T> &QSet<T>::unite(const QSet<T> &other)
{
    QSet<T> copy(other);
    typename QSet<T>::const_iterator i = copy.constEnd();
    while (i != copy.constBegin()) {
        --i;
        insert(*i);
    }
    return *this;
}

template <class T>
Q_INLINE_TEMPLATE QSet<T> &QSet<T>::intersect(const QSet<T> &other)
{
    QSet<T> copy1;
    QSet<T> copy2;
    if (size() <= other.size()) {
        copy1 = *this;
        copy2 = other;
    } else {
        copy1 = other;
        copy2 = *this;
        *this = copy1;
    }
    typename QSet<T>::const_iterator i = copy1.constEnd();
    while (i != copy1.constBegin()) {
        --i;
        if (!copy2.contains(*i))
            remove(*i);
    }
    return *this;
}

template <class T>
Q_INLINE_TEMPLATE bool QSet<T>::intersects(const QSet<T> &other) const
{
    const bool otherIsBigger = other.size() > size();
    const QSet &smallestSet = otherIsBigger ? *this : other;
    const QSet &biggestSet = otherIsBigger ? other : *this;
    const bool equalSeeds = q_hash.d->seed == other.q_hash.d->seed;
    typename QSet::const_iterator i = smallestSet.cbegin();
    typename QSet::const_iterator e = smallestSet.cend();

    if (Q_LIKELY(equalSeeds)) {
        // If seeds are equal we take the fast path so no hash is recalculated.
        while (i != e) {
            if (*biggestSet.q_hash.findNode(*i, i.i.i->h) != biggestSet.q_hash.e)
                return true;
            ++i;
        }
    } else {
        while (i != e) {
            if (biggestSet.contains(*i))
                return true;
            ++i;
        }
     }

    return false;
}

template <class T>
Q_INLINE_TEMPLATE QSet<T> &QSet<T>::subtract(const QSet<T> &other)
{
    QSet<T> copy1(*this);
    QSet<T> copy2(other);
    typename QSet<T>::const_iterator i = copy1.constEnd();
    while (i != copy1.constBegin()) {
        --i;
        if (copy2.contains(*i))
            remove(*i);
    }
    return *this;
}

template <class T>
Q_INLINE_TEMPLATE bool QSet<T>::contains(const QSet<T> &other) const
{
    typename QSet<T>::const_iterator i = other.constBegin();
    while (i != other.constEnd()) {
        if (!contains(*i))
            return false;
        ++i;
    }
    return true;
}

template <typename T>
Q_OUTOFLINE_TEMPLATE QList<T> QSet<T>::toList() const
{
    QList<T> result;
    result.reserve(size());
    typename QSet<T>::const_iterator i = constBegin();
    while (i != constEnd()) {
        result.append(*i);
        ++i;
    }
    return result;
}

template <typename T>
Q_OUTOFLINE_TEMPLATE QSet<T> QList<T>::toSet() const
{
    QSet<T> result;
    result.reserve(size());
    for (int i = 0; i < size(); ++i)
        result.insert(at(i));
    return result;
}

template <typename T>
QSet<T> QSet<T>::fromList(const QList<T> &list)
{
    return list.toSet();
}

template <typename T>
QList<T> QList<T>::fromSet(const QSet<T> &set)
{
    return set.toList();
}

Q_DECLARE_SEQUENTIAL_ITERATOR(Set)

template <typename T>
class QMutableSetIterator
{
    typedef typename QSet<T>::iterator iterator;
    QSet<T> *c;
    iterator i, n;
    inline bool item_exists() const { return c->constEnd() != n; }

public:
    inline QMutableSetIterator(QSet<T> &container)
        : c(&container)
    { i = c->begin(); n = c->end(); }
    inline QMutableSetIterator &operator=(QSet<T> &container)
    { c = &container; i = c->begin(); n = c->end(); return *this; }
    inline void toFront() { i = c->begin(); n = c->end(); }
    inline void toBack() { i = c->end(); n = i; }
    inline bool hasNext() const { return c->constEnd() != i; }
    inline const T &next() { n = i++; return *n; }
    inline const T &peekNext() const { return *i; }
    inline bool hasPrevious() const { return c->constBegin() != i; }
    inline const T &previous() { n = --i; return *n; }
    inline const T &peekPrevious() const { iterator p = i; return *--p; }
    inline void remove()
    { if (c->constEnd() != n) { i = c->erase(n); n = c->end(); } }
    inline const T &value() const { Q_ASSERT(item_exists()); return *n; }
    inline bool findNext(const T &t)
    { while (c->constEnd() != (n = i)) if (*i++ == t) return true; return false; }
    inline bool findPrevious(const T &t)
    { while (c->constBegin() != i) if (*(n = --i) == t) return true;
      n = c->end(); return false;  }
};

QT_END_NAMESPACE

#endif // QSET_H
