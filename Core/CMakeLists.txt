project(Core)
cmake_minimum_required(VERSION 2.8)

set(SOURCES EventHandler ExceptionSafeWrapper IdHolder)

add_library(${PROJECT_NAME} ${SOURCES})
