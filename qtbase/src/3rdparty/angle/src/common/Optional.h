//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Optional.h:
//   Represents a type that may be invalid, similar to std::optional.
//

#ifndef COMMON_OPTIONAL_H_
#define COMMON_OPTIONAL_H_

template <class T>
struct Optional
{
    Optional()
        : mValid(false),
          mValue(T())
    {}

    explicit Optional(const T &valueIn)
        : mValid(true),
          mValue(valueIn)
    {}

    Optional(const Optional &other)
        : mValid(other.mValid),
          mValue(other.mValue)
    {}

    Optional &operator=(const Optional &other)
    {
        this->mValid = other.mValid;
        this->mValue = other.mValue;
        return *this;
    }

    static Optional None()
    {
        return Optional();
    }

    bool valid() const { return mValid; }
    const T &value() const { return mValue; }

    bool operator==(const Optional &other) const
    {
        return ((mValid == other.mValid) && (!mValid || (mValue == other.mValue)));
    }

    bool operator!=(const Optional &other) const
    {
        return !(*this == other);
    }

  private:
    bool mValid;
    T mValue;
};

#endif // COMMON_OPTIONAL_H_
