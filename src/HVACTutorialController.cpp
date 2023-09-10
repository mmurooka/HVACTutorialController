#include <mc_rtc/gui/Button.h>

#include "HVACTutorialController.h"

HVACTutorialController::HVACTutorialController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  // Construct hand task
  handTask = std::make_shared<mc_tasks::TransformTask>("LeftGripper", robots(), 0, 100.0, 500.0);

  // Construct foot tasks
  footTasks[0] = std::make_shared<mc_tasks::TransformTask>("LeftFoot", robots(), 0, 1000.0, 500.0);
  footTasks[1] = std::make_shared<mc_tasks::TransformTask>("RightFoot", robots(), 0, 1000.0, 500.0);

  // Construct CoM task
  comTask = std::make_shared<mc_tasks::CoMTask>(robots(), 0, 1000.0, 500.0);
  comTask->dimWeight(Eigen::Vector3d(1.0, 1.0, 0.1));

  // Construct base task
  baseTask = std::make_shared<mc_tasks::OrientationTask>("WAIST_R_S", robots(), 0, 50.0, 30.0);

  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(kinematicsConstraint);
  solver().addConstraintSet(selfCollisionConstraint);
  solver().addTask(postureTask);
  solver().addTask(handTask);
  solver().addTask(footTasks[0]);
  solver().addTask(footTasks[1]);
  solver().addTask(comTask);
  solver().addTask(baseTask);
  solver().setContacts({{}});

  // Add buttons to move the CoM
  gui()->addElement(
      {"HVACTutorialController"},
      mc_rtc::gui::Button("Move CoM to the left", [this]() { comFlag = 1; }),
      mc_rtc::gui::Button("Move CoM to the center", [this]() { comFlag = 0; }),
      mc_rtc::gui::Button("Move CoM to the right", [this]() { comFlag = -1; }));

  // Add the sample log entry
  logger().addLogEntry("sampleEntry", this, [this]() { return std::sin(t) + std::cos(0.4 * t); });

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

  // Update the target position of the CoM
  Eigen::Vector3d footCenter = 0.5 * (footTasks[0]->target().translation() + footTasks[1]->target().translation());
  comTask->com(footCenter + Eigen::Vector3d(0.0, static_cast<double>(comFlag) * 0.1, 0.8));

  return mc_control::MCController::run();
}

void HVACTutorialController::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);
}

CONTROLLER_CONSTRUCTOR("HVACTutorialController", HVACTutorialController)
