cmake_minimum_required(VERSION 2.8.11)
project(ep_keyview CXX)

set(KEYVIEW_MAJOR_VERSION 3)
set(KEYVIEW_MINOR_VERSION 5)
set(KEYVIEW_PATCH_VERSION 0)
set(KEYVIEW_BUILD_NO 002)

if (NOT EXTERNAL_PREFIX)
    if("${PLATFORM_TYPE}" STREQUAL "Win32")
        set(EXTERNAL_PREFIX "${PROJECT_SOURCE_DIR}/../external32")
    else()
        set(EXTERNAL_PREFIX "${PROJECT_SOURCE_DIR}/../external")
    endif()
endif()


set(OBJECT_RESOLVER_MODULE 1)
add_definitions(-DOBJECT_RESOLVER_MODULE)
if (NOT WIN32)
    
    set(CMAKE_CXX_FLAGS "-Wall -pthread -std=c++11 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")

    if(APPLE)
        set(CMAKE_MACOSX_RPATH 1)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.9")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -Wno-unused-local-typedef -Wno-macro-redefined")
        
        set(CPACK_PACKAGE_ARCHITECTURE OSX-x86_64)
    else()
        set(CPACK_PACKAGE_ARCHITECTURE ${KERNEL_MACHINE})
    endif()
    
else()
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /MD")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF")
    if (NOT TOOLSET)
        set(TOOLSET "v140_xp")
    endif()
    set(EXTRA_P "/p:MultiProcessorCompilation=true /p:PlatformToolset=${TOOLSET}")


    if ("${PLATFORM_TYPE}" STREQUAL x64)
        set(CPACK_PACKAGE_ARCHITECTURE win32-x86_64)
    else()
        set(CPACK_PACKAGE_ARCHITECTURE win32-x86)
    endif()
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/export)
set(CMAKE_INSTALL_CONFIG_NAME ${CMAKE_BUILD_TYPE})
set(CPACK_PACKAGE_VENDOR "EndpointKeyView Inc.")
set(CPACK_PACKAGE_VERSION ${KEYVIEW_MAJOR_VERSION}.${KEYVIEW_MINOR_VERSION}.${KEYVIEW_PATCH_VERSION}-${KEYVIEW_BUILD_NO})
set(CPACK_PACKAGE_VERSION_MAJOR ${KEYVIEW_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${KEYVIEW_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${KEYVIEW_PATCH_VERSION})
set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE})
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_PACKAGING_INSTALL_PREFIX "")
set(CPACK_COMPONENTS_ALL "dev")
set(CPACK_GENERATOR TGZ)
include(CPack)


include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${EXTERNAL_PREFIX}/include)
link_directories(${EXTERNAL_PREFIX}/lib)

if(NOT WIN32)
    include_directories("/usr/local/include")
    link_directories("/usr/local/lib/")
    link_libraries(
        -lssl
        -lcrypto 
        -lpthread 
        -lboost_thread 
        -lboost_filesystem 
        -lboost_system 
        -lboost_program_options 
        -lboost_chrono 
        -lboost_iostreams 
        -lboost_locale 
        -lboost_regex 
        -lboost_date_time 
        -lboost_atomic
        -llog4cxx )   
elseif(WIN32)
    if (MSVC14)
        set(Boost_LIBRARIES ${EXTERNAL_LIB_PATH}/libboost_thread-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_filesystem-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_system-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_program_options-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_chrono-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_date_time-vc140-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_regex-vc140-mt-1_58.lib
            )
    else()
        set(Boost_LIBRARIES ${EXTERNAL_LIB_PATH}/libboost_thread-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_filesystem-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_system-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_program_options-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_chrono-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_date_time-vc120-mt-1_58.lib
            ${EXTERNAL_LIB_PATH}/libboost_regex-vc120-mt-1_58.lib
            )
    endif()
        link_libraries(Psapi.lib
                log4cxx.lib
                kernel32.lib
                user32.lib
                gdi32.lib
                winspool.lib
                comdlg32.lib
                advapi32.lib
                shell32.lib
                ole32.lib
                oleaut32.lib
                uuid.lib
                odbc32.lib
                odbccp32.lib
                libeay32.lib
                ssleay32.lib
                Crypt32.lib
                libthrift.lib
                Rasapi32.lib
                Shlwapi.lib
        )
endif()

add_subdirectory(src)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/etc/EndpointKeyView.ini DESTINATION etc COMPONENT "dev")