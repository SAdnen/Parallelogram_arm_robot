cmake_minimum_required(VERSION 2.8.3)

find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})

#Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Build our plugin
add_library(arm_plugin SHARED arm_plugin.cc)
target_link_libraries(arm_plugin  ${GAZEBO_libraries} ${roscpp_LIBRARIES})


# Build the stand-alone test program
add_executable(velDD1 velDD1.cc)

if (${gazebo_VERSION_MAJOR} LESS 6)
  # These two
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(velDD1 ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(velDD1 ${GAZEBO_LIBRARIES})
endif()

# Build the stand-alone test program
add_executable(velDD2 velDD2.cc)
if (${gazebo_VERSION_MAJOR} LESS 6)
  # These two
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(velDD2 ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(velDD2 ${GAZEBO_LIBRARIES})
endif()
add_executable(vel12 vel12.cc)
if (${gazebo_VERSION_MAJOR} LESS 6)
  # These two
  include(FindBoost)
  find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
  target_link_libraries(vel12 ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else()
  target_link_libraries(vel12 ${GAZEBO_LIBRARIES})
endif()
