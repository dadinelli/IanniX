find_package(Qt${QT_VERSION} REQUIRED COMPONENTS 
    Core    
    Test
    Widgets
)

add_executable(test_uihelp
    test_uihelp.cpp
    ../gui/uihelp.cpp
)

target_link_libraries(test_uihelp
    PRIVATE
    Qt${QT_VERSION}::Core
    Qt${QT_VERSION}::Test
    Qt${QT_VERSION}::Widgets
)

add_test(
    NAME UiHelpTest
    COMMAND $<TARGET_FILE:test_uihelp>
)

set(CMAKE_AUTOMOC ON)