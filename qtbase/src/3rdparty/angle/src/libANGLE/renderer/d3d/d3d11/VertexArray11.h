//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// VertexArray11.h: Defines the rx::VertexArray11 class which implements rx::VertexArrayImpl.

#ifndef LIBANGLE_RENDERER_D3D_D3D11_VERTEXARRAY11_H_
#define LIBANGLE_RENDERER_D3D_D3D11_VERTEXARRAY11_H_

#include "libANGLE/renderer/VertexArrayImpl.h"
#include "libANGLE/renderer/d3d/d3d11/Renderer11.h"

namespace rx
{
class Renderer11;

class VertexArray11 : public VertexArrayImpl
{
  public:
    VertexArray11(Renderer11 *renderer)
        : VertexArrayImpl(),
          mRenderer(renderer)
    {
    }
    virtual ~VertexArray11() { }

    virtual void setElementArrayBuffer(const gl::Buffer *buffer) { }
    virtual void setAttribute(size_t idx, const gl::VertexAttribute &attr) { }
    virtual void setAttributeDivisor(size_t idx, GLuint divisor) { }
    virtual void enableAttribute(size_t idx, bool enabledState) { }

  private:
    Renderer11 *mRenderer;
};

}

#endif // LIBANGLE_RENDERER_D3D_D3D11_VERTEXARRAY11_H_
