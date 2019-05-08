cmake_minimum_required(VERSION 3.1)

project(TFY4235_Project_1 CXX C)

add_compile_options(-std=c++17 -O3)

find_package(OpenMP)
find_package(HDF5 REQUIRED)
find_package(Armadillo REQUIRED)

file(GLOB proj_SRC
    "*.cpp"
)

include_directories(${ARMADILLO_INCLUDE_DIRS} ${HDF5_INCLUDE_DIR})
set(_hdf5_libs hdf5 hdf5_cpp)
add_executable(project1 ${proj_SRC})
target_link_libraries(project1 PUBLIC ${_hdf5_libs})
target_link_libraries(project1 PUBLIC ${ARMADILLO_LIBRARIES})
target_include_directories(project1 PRIVATE ${ARMADILLO_INCLUDE_DIRS})

if(OpenMP_CXX_FOUND)
    target_link_libraries(project1 PUBLIC OpenMP::OpenMP_CXX)
endif()
