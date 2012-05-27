cmake_minimum_required ( VERSION 2.8)

if(NOT ZOOST_CONFIG_DEFINED)
	set(ZOOST_CONFIG_DEFINED 1)
	configure_file(
	    "${ROOTDIR}/cmake/cmake_uninstall.cmake.in"
	    "${ROOTDIR}/cmake_uninstall.cmake"
	    IMMEDIATE @ONLY)

	add_custom_target(uninstall
	    COMMAND ${CMAKE_COMMAND} -P
	${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

	set(CMAKE_MODULE_PATH ${ROOTDIR}/cmake/modules)

	set(EXECUTABLE_OUTPUT_PATH ${ROOTDIR}/examples/bin)
	set(LIBRARY_OUTPUT_PATH ${ROOTDIR}/lib)

	# detect the OS
	if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	    set(WINDOWS 1)
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	    set(LINUX 1)
	elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	    set(MACOSX 1)
	else()
	    message(WARNING "Unsupported operating system")
	    return()
	endif()

	find_package (OpenGL REQUIRED)
endif()
