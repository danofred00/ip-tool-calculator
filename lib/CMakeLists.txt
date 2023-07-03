
set(LIB_BUILD_TYPE SHARED)
set(LIB_SOURCEDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_HEADERDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${LIB_SOURCEDIR}/utils.cpp ${LIB_HEADERDIR}/utils.h
    ${LIB_SOURCEDIR}/ipv4.cpp ${LIB_HEADERDIR}/ipv4.h
    ${LIB_SOURCEDIR}/netip.cpp ${LIB_HEADERDIR}/netip.h
    ${LIB_SOURCEDIR}/subnet.cpp ${LIB_HEADERDIR}/subnet.h)

add_library(net ${LIB_BUILD_TYPE} ${SOURCES})
target_include_directories(net PUBLIC ${LIB_HEADERDIR})

#add_library(utils ${LIB_BUILD_TYPE} ${LIB_SOURCEDIR}/utils.c ${LIB_HEADERDIR}/utils.h)
#target_include_directories(utils INTERFACE ${LIB_HEADERDIR})

## IPV4 lib
#add_library(ipv4 ${LIB_BUILD_TYPE} ${LIB_SOURCEDIR}/ipv4.c ${LIB_HEADERDIR}/ipv4.h)
#target_include_directories(ipv4 PRIVATE ${LIB_HEADERDIR})

## NETIP lib
#add_library(netip ${LIB_BUILD_TYPE} ${LIB_SOURCEDIR}/netip.c ${LIB_HEADERDIR}/netip.h)
#target_link_libraries(netip ipv4)
#target_include_directories(netip PRIVATE ${LIB_HEADERDIR})

## SUBNET lib
#add_library(subnet ${LIB_BUILD_TYPE} ${LIB_SOURCEDIR}/subnet.c ${LIB_HEADERDIR}/subnet.h)
#target_link_libraries(subnet ipv4 netip utils)
#target_include_directories(subnet PRIVATE ${LIB_HEADERDIR})
