// Copyright 2018 The Darwin Neuroevolution Framework Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <QString>
#include <QDockWidget>
#include <QLabel>
#include <QMainWindow>

#include <core/darwin.h>
#include <core/evolution.h>
#include <core/universe.h>

#include <memory>
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow() override;

 signals:
  void sigBeginRun();
  void sigAbortRun();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  // new/open universe
  void on_action_new_triggered();
  void on_action_open_triggered();

  void on_action_run_triggered();
  void on_action_pause_triggered();
  void on_action_reset_triggered();

  // new/open experiment
  void on_action_new_experiment_triggered();
  void on_action_open_experiment_triggered();
  void on_action_branch_experiment_triggered();

  void on_action_new_sandbox_triggered();
  void on_sandbox_tabs_tabCloseRequested(int index);

 private:
  void dockWindow(const char* name,
                  QFrame* window,
                  Qt::DockWidgetAreas allowed_areas,
                  Qt::DockWidgetArea area,
                  bool permanent = false);
                  
  bool confirmationDialog(const QString& title, const QString& text);
  bool confirmEndOfExperiment();

  void createExperimentWindows();

  void reopenLastUniverse();
  void universeSwitched();

  bool resetExperiment();
  void closeExperiment();
  void nextBatchedRun();

  void saveGeometry() const;
  void restoreGeometry();

  void saveLayout() const;
  void restoreLayout();

  void evolutionEvent(uint32_t event_flags);
  void updateUi();

 private:
  Ui::MainWindow* ui;
  QLabel* status_label_ = nullptr;
  QLabel* batch_label_ = nullptr;
  vector<QDockWidget*> experiment_windows_;

  unique_ptr<darwin::Universe> universe_;
  shared_ptr<darwin::Experiment> experiment_;

  // has the experiment been started?
  bool active_experiment_ = false;
  
  // current batch state
  // (current_run = [1 .. total_runs])
  int batch_total_runs_ = 0;
  int batch_current_run_ = 0;

  // the evolution config for the current batch  
  darwin::EvolutionConfig evolution_config_;
};
