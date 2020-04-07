# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS += -Iinclude -Ithirdparty/tinyfsm/include -Ithirdparty/sml/include -Ithirdparty/sigslot/include

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

ifdef DEBUG
        CXXFLAGS += -g
endif


# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)
SOURCES += $(wildcard src/cvwizard/*.cpp)
SOURCES += $(wildcard src/cvwizard/controller/*.cpp)
SOURCES += $(wildcard src/cvwizard/sm/keyboard/*.cpp)
SOURCES += $(wildcard src/cvwizard/ui/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

CXXFLAGS := $(filter-out -std=c++11,$(CXXFLAGS))
CXXFLAGS += -std=c++14
