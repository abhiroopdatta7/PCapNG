# Makefile
# A7d

VERSION := local
export PCapNG_VERSION = $(VERSION)
BUILD_DIR := build
BUILD_TYPE := Debug
.DEFAULT_GOAL := all

${BUILD_DIR}:
	# cmake --no-warn-unused-cli 					\
	# 	  -DBUILD_SHARED_LIBS=ON 					\
	# 	  -DCMAKE_POSITION_INDEPENDENT_CODE=ON 		\
	# 	  -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} 	\
	# 	  -H./ -B${BUILD_DIR} 						\
	# 	  -G Ninja
	conan install . -s build_type=${BUILD_TYPE} --install-folder ${BUILD_DIR} --build=missing

all: ${BUILD_DIR}
	# cmake --build ${BUILD_DIR} --target all
	conan build . --build-folder ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}
	@echo "Cleaned: ${BUILD_DIR}"
