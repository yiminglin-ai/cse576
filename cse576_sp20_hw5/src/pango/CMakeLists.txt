find_package(Pangolin QUIET)

if(Pangolin_FOUND)
  message(---------------------------------------------)
  message("Pangolin found!!!!")
  message("Building WITH Visualization")
  message(---------------------------------------------)
  
  link_libraries(${Pangolin_LIBRARIES})
  include_directories(${Pangolin_INCLUDE_DIRS})
  
  add_executable(harris test5-harris.cpp pango-utils.h)
  add_executable(panorama test5-panorama.cpp pango-utils.h)
  add_executable(projections test5-proj.cpp pango-utils.h)
else()
  message(---------------------------------------------)
  message("Pangolin NOT found")
  message("Building WITHOUT Visualization")
  message(---------------------------------------------)
endif()
