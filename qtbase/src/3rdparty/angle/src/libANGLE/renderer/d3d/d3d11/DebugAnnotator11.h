//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DebugAnnotator11.h: D3D11 helpers for adding trace annotations.
//

#ifndef LIBANGLE_RENDERER_D3D_D3D11_DEBUGANNOTATOR11_H_
#define LIBANGLE_RENDERER_D3D_D3D11_DEBUGANNOTATOR11_H_

#include "common/debug.h"

struct ID3DUserDefinedAnnotation;

namespace rx
{

class DebugAnnotator11 : public gl::DebugAnnotator
{
  public:
    DebugAnnotator11();
    ~DebugAnnotator11() override;
    void beginEvent(const std::wstring &eventName) override;
    void endEvent() override;
    void setMarker(const std::wstring &markerName) override;
    bool getStatus() override;

  private:
    void initializeDevice();

    bool mInitialized;
    HMODULE mD3d11Module;
    ID3DUserDefinedAnnotation *mUserDefinedAnnotation;
};

}

#endif // LIBANGLE_RENDERER_D3D_D3D11_DEBUGANNOTATOR11_H_
