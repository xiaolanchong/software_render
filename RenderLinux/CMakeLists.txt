# CMakeList.txt : CMake project for RenderLinux, include source and define
# project specific logic here.
#

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (RenderLinux)

set(_sources
	"RenderLinux.cpp" 
	"RenderLinux.h"
		
	"PropertyMapImpl.h"
	"PropertyMapImpl.cpp"

	"XDeviceContext.h"
	"XDeviceContext.cpp"
)

# Add source to this project's executable.
add_executable (RenderLinux ${_sources})

set_property(TARGET RenderLinux PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
target_link_libraries(RenderLinux RenderLib X11)
