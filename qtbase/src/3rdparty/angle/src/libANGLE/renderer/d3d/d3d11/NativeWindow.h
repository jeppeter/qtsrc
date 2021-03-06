//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// NativeWindow.h: Defines NativeWindow, a class for managing and
// performing operations on an EGLNativeWindowType.
// It is used for HWND (Desktop Windows) and IInspectable objects
//(Windows Store Applications).

#ifndef LIBANGLE_RENDERER_D3D_D3D11_NATIVEWINDOW_H_
#define LIBANGLE_RENDERER_D3D_D3D11_NATIVEWINDOW_H_

#include "common/debug.h"
#include "common/platform.h"

#include <EGL/eglplatform.h>

// DXGISwapChain and DXGIFactory are typedef'd to specific required
// types. The HWND NativeWindow implementation requires IDXGISwapChain
// and IDXGIFactory and the Windows Store NativeWindow
// implementation requires IDXGISwapChain1 and IDXGIFactory2.
#if defined(ANGLE_ENABLE_WINDOWS_STORE)
typedef IDXGISwapChain1 DXGISwapChain;
typedef IDXGIFactory2 DXGIFactory;

#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>
#include <windows.applicationmodel.core.h>
#include <memory>

namespace rx
{
class InspectableNativeWindow;
}

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

#elif defined(ANGLE_ENABLE_D3D11)
typedef IDXGISwapChain DXGISwapChain;
typedef IDXGIFactory DXGIFactory;
#endif

namespace rx
{

class NativeWindow
{
  public:
    enum RotationFlags { RotateNone = 0, RotateLeft = 1, RotateRight = 2 };
    explicit NativeWindow(EGLNativeWindowType window);

    bool initialize();
    bool getClientRect(LPRECT rect);
    bool isIconic();
#if defined(ANGLE_ENABLE_WINDOWS_STORE) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
    RotationFlags rotationFlags() const;
#endif
    static bool isValidNativeWindow(EGLNativeWindowType window);

#if defined(ANGLE_ENABLE_D3D11)
    HRESULT createSwapChain(ID3D11Device* device, DXGIFactory* factory,
                            DXGI_FORMAT format, UINT width, UINT height,
                            DXGISwapChain** swapChain);
#endif

    inline EGLNativeWindowType getNativeWindow() const { return mWindow; }

  private:
    EGLNativeWindowType mWindow;

#if defined(ANGLE_ENABLE_WINDOWS_STORE)
    std::shared_ptr<InspectableNativeWindow> mImpl;
#endif

};

}

#endif // LIBANGLE_RENDERER_D3D_D3D11_NATIVEWINDOW_H_
