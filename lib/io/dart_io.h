// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_LIB_IO_DART_IO_H_
#define FLUTTER_LIB_IO_DART_IO_H_

#include "lib/ftl/macros.h"

namespace blink {

class DartIO {
 public:
  static void InitForIsolate();

 private:
  FTL_DISALLOW_IMPLICIT_CONSTRUCTORS(DartIO);
};

}  // namespace blink

#endif  // FLUTTER_LIB_IO_DART_IO_H_
