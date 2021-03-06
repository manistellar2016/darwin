
#include "camera_window.h"
#include "sandbox_window.h"

#include <QVBoxLayout>

CameraWindow::CameraWindow(QWidget* parent) : ToolWindow(parent) {
  setWindowTitle("Camera");
  setMinimumSize(64, 64);
  setMaximumSize(4096, 64);
  camera_widget_ = new physics_ui::CameraWidget(this);
  auto layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(camera_widget_);
}

void CameraWindow::onSandboxChange(SandboxWindow* sandbox_window) {
  auto scene = sandbox_window ? sandbox_window->scenePackage().scene.get() : nullptr;
  camera_widget_->setCamera(scene ? scene->camera() : nullptr);
}
