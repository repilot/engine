// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_LIB_UI_WINDOW_WINDOW_H_
#define FLUTTER_LIB_UI_WINDOW_WINDOW_H_

#include <unordered_map>

#include "flutter/lib/ui/semantics/semantics_update.h"
#include "flutter/lib/ui/window/platform_message.h"
#include "flutter/lib/ui/window/pointer_data_packet.h"
#include "flutter/lib/ui/window/viewport_metrics.h"
#include "lib/ftl/time/time_point.h"
#include "lib/tonic/dart_persistent_value.h"

namespace tonic {
class DartLibraryNatives;
}  // namespace tonic

namespace blink {
class Scene;

class WindowClient {
 public:
  virtual void ScheduleFrame() = 0;
  virtual void Render(Scene* scene) = 0;
  virtual void UpdateSemantics(SemanticsUpdate* update) = 0;
  virtual void HandlePlatformMessage(ftl::RefPtr<PlatformMessage> message) = 0;

 protected:
  virtual ~WindowClient();
};

class Window {
 public:
  explicit Window(WindowClient* client);
  ~Window();

  WindowClient* client() const { return client_; }

  void DidCreateIsolate();
  void UpdateWindowMetrics(const ViewportMetrics& metrics);
  void UpdateLocale(const std::string& language_code,
                    const std::string& country_code);
  void UpdateSemanticsEnabled(bool enabled);
  void DispatchPlatformMessage(ftl::RefPtr<PlatformMessage> message);
  void DispatchPointerDataPacket(const PointerDataPacket& packet);
  void DispatchSemanticsAction(int32_t id, SemanticsAction action);
  void BeginFrame(ftl::TimePoint frameTime);

  void CompletePlatformMessageResponse(int response_id,
                                       std::vector<uint8_t> data);

  static void RegisterNatives(tonic::DartLibraryNatives* natives);

 private:
  WindowClient* client_;
  tonic::DartPersistentValue library_;

  // We use id 0 to mean that no response is expected.
  int next_response_id_ = 1;
  std::unordered_map<int, ftl::RefPtr<blink::PlatformMessageResponse>>
      pending_responses_;
};

}  // namespace blink

#endif  // FLUTTER_LIB_UI_WINDOW_WINDOW_H_
