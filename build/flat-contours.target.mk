# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := flat-contours
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=flat-contours' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Debug := \
	-I/home/sevenflash/.node-gyp/6.6.0/include/node \
	-I/home/sevenflash/.node-gyp/6.6.0/src \
	-I/home/sevenflash/.node-gyp/6.6.0/deps/uv/include \
	-I/home/sevenflash/.node-gyp/6.6.0/deps/v8/include

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=flat-contours' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++0x

INCS_Release := \
	-I/home/sevenflash/.node-gyp/6.6.0/include/node \
	-I/home/sevenflash/.node-gyp/6.6.0/src \
	-I/home/sevenflash/.node-gyp/6.6.0/deps/uv/include \
	-I/home/sevenflash/.node-gyp/6.6.0/deps/v8/include

OBJS := \
	$(obj).target/$(TARGET)/flat-contours.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS :=

$(obj).target/flat-contours.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/flat-contours.node: LIBS := $(LIBS)
$(obj).target/flat-contours.node: TOOLSET := $(TOOLSET)
$(obj).target/flat-contours.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/flat-contours.node
# Add target alias
.PHONY: flat-contours
flat-contours: $(builddir)/flat-contours.node

# Copy this to the executable output path.
$(builddir)/flat-contours.node: TOOLSET := $(TOOLSET)
$(builddir)/flat-contours.node: $(obj).target/flat-contours.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/flat-contours.node
# Short alias for building this executable.
.PHONY: flat-contours.node
flat-contours.node: $(obj).target/flat-contours.node $(builddir)/flat-contours.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/flat-contours.node

