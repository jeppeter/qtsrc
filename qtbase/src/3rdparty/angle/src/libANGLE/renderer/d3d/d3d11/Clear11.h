//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Clear11.h: Framebuffer clear utility class.

#ifndef LIBANGLE_RENDERER_D3D_D3D11_CLEAR11_H_
#define LIBANGLE_RENDERER_D3D_D3D11_CLEAR11_H_

#include <map>
#include <vector>

#include "libANGLE/angletypes.h"
#include "libANGLE/Error.h"
#include "libANGLE/Framebuffer.h"

namespace rx
{
class Renderer11;
class RenderTarget11;
struct ClearParameters;

class Clear11 : angle::NonCopyable
{
  public:
    explicit Clear11(Renderer11 *renderer);
    ~Clear11();

    // Clears the framebuffer with the supplied clear parameters, assumes that the framebuffer is currently applied.
    gl::Error clearFramebuffer(const ClearParameters &clearParams, const gl::Framebuffer::Data &fboData);

  private:
    struct MaskedRenderTarget
    {
        bool colorMask[4];
        RenderTarget11 *renderTarget;
    };

    ID3D11BlendState *getBlendState(const std::vector<MaskedRenderTarget> &rts);
    ID3D11DepthStencilState *getDepthStencilState(const ClearParameters &clearParams);

    struct ClearShader
    {
        ID3D11InputLayout *inputLayout;
        ID3D11VertexShader *vertexShader;
        ID3D11PixelShader *pixelShader;
    };

    template <unsigned int vsSize, unsigned int psSize>
    static ClearShader CreateClearShader(ID3D11Device *device, DXGI_FORMAT colorType, const BYTE(&vsByteCode)[vsSize], const BYTE(&psByteCode)[psSize]);

    Renderer11 *mRenderer;

    struct ClearBlendInfo
    {
        bool maskChannels[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT][4];
    };
    typedef bool(*ClearBlendInfoComparisonFunction)(const ClearBlendInfo&, const ClearBlendInfo &);
    typedef std::map<ClearBlendInfo, ID3D11BlendState*, ClearBlendInfoComparisonFunction> ClearBlendStateMap;
    ClearBlendStateMap mClearBlendStates;

    ClearShader mFloatClearShader;
    ClearShader mUintClearShader;
    ClearShader mIntClearShader;

    struct ClearDepthStencilInfo
    {
        bool clearDepth;
        bool clearStencil;
        UINT8 stencilWriteMask;
    };
    typedef bool (*ClearDepthStencilInfoComparisonFunction)(const ClearDepthStencilInfo&, const ClearDepthStencilInfo &);
    typedef std::map<ClearDepthStencilInfo, ID3D11DepthStencilState*, ClearDepthStencilInfoComparisonFunction> ClearDepthStencilStateMap;
    ClearDepthStencilStateMap mClearDepthStencilStates;

    ID3D11Buffer *mVertexBuffer;
    ID3D11RasterizerState *mRasterizerState;

    bool mSupportsClearView;
};

}

#endif // LIBANGLE_RENDERER_D3D_D3D11_CLEAR11_H_
