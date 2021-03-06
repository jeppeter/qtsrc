// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMMON_EVENT_TRACER_H_
#define COMMON_EVENT_TRACER_H_

#include "common/platform.h"

extern "C" {

typedef const unsigned char* (*GetCategoryEnabledFlagFunc)(const char* name);
typedef void (*AddTraceEventFunc)(char phase, const unsigned char* categoryGroupEnabled, const char* name,
                                  unsigned long long id, int numArgs, const char** argNames,
                                  const unsigned char* argTypes, const unsigned long long* argValues,
                                  unsigned char flags);

}

namespace gl
{

extern GetCategoryEnabledFlagFunc g_getCategoryEnabledFlag;
extern AddTraceEventFunc g_addTraceEvent;

const unsigned char* TraceGetTraceCategoryEnabledFlag(const char* name);

void TraceAddTraceEvent(char phase, const unsigned char* categoryGroupEnabled, const char* name, unsigned long long id,
                        int numArgs, const char** argNames, const unsigned char* argTypes,
                        const unsigned long long* argValues, unsigned char flags);

}

#endif  // COMMON_EVENT_TRACER_H_
