#include "HVACTutorialController.h"

HVACTutorialController::HVACTutorialController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  // Construct hand task
  handTask = std::make_shared<mc_tasks::TransformTask>("LeftGripper", robots(), 0, 100.0, 500.0);

  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(kinematicsConstraint);
  solver().addTask(postureTask);
  solver().addTask(handTask);
  solver().setContacts({{}});

  mc_rtc::log::success("HVACTutorialController init done ");
}

bool HVACTutorialController::run()
{
  // Update time
  t += solver().dt();

  // Update the target angle of the neck joint
  postureTask->target({{"NECK_Y", {mc_rtc::constants::toRad(45) * std::sin(0.5 * t)}}});

  // Update the target pose of the hand
  handTask->target(
      sva::PTransformd(sva::RotX(mc_rtc::constants::PI),
                       Eigen::Vector3d(0.4 + 0.2 * std::cos(t), 0.2 + 0.2 * std::sin(t), 0.8)));

  return mc_control::MCController::run();
}

void HVACTutorialController::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);
}

CONTROLLER_CONSTRUCTOR("HVACTutorialController", HVACTutorialController)
