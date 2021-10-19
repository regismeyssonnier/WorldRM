CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project (WorldRMW)
INCLUDE(GNUInstallDirs)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# setup version numbers
# TODO: Update these for each release!
set(VERSION_MAJOR 3)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# Update fg_version.h to match the versions number here in cmake
CONFIGURE_FILE(../../src/fg_version.h.in ../../src/fg_version.h)

# shared lib version numbers (change before release)
set(SO_MAJOR 3)		# increment on backwards incompatible API/ABI changes
set(SO_MINOR 10)	# increment on backwards compatible or internal changes
set(SO_REV 0)		# if nothing else changed increment this

# FREEGLUT_BUILD_SHARED_LIBS is already a standard CMake variable, but we need to
# re-declare it here so it will show up in the GUI.
# by default, we want to build both
OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." ON)
OPTION(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." ON)

# option for whether warnings and errors should be printed
OPTION(FREEGLUT_PRINT_ERRORS "Lib prints errors to stderr" ON)
#MARK_AS_ADVANCED(FREEGLUT_PRINT_ERRORS)
OPTION(FREEGLUT_PRINT_WARNINGS "Lib prints warnings to stderr" ON)
#MARK_AS_ADVANCED(FREEGLUT_PRINT_WARNINGS)

# option to also copy .pdb files to install directory when executing
# INSTALL target
IF(MSVC)
    OPTION(INSTALL_PDB "Also install .pdb files" ON)
ELSE()
    SET(INSTALL_PDB OFF)
ENDIF()

# OpenGL ES support
OPTION(FREEGLUT_GLES "Use OpenGL ES (requires EGL)" OFF)

# option to build either as "glut" (ON) or "freeglut" (OFF)
IF(NOT WIN32)
    OPTION(FREEGLUT_REPLACE_GLUT "Be a replacement for GLUT" ON)
ENDIF()


SET(FREEGLUT_HEADERS
    ../../include/GL/freeglut.h
    ../../include/GL/freeglut_ext.h
    ../../include/GL/freeglut_std.h
    ../../include/GL/glut.h
)
SET(FREEGLUT_SRCS
    ${FREEGLUT_HEADERS}
    ../../src/fg_callbacks.c
    ../../src/fg_cursor.c
    ../../src/fg_display.c
    ../../src/fg_ext.c
    ../../src/fg_font_data.c
    ../../src/fg_gamemode.c
    ../../src/fg_geometry.c
    ../../src/fg_gl2.c
    ../../src/fg_gl2.h
    ../../src/fg_init.c
    ../../src/fg_init.h
    ../../src/fg_internal.h
    ../../src/fg_input_devices.c
    ../../src/fg_joystick.c
    ../../src/fg_main.c
    ../../src/fg_misc.c
    ../../src/fg_overlay.c
    ../../src/fg_spaceball.c
    ../../src/fg_state.c
    ../../src/fg_stroke_mono_roman.c
    ../../src/fg_stroke_roman.c
    ../../src/fg_structure.c
    ../../src/fg_teapot.c
    ../../src/fg_teapot_data.h
    ../../src/fg_videoresize.c
    ../../src/fg_window.c
)
# TODO: OpenGL ES requires a compatible version of these files:
IF(NOT FREEGLUT_GLES)
    LIST(APPEND FREEGLUT_SRCS
        ../../src/fg_font.c
        ../../src/fg_menu.c
    )
ELSE()
    LIST(APPEND FREEGLUT_SRCS
        ../../src/gles_stubs.c
    )
ENDIF()


LIST(APPEND FREEGLUT_SRCS
	../../src/x11/fg_cursor_x11.c
	../../src/x11/fg_ext_x11.c
	../../src/x11/fg_gamemode_x11.c
	../../src/x11/fg_glutfont_definitions_x11.c
	../../src/x11/fg_init_x11.c
	../../src/x11/fg_internal_x11.h
	../../src/x11/fg_input_devices_x11.c
	../../src/x11/fg_joystick_x11.c
	../../src/x11/fg_main_x11.c
	../../src/x11/fg_menu_x11.c
	../../src/x11/fg_spaceball_x11.c
	../../src/x11/fg_state_x11.c
	../../src/x11/fg_structure_x11.c
	../../src/x11/fg_window_x11.c
	../../src/x11/fg_xinput_x11.c
)
IF(NOT(FREEGLUT_GLES))
LIST(APPEND FREEGLUT_SRCS
	../../src/x11/fg_internal_x11_glx.h
	../../src/x11/fg_display_x11_glx.c
	../../src/x11/fg_state_x11_glx.c
	../../src/x11/fg_state_x11_glx.h
	../../src/x11/fg_window_x11_glx.c
	../../src/x11/fg_window_x11_glx.h
)
ENDIF()

IF(FREEGLUT_GLES)
    LIST(APPEND FREEGLUT_SRCS
        ../../src/egl/fg_internal_egl.h
        ../../src/egl/fg_display_egl.c
        ../../src/egl/fg_ext_egl.c
        ../../src/egl/fg_init_egl.c
        ../../src/egl/fg_init_egl.h
        ../../src/egl/fg_state_egl.c
        ../../src/egl/fg_state_egl.h
        ../../src/egl/fg_structure_egl.c
        ../../src/egl/fg_structure_egl.h
        ../../src/egl/fg_window_egl.c
        ../../src/egl/fg_window_egl.h
    )
ENDIF()

# For OpenGL ES (GLES): compile with -DFREEGLUT_GLES to cleanly
# bootstrap headers inclusion in freeglut_std.h; this constant also
# need to be defined in client applications (e.g. through pkg-config),
# but do use GLES constants directly for all other needs
# GLES1 and GLES2 libraries are compatible and can be co-linked.
IF(FREEGLUT_GLES)
  ADD_DEFINITIONS(-DFREEGLUT_GLES)
  LIST(APPEND LIBS GLESv2 GLESv1_CM EGL)
ELSE()
  FIND_PACKAGE(OpenGL REQUIRED)
  LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ENDIF()

# lib m for math, not needed on windows
IF (NOT WIN32)
    # For compilation:
    LIST(APPEND LIBS m)
    # For CHECK_FUNCTION_EXISTS:
    LIST(APPEND CMAKE_REQUIRED_LIBRARIES m)
ENDIF()

IF(WIN32)
    # hide insecure CRT warnings, common practice
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    IF(MSVC)
        SET( CMAKE_DEBUG_POSTFIX "d" )
    ENDIF(MSVC)
    
    # enable the use of Win2000 APIs (needed for really old compilers like MSVC6)
    ADD_DEFINITIONS(-D_WIN32_WINNT=0x0500)
    ADD_DEFINITIONS(-DWINVER=0x0500)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
  IF(NOT(ANDROID OR BLACKBERRY))
    # not setting -ansi as EGL/KHR headers doesn't support it
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
  ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCC)

INCLUDE(CheckIncludeFiles)
IF(UNIX AND NOT(ANDROID OR BLACKBERRY))
    FIND_PACKAGE(X11 REQUIRED)
    INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
    LIST(APPEND LIBS ${X11_LIBRARIES})
    IF(X11_Xrandr_FOUND)
        SET(HAVE_X11_EXTENSIONS_XRANDR_H TRUE)
        LIST(APPEND LIBS ${X11_Xrandr_LIB})
    ENDIF()
    IF(X11_xf86vmode_FOUND)
        SET(HAVE_X11_EXTENSIONS_XF86VMODE_H TRUE)
        LIST(APPEND LIBS ${X11_Xxf86vm_LIB})
    ENDIF()
    IF(X11_Xinput_FOUND)
        # Needed for multi-touch:
        CHECK_INCLUDE_FILES("${X11_Xinput_INCLUDE_PATH}/X11/extensions/XInput2.h" HAVE_X11_EXTENSIONS_XINPUT2_H)
        LIST(APPEND LIBS ${X11_Xinput_LIB})
    ENDIF()
ENDIF()
IF(ANDROID)
    # -landroid for ANativeWindow
    # -llog for native Android logging
    LIST(APPEND LIBS android log)
ELSEIF(BLACKBERRY)
    # -lbps for event loop
    # -screen for native screen
    LIST(APPEND LIBS bps screen)

    if(NOT PLAYBOOK)
        # -lslog2 for logging
        # -pps for low-level screen manipulation
        LIST(APPEND LIBS slog2 pps)
    ENDIF()
ENDIF()

SET(DEMO_LIBS ${OPENGL_glu_LIBRARY} ${LIBS})
# lib m for math, not needed on windows
IF (NOT WIN32)
    LIST(APPEND DEMO_LIBS m)
ENDIF()


add_executable(World world.c SOIL.c stb_image_aug.c image_DXT.c image_helper.c glmatrix.c)
TARGET_LINK_LIBRARIES(World ${DEMO_LIBS} glut)
#SET_TARGET_PROPERTIES(Fractals_static PROPERTIES COMPILE_FLAGS -DFREEGLUT_STATIC)
#IF(FREEGLUT_BUILD_SHARED_LIBS)
#    ADD_EXECUTABLE(Fractals fractals.c)
#    TARGET_LINK_LIBRARIES(Fractals ${DEMO_LIBS} freeglut)
#    IF(WIN32 AND MSVC)
#        SET_TARGET_PROPERTIES(Fractals PROPERTIES DEBUG_POSTFIX d)
#    ENDIF()
#ENDIF()
#IF(FREEGLUT_BUILD_STATIC_LIBS)
#    ADD_EXECUTABLE(Fractals static fractals.c)
#    TARGET_LINK_LIBRARIES(Fractals_static ${DEMO_LIBS} freeglut_static)
#    SET_TARGET_PROPERTIES(Fractals_static PROPERTIES COMPILE_FLAGS -DFREEGLUT_STATIC)
#    IF(WIN32 AND MSVC)
#        SET_TARGET_PROPERTIES(Fractals_static PROPERTIES DEBUG_POSTFIX d)
#    ENDIF()
#ENDIF()

