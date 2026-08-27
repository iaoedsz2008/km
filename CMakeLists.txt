
cmake_minimum_required(VERSION 3.4)

project(awesome)
enable_language(ASM_MASM)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

include(CheckCXXCompilerFlag)
include(TestBigEndian)

include_directories(${CMAKE_CURRENT_LIST_DIR})

################################################################################

if(MSVC)

  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB /ENTRY:main")

  # https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-build-my-msvc-application-with-a-static-runtime
  foreach(flag_var
          CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
          CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)

    # Runtime Library
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")

    # Basic Runtime Checks
    if(${flag_var} MATCHES "/RTC")
        string(REGEX REPLACE "/RTC[^ ]+" "" ${flag_var} "${${flag_var}}")
    endif()

    # Warning Level
    if(${flag_var} MATCHES "/W3")
        string(REGEX REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")
    endif()

  endforeach(flag_var)

  add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_UNICODE)
  add_definitions(-DUNICODE)
  add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/utf-8>)

endif()

################################################################################

# https://discourse.cmake.org/t/cmake-3-21-rc-1-threads-threads-not-found/3630
find_package(Threads REQUIRED)

################################################################################

set(OPENSSL_MSVC_STATIC_RT  ON  CACHE BOOL "" FORCE)
set(OPENSSL_USE_STATIC_LIBS ON  CACHE BOOL "" FORCE)

find_package(OpenSSL REQUIRED)

################################################################################
#
#set(LEVELDB_BUILD_TESTS             OFF CACHE BOOL "" FORCE)
#set(LEVELDB_BUILD_BENCHMARKS        OFF CACHE BOOL "" FORCE)
#set(LEVELDB_INSTALL                 OFF CACHE BOOL "" FORCE)
#
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/leveldb)
#
################################################################################

add_library(sqlite3
  STATIC
  ${CMAKE_CURRENT_LIST_DIR}/sqlite-amalgamation-3530400/sqlite3.c
  ${CMAKE_CURRENT_LIST_DIR}/sqlite-amalgamation-3530400/sqlite3.h
  ${CMAKE_CURRENT_LIST_DIR}/sqlite-amalgamation-3530400/sqlite3ext.h
)

target_include_directories(sqlite3
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/sqlite-amalgamation-3530400
)

################################################################################

add_library(Support
  STATIC
  ${CMAKE_CURRENT_LIST_DIR}/Support/lfqueue.cxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/lfqueue.hxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/lfstack.cxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/lfstack.hxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/SecureSeed.hxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/StringHash.hxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/Support.cxx
  ${CMAKE_CURRENT_LIST_DIR}/Support/Support.hxx
)

target_include_directories(Support
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Support
)

################################################################################

add_executable(cli
  cli/cli.cxx
  cli/cli.hxx
)

target_link_libraries(cli PUBLIC sqlite3)
target_link_libraries(cli PUBLIC Support)
