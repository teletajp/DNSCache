add_library(${PROJECT_NAME})


set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROJECT_NAME}
PRIVATE 
	$<$<CXX_COMPILER_ID:GNU>: -Wpedantic -Wall -Wextra -O3> # Флаги для GNU компилятора
	$<$<CXX_COMPILER_ID:AppleClang>: -Wpedantic -Wall -Wextra -O3> # Флаги для apple clang компилятора
	$<$<CXX_COMPILER_ID:MSVC>: -D_CRT_SECURE_NO_WARNINGS /Zi /std:c++14>
	#$<$<CXX_COMPILER_ID:MSVC>:/W3 /WX /MT -D_CRT_SECURE_NO_WARNINGS -DHAVE_REMOTE>
) # Флаги для MSVC компилятора

target_sources(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/dns_cache.h
	${CMAKE_CURRENT_SOURCE_DIR}/dns_cache.cpp
)