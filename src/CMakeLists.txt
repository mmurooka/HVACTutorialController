set(controller_SRC
  HVACTutorialController.cpp
)

set(controller_HDR
  HVACTutorialController.h
)

add_controller(${PROJECT_NAME} ${controller_SRC} ${controller_HDR})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DHVACTutorialController_EXPORTS")

