//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Renderbuffer.cpp: Implements the renderer-agnostic gl::Renderbuffer class,
// GL renderbuffer objects and related functionality.
// [OpenGL ES 2.0.24] section 4.4.3 page 108.

#include "libANGLE/Renderbuffer.h"

#include "common/utilities.h"
#include "libANGLE/FramebufferAttachment.h"
#include "libANGLE/Texture.h"
#include "libANGLE/formatutils.h"
#include "libANGLE/renderer/d3d/RenderTargetD3D.h"
#include "libANGLE/renderer/RenderbufferImpl.h"

namespace gl
{
Renderbuffer::Renderbuffer(rx::RenderbufferImpl *impl, GLuint id)
  : RefCountObject(id),
    mRenderbuffer(impl),
    mWidth(0),
    mHeight(0),
    mInternalFormat(GL_RGBA4),
    mSamples(0)
{
}

Renderbuffer::~Renderbuffer()
{
    SafeDelete(mRenderbuffer);
}

Error Renderbuffer::setStorage(GLenum internalformat, size_t width, size_t height)
{
    Error error = mRenderbuffer->setStorage(internalformat, width, height);
    if (error.isError())
    {
        return error;
    }

    mWidth = width;
    mHeight = height;
    mInternalFormat = internalformat;
    mSamples = 0;

    return Error(GL_NO_ERROR);
}

Error Renderbuffer::setStorageMultisample(size_t samples, GLenum internalformat, size_t width, size_t height)
{
    Error error = mRenderbuffer->setStorageMultisample(samples, internalformat, width, height);
    if (error.isError())
    {
        return error;
    }

    mWidth = width;
    mHeight = height;
    mInternalFormat = internalformat;
    mSamples = samples;

    return Error(GL_NO_ERROR);
}

rx::RenderbufferImpl *Renderbuffer::getImplementation()
{
    ASSERT(mRenderbuffer);
    return mRenderbuffer;
}

const rx::RenderbufferImpl *Renderbuffer::getImplementation() const
{
    return mRenderbuffer;
}

GLsizei Renderbuffer::getWidth() const
{
    return mWidth;
}

GLsizei Renderbuffer::getHeight() const
{
    return mHeight;
}

GLenum Renderbuffer::getInternalFormat() const
{
    return mInternalFormat;
}

GLsizei Renderbuffer::getSamples() const
{
    return mSamples;
}

GLuint Renderbuffer::getRedSize() const
{
    return GetInternalFormatInfo(mInternalFormat).redBits;
}

GLuint Renderbuffer::getGreenSize() const
{
    return GetInternalFormatInfo(mInternalFormat).greenBits;
}

GLuint Renderbuffer::getBlueSize() const
{
    return GetInternalFormatInfo(mInternalFormat).blueBits;
}

GLuint Renderbuffer::getAlphaSize() const
{
    return GetInternalFormatInfo(mInternalFormat).alphaBits;
}

GLuint Renderbuffer::getDepthSize() const
{
    return GetInternalFormatInfo(mInternalFormat).depthBits;
}

GLuint Renderbuffer::getStencilSize() const
{
    return GetInternalFormatInfo(mInternalFormat).stencilBits;
}

}
