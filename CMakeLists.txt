project(DecisionTree)
cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

include_directories(${DecisionTree_SOURCE_DIR}/include)

set(DECISION_CPP

                                                src/continuousdescriptor.cpp
                                                src/categoricaldescriptor.cpp
                                                src/pool.cpp
                                                src/decisiontree.cpp
    )

set(DECISION_H
                                                include/abstractdescriptor.h
                                                include/continuousdescriptor.h
                                                include/categoricaldescriptor.h
                                                include/pool.h
                                                include/decisiontree.h
    )

set(DECISION_DEMO_APP_SRC src/main.cpp)


add_library(Decision STATIC ${DECISION_CPP} ${DECISION_H})

add_executable(DecisionTree ${DECISION_DEMO_APP_SRC})

target_link_libraries(DecisionTree Decision)


