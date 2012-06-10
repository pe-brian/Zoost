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
