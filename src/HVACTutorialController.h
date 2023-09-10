#pragma once

#include <mc_control/mc_controller.h>
#include <mc_tasks/TransformTask.h>


#include "api.h"

struct HVACTutorialController_DLLAPI HVACTutorialController : public mc_control::MCController
{
  HVACTutorialController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

  bool run() override;

  void reset(const mc_control::ControllerResetData & reset_data) override;

protected:
  //! Current time [sec]
  double t = 0.0;

  //! Hand task
  std::shared_ptr<mc_tasks::TransformTask> handTask;
};
