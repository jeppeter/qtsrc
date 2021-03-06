//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// TextureImpl.h: Defines the abstract rx::TextureImpl classes.

#ifndef LIBANGLE_RENDERER_TEXTUREIMPL_H_
#define LIBANGLE_RENDERER_TEXTUREIMPL_H_

#include "libANGLE/Error.h"
#include "libANGLE/ImageIndex.h"

#include "common/angleutils.h"

#include "angle_gl.h"

#include <stdint.h>

namespace egl
{
class Surface;
}

namespace gl
{
struct Box;
struct Extents;
struct Offset;
struct Rectangle;
class Framebuffer;
struct PixelUnpackState;
struct SamplerState;
}

namespace rx
{

class TextureImpl : angle::NonCopyable
{
  public:
    virtual ~TextureImpl() {};

    virtual void setUsage(GLenum usage) = 0;

    virtual gl::Error setImage(GLenum target, size_t level, GLenum internalFormat, const gl::Extents &size, GLenum format, GLenum type,
                               const gl::PixelUnpackState &unpack, const uint8_t *pixels) = 0;
    virtual gl::Error setSubImage(GLenum target, size_t level, const gl::Box &area, GLenum format, GLenum type,
                                  const gl::PixelUnpackState &unpack, const uint8_t *pixels) = 0;

    virtual gl::Error setCompressedImage(GLenum target, size_t level, GLenum internalFormat, const gl::Extents &size,
                                         const gl::PixelUnpackState &unpack, const uint8_t *pixels) = 0;
    virtual gl::Error setCompressedSubImage(GLenum target, size_t level, const gl::Box &area, GLenum format,
                                            const gl::PixelUnpackState &unpack, const uint8_t *pixels) = 0;

    virtual gl::Error copyImage(GLenum target, size_t level, const gl::Rectangle &sourceArea, GLenum internalFormat,
                                const gl::Framebuffer *source) = 0;
    virtual gl::Error copySubImage(GLenum target, size_t level, const gl::Offset &destOffset, const gl::Rectangle &sourceArea,
                                   const gl::Framebuffer *source) = 0;

    virtual gl::Error setStorage(GLenum target, size_t levels, GLenum internalFormat, const gl::Extents &size) = 0;

    virtual gl::Error generateMipmaps() = 0;

    virtual void bindTexImage(egl::Surface *surface) = 0;
    virtual void releaseTexImage() = 0;
};

}

#endif // LIBANGLE_RENDERER_TEXTUREIMPL_H_
