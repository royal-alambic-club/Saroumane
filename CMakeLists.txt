cmake_minimum_required(VERSION 3.6)
project(RAC_RenifleurDuXul)
set (CMAKE_CXX_STANDARD 14)
add_definitions( "-Wall -pedantic -W" )

set(gtest_SOURCE_DIR, third_party/googletest/googletest/include/)
set(SRC_LOG_TEST_DIRECTORY "test/log_unit_test")

################################
# GTest
################################

enable_testing()
add_subdirectory(third_party/googletest)
include_directories(${gtest_SOURCE_DIR})

################################
# Unit Tests
################################

# Add test cpp file
add_executable( runUnitTests test/log_unit_test/log_unit_test.cpp test/conf_unit_test/conf_unit_test.cpp src/conf/JsonConfHandler.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )


################################
# END GTest
################################


################################
# Json Boost
################################

set(INCLUDE_JSONBOOST_DIR, third_party/property_tree/include/)

################################
# END Json Boost
################################

option(WITH_FILTER "Filter" 1) #FILTER SET VALUE TO 0 TO UNABLE THE FILTER

if(WITH_FILTER)
      set(INCLUDE_FILTER_DIRECTORY "include/filter/")
      include_directories(${INCLUDE_FILTER_DIRECTORY})
      set(filter_src "src/filter/FilterOutput.cpp")
      add_definitions(-DRAC_FILTER)
else() 
      set(filter_src "")
      endif()

set(INCLUDE_LOG_DIRECTORY "include/log/")
set(INCLUDE_TIME_DIRECTORY "include/time/")
set(INCLUDE_SOCKET_DIRECTORY "include/socket/")
set(INCLUDE_CONF_DIRECTORY "include/conf/")
set(INCLUDE_ERROR_DIRECTORY "include/error/")
set(INCLUDE_PROTOCOLS_DIRECTORY "include/protocols/")
set(INCLUDE_DECODER_DIRECTORY "include/decoder/")
set(INCLUDE_TS_DIRECTORY "include/thread_safe/")
set(INCLUDE_HACK_DIRECTORY "include/hacker/")
set(EXECUTABLE_OUTPUT_PATH bin)

    add_executable(

	    RAC_RenifleurDuXul

	    main.cpp

	    ${filter_src}
	    src/log/LogHandler.cpp
	    include/log/LogHandler.h
	    include/log/LogInstanceInitializer.h

	    include/time/TimeHandler.h

	    src/socket/RawSocket.cpp
	    src/socket/ISocket.cpp
	    include/socket/ISocket.h
	    include/socket/RawSocket.h

	    src/conf/JsonConfHandler.cpp
	    include/conf/JsonConfHandler.h
	    include/conf/JsonConfInstanceInitializer.h

	    src/socket/RawSocketProducer.cpp
	    src/socket/RawSocketListener.cpp
	    include/socket/RawSocketProducer.h
	    include/socket/RawSocketListener.h

	    src/error/ErrorSocket.cpp
	    include/error/ErrorSocket.h

	    src/socket/RawSocketConsumer.cpp
	    include/socket/RawSocketConsumer.h

	    src/protocols/ProtocolIP.cpp
	    src/protocols/ProtocolEthernet.cpp
	    src/protocols/ProtocolARP.cpp
	    src/protocols/ProtocolTCP.cpp
	    src/protocols/ProtocolUDP.cpp
	    include/protocols/ProtocolTCP.h
	    include/protocols/ProtocolUDP.h
	    include/protocols/ProtocolARP.h
	    include/protocols/IProtocol.h
	    include/protocols/ProtocolIP.h
	    include/protocols/ProtocolsDefinition.h
	    include/protocols/ProtocolEthernet.h
	    include/protocols/ProtocolsHeader.h
	    src/decoder/DecoderLayer.cpp
	    include/decoder/DecoderLayer.h

	    include/thread_safe/TSqueue.h

	    src/hacker/HackerDuXul.cpp
	    src/hacker/HackerARP.cpp
	    src/hacker/IHackerAttack.cpp
	    include/hacker/HackerDuXul.h
	    include/hacker/HackerARP.h
	    include/hacker/IHackerAttack.h
	    include/hacker/AttacksDefinition.h
	    include/hacker/AttacksHeader.h
	    )

TARGET_LINK_LIBRARIES( RAC_RenifleurDuXul
pthread
)
include_directories(${INCLUDE_LOG_DIRECTORY} ${gtest_SOURCE_DIR} ${INCLUDE_TIME_DIRECTORY} 
		    ${INCLUDE_SOCKET_DIRECTORY} ${INCLUDE_CONF_DIRECTORY} ${INCLUDE_JSONBOOST_DIR} 
		    ${INCLUDE_ERROR_DIRECTORY} ${INCLUDE_PROTOCOLS_DIRECTORY}
		    ${INCLUDE_DECODER_DIRECTORY} ${INCLUDE_TS_DIRECTORY} ${INCLUDE_HACK_DIRECTORY})




