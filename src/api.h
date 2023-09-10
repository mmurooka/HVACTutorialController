#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define HVACTutorialController_DLLIMPORT __declspec(dllimport)
#  define HVACTutorialController_DLLEXPORT __declspec(dllexport)
#  define HVACTutorialController_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define HVACTutorialController_DLLIMPORT __attribute__((visibility("default")))
#    define HVACTutorialController_DLLEXPORT __attribute__((visibility("default")))
#    define HVACTutorialController_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define HVACTutorialController_DLLIMPORT
#    define HVACTutorialController_DLLEXPORT
#    define HVACTutorialController_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef HVACTutorialController_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define HVACTutorialController_DLLAPI
#  define HVACTutorialController_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef HVACTutorialController_EXPORTS
#    define HVACTutorialController_DLLAPI HVACTutorialController_DLLEXPORT
#  else
#    define HVACTutorialController_DLLAPI HVACTutorialController_DLLIMPORT
#  endif // HVACTutorialController_EXPORTS
#  define HVACTutorialController_LOCAL HVACTutorialController_DLLLOCAL
#endif // HVACTutorialController_STATIC