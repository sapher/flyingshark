# - Locate SDL_gfx library
# This module defines
#  SDL_GFX_LIBRARY, the library to link against
#  SDL_GFX_FOUND, if false, do not try to link to SDL
#  SDL_GFX_INCLUDE_DIR, where to find SDL/SDL_gfxPrimitives.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Olivier DOLE. This was copied from the FindSDL_image.cmake
# module.
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of
# SDL_GFX_LIBRARY to override this selection.
FIND_PATH(SDL_GFX_INCLUDE_DIR SDL_gfxPrimitives.h
        $ENV{SDL_GFXDIR}/include
        $ENV{SDLDIR}/include
        ~/Library/Frameworks/SDL_gfx.framework/Headers
        /Library/Frameworks/SDL_gfx.framework/Headers
        /usr/local/include/SDL12
        /usr/local/include/SDL11 # FreeBSD ports
        /usr/include/SDL12
        /usr/include/SDL11
        /usr/local/include
        /usr/include
        /sw/include
        /opt/local/include
        /opt/csw/include
        /opt/include
        PATH_SUFFIXES SDL
        )
# I'm not sure if I should do a special casing for Apple. It is
# unlikely that other Unix systems will find the framework path.
# But if they do ([Next|Open|GNU]Step?),
# do they want the -framework option also?
IF(${SDL_GFX_INCLUDE_DIR} MATCHES ".framework")
    # Extract the path the framework resides in so we can use it for the -F flag
    STRING(REGEX REPLACE "(.*)/.*\\.framework/.*" "\\1" SDL_GFX_FRAMEWORK_PATH_TEMP ${SDL_GFX_INCLUDE_DIR})
    IF("${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/Library/Frameworks"
            OR "${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/System/Library/Frameworks"
            )
        # String is in default search path, don't need to use -F
        SET(SDL_GFX_LIBRARY "-framework SDL_gfx" CACHE STRING "SDL_gfx framework for OSX")
    ELSE("${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/Library/Frameworks"
            OR "${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/System/Library/Frameworks"
            )
        # String is not /Library/Frameworks, need to use -F
        SET(SDL_GFX_LIBRARY "-F${SDL_GFX_FRAMEWORK_PATH_TEMP} -framework SDL_gfx" CACHE STRING "SDL_gfx framework for OSX")
    ENDIF("${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/Library/Frameworks"
            OR "${SDL_GFX_FRAMEWORK_PATH_TEMP}" STREQUAL "/System/Library/Frameworks"
            )
    # Clear the temp variable so nobody can see it
    SET(SDL_GFX_FRAMEWORK_PATH_TEMP "" CACHE INTERNAL "")

ELSE(${SDL_GFX_INCLUDE_DIR} MATCHES ".framework")
    FIND_LIBRARY(SDL_GFX_LIBRARY
            NAMES SDL_gfx
            PATHS
            $ENV{SDL_GFXDIR}/lib
            $ENV{SDLDIR}/lib
            /usr/local/lib
            /usr/lib
            /sw/lib
            /opt/local/lib
            /opt/csw/lib
            /opt/lib
            )
ENDIF(${SDL_GFX_INCLUDE_DIR} MATCHES ".framework")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL_gfx REQUIRED_VARS SDL_GFX_LIBRARY SDL_GFX_INCLUDE_DIR)
