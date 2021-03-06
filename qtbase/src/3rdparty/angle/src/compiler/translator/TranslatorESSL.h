//
// Copyright (c) 2002-2011 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_TRANSLATOR_TRANSLATORESSL_H_
#define COMPILER_TRANSLATOR_TRANSLATORESSL_H_

#include "compiler/translator/Compiler.h"

class TranslatorESSL : public TCompiler
{
  public:
    TranslatorESSL(sh::GLenum type, ShShaderSpec spec);

  protected:
    void initBuiltInFunctionEmulator(BuiltInFunctionEmulator *emu, int compileOptions) override;

    virtual void translate(TIntermNode *root, int compileOptions);

  private:
    void writeExtensionBehavior();
};

#endif  // COMPILER_TRANSLATOR_TRANSLATORESSL_H_
