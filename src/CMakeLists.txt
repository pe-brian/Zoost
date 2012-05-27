#################################################################################
#
# ZinLibs C++ Libraries
# Copyright (c) 2011-2012 ZinTech
# 
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 
# 3. This notice may not be removed or altered from any source distribution.
#
#################################################################################
 
set(SRCDIR ${ROOTDIR}/src)

set( 
    SOURCES
    ${SRCDIR}/Rect.cpp
    ${SRCDIR}/Segment.cpp
    ${SRCDIR}/Line.cpp
    ${SRCDIR}/Curve.cpp
    ${SRCDIR}/Geom.cpp
    ${SRCDIR}/Transform.cpp
    ${SRCDIR}/Transformable.cpp
    ${SRCDIR}/Math.cpp
    ${SRCDIR}/Triangle.cpp
    ${SRCDIR}/Vertex.cpp
    ${SRCDIR}/Liaison.cpp
    ${SRCDIR}/Face.cpp
    ${SRCDIR}/Converter.cpp
)

add_library( 
  zoost
  SHARED
  ${SOURCES}
)

install(
    TARGETS zoost
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
