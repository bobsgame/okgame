# GNU Make project makefile autogenerated by Premake
ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release/GWEN-Static
  TARGETDIR  = ../../../lib/macosx/gmake
  TARGET     = $(TARGETDIR)/libgwen_static.a
  DEFINES   += -DNDEBUG -DGWEN_COMPILE_STATIC
  INCLUDES  += -I../../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -msse -O2 -ffast-math
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../../lib -L../../../lib/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug/GWEN-Static
  TARGETDIR  = ../../../lib/macosx/gmake
  TARGET     = $(TARGETDIR)/libgwen_staticd.a
  DEFINES   += -D_DEBUG -DGWEN_COMPILE_STATIC
  INCLUDES  += -I../../../include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -msse
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../../lib -L../../../lib/macosx
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/Anim.o \
	$(OBJDIR)/BaseRender.o \
	$(OBJDIR)/ControlList.o \
	$(OBJDIR)/DragAndDrop.o \
	$(OBJDIR)/events.o \
	$(OBJDIR)/Gwen.o \
	$(OBJDIR)/Hook.o \
	$(OBJDIR)/inputhandler.o \
	$(OBJDIR)/Skin.o \
	$(OBJDIR)/ToolTip.o \
	$(OBJDIR)/Utility.o \
	$(OBJDIR)/globber.o \
	$(OBJDIR)/fastlz.o \
	$(OBJDIR)/happyhttp.o \
	$(OBJDIR)/jpge.o \
	$(OBJDIR)/Alloc.o \
	$(OBJDIR)/LzFind.o \
	$(OBJDIR)/LzmaDec.o \
	$(OBJDIR)/LzmaEnc.o \
	$(OBJDIR)/LzmaLib.o \
	$(OBJDIR)/crc.o \
	$(OBJDIR)/smhash_md5.o \
	$(OBJDIR)/tinythread.o \
	$(OBJDIR)/unzip.o \
	$(OBJDIR)/zip.o \
	$(OBJDIR)/adler32.o \
	$(OBJDIR)/compress.o \
	$(OBJDIR)/crc32.o \
	$(OBJDIR)/deflate.o \
	$(OBJDIR)/gzclose.o \
	$(OBJDIR)/gzlib.o \
	$(OBJDIR)/gzread.o \
	$(OBJDIR)/gzwrite.o \
	$(OBJDIR)/infback.o \
	$(OBJDIR)/inffast.o \
	$(OBJDIR)/inflate.o \
	$(OBJDIR)/inftrees.o \
	$(OBJDIR)/trees.o \
	$(OBJDIR)/uncompr.o \
	$(OBJDIR)/zutil.o \
	$(OBJDIR)/Base.o \
	$(OBJDIR)/Console.o \
	$(OBJDIR)/ConsoleInput.o \
	$(OBJDIR)/Json.o \
	$(OBJDIR)/Tree.o \
	$(OBJDIR)/Changes.o \
	$(OBJDIR)/File.o \
	$(OBJDIR)/System.o \
	$(OBJDIR)/Image.o \
	$(OBJDIR)/JPEG.o \
	$(OBJDIR)/HTTP.o \
	$(OBJDIR)/Network.o \
	$(OBJDIR)/Socket.o \
	$(OBJDIR)/Platform_LINUX.o \
	$(OBJDIR)/Platform_NULL.o \
	$(OBJDIR)/Platform_OSX.o \
	$(OBJDIR)/Platform_WINDOWS.o \
	$(OBJDIR)/Mutex.o \
	$(OBJDIR)/Thread.o \
	$(OBJDIR)/Utility.o \
	$(OBJDIR)/Buffer.o \
	$(OBJDIR)/Math.o \
	$(OBJDIR)/String.o \
	$(OBJDIR)/String_Convert.o \
	$(OBJDIR)/String_Encode.o \
	$(OBJDIR)/String_File.o \
	$(OBJDIR)/String_Format.o \
	$(OBJDIR)/String_Sanitize.o \
	$(OBJDIR)/String_Test.o \
	$(OBJDIR)/String_To.o \
	$(OBJDIR)/String_URL.o \
	$(OBJDIR)/String_Util.o \
	$(OBJDIR)/CommandLine.o \
	$(OBJDIR)/Compression.o \
	$(OBJDIR)/CompressionLZMA.o \
	$(OBJDIR)/Hasher.o \
	$(OBJDIR)/PackFile.o \
	$(OBJDIR)/Processes.o \
	$(OBJDIR)/Time.o \
	$(OBJDIR)/Base.o \
	$(OBJDIR)/Button.o \
	$(OBJDIR)/Canvas.o \
	$(OBJDIR)/CheckBox.o \
	$(OBJDIR)/CollapsibleCategory.o \
	$(OBJDIR)/ColorControls.o \
	$(OBJDIR)/ColorPicker.o \
	$(OBJDIR)/ComboBox.o \
	$(OBJDIR)/CrossSplitter.o \
	$(OBJDIR)/DockBase.o \
	$(OBJDIR)/DockedTabControl.o \
	$(OBJDIR)/Dragger.o \
	$(OBJDIR)/GroupBox.o \
	$(OBJDIR)/HorizontalScrollBar.o \
	$(OBJDIR)/HorizontalSlider.o \
	$(OBJDIR)/HorizontalSplitter.o \
	$(OBJDIR)/HSVColorPicker.o \
	$(OBJDIR)/ImagePanel.o \
	$(OBJDIR)/Label.o \
	$(OBJDIR)/LabelClickable.o \
	$(OBJDIR)/ListBox.o \
	$(OBJDIR)/Menu.o \
	$(OBJDIR)/MenuItem.o \
	$(OBJDIR)/MenuStrip.o \
	$(OBJDIR)/NumericUpDown.o \
	$(OBJDIR)/PageControl.o \
	$(OBJDIR)/ProgressBar.o \
	$(OBJDIR)/Properties.o \
	$(OBJDIR)/PropertyTree.o \
	$(OBJDIR)/RadioButton.o \
	$(OBJDIR)/RadioButtonController.o \
	$(OBJDIR)/Rectangle.o \
	$(OBJDIR)/ResizableControl.o \
	$(OBJDIR)/Resizer.o \
	$(OBJDIR)/RichLabel.o \
	$(OBJDIR)/ScrollBar.o \
	$(OBJDIR)/ScrollBarBar.o \
	$(OBJDIR)/ScrollBarButton.o \
	$(OBJDIR)/ScrollControl.o \
	$(OBJDIR)/Slider.o \
	$(OBJDIR)/SplitterBar.o \
	$(OBJDIR)/TabButton.o \
	$(OBJDIR)/TabControl.o \
	$(OBJDIR)/TabStrip.o \
	$(OBJDIR)/Text.o \
	$(OBJDIR)/TextBox.o \
	$(OBJDIR)/TextBoxNumeric.o \
	$(OBJDIR)/TreeControl.o \
	$(OBJDIR)/TreeNode.o \
	$(OBJDIR)/VerticalScrollBar.o \
	$(OBJDIR)/VerticalSlider.o \
	$(OBJDIR)/WindowCanvas.o \
	$(OBJDIR)/WindowControl.o \
	$(OBJDIR)/FileOpen.o \
	$(OBJDIR)/FileSave.o \
	$(OBJDIR)/FolderOpen.o \
	$(OBJDIR)/Query.o \
	$(OBJDIR)/AllegroPlatform.o \
	$(OBJDIR)/Null.o \
	$(OBJDIR)/Windows.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking GWEN-Static
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning GWEN-Static
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/Anim.o: ../../../src/Anim.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/BaseRender.o: ../../../src/BaseRender.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ControlList.o: ../../../src/ControlList.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DragAndDrop.o: ../../../src/DragAndDrop.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/events.o: ../../../src/events.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Gwen.o: ../../../src/Gwen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Hook.o: ../../../src/Hook.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/inputhandler.o: ../../../src/inputhandler.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Skin.o: ../../../src/Skin.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ToolTip.o: ../../../src/ToolTip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Utility.o: ../../../src/Utility.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/globber.o: ../../../src/3rdParty/globber.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/fastlz.o: ../../../src/3rdParty/fastlz/fastlz.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/happyhttp.o: ../../../src/3rdParty/happyhttp/happyhttp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/jpge.o: ../../../src/3rdParty/jpegcompressor/jpge.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Alloc.o: ../../../src/3rdParty/lzma/Alloc.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LzFind.o: ../../../src/3rdParty/lzma/LzFind.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LzmaDec.o: ../../../src/3rdParty/lzma/LzmaDec.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LzmaEnc.o: ../../../src/3rdParty/lzma/LzmaEnc.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LzmaLib.o: ../../../src/3rdParty/lzma/LzmaLib.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/crc.o: ../../../src/3rdParty/smhasher/crc.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/smhash_md5.o: ../../../src/3rdParty/smhasher/smhash_md5.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/tinythread.o: ../../../src/3rdParty/tinythreadpp/tinythread.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/unzip.o: ../../../src/3rdParty/xzip/unzip.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/zip.o: ../../../src/3rdParty/xzip/zip.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/adler32.o: ../../../src/3rdParty/zlib/adler32.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/compress.o: ../../../src/3rdParty/zlib/compress.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/crc32.o: ../../../src/3rdParty/zlib/crc32.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/deflate.o: ../../../src/3rdParty/zlib/deflate.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/gzclose.o: ../../../src/3rdParty/zlib/gzclose.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/gzlib.o: ../../../src/3rdParty/zlib/gzlib.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/gzread.o: ../../../src/3rdParty/zlib/gzread.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/gzwrite.o: ../../../src/3rdParty/zlib/gzwrite.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/infback.o: ../../../src/3rdParty/zlib/infback.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/inffast.o: ../../../src/3rdParty/zlib/inffast.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/inflate.o: ../../../src/3rdParty/zlib/inflate.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/inftrees.o: ../../../src/3rdParty/zlib/inftrees.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/trees.o: ../../../src/3rdParty/zlib/trees.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/uncompr.o: ../../../src/3rdParty/zlib/uncompr.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/zutil.o: ../../../src/3rdParty/zlib/zutil.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Base.o: ../../../src/Bootil/Base.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Console.o: ../../../src/Bootil/Console/Console.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ConsoleInput.o: ../../../src/Bootil/Console/ConsoleInput.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Json.o: ../../../src/Bootil/Data/Json.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Tree.o: ../../../src/Bootil/Data/Tree.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Changes.o: ../../../src/Bootil/File/Changes.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/File.o: ../../../src/Bootil/File/File.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/System.o: ../../../src/Bootil/File/System.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Image.o: ../../../src/Bootil/Image/Image.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/JPEG.o: ../../../src/Bootil/Image/JPEG.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HTTP.o: ../../../src/Bootil/Network/HTTP.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Network.o: ../../../src/Bootil/Network/Network.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Socket.o: ../../../src/Bootil/Network/Socket.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Platform_LINUX.o: ../../../src/Bootil/Platform/Platform_LINUX.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Platform_NULL.o: ../../../src/Bootil/Platform/Platform_NULL.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Platform_OSX.o: ../../../src/Bootil/Platform/Platform_OSX.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Platform_WINDOWS.o: ../../../src/Bootil/Platform/Platform_WINDOWS.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Mutex.o: ../../../src/Bootil/Threads/Mutex.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Thread.o: ../../../src/Bootil/Threads/Thread.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Utility.o: ../../../src/Bootil/Threads/Utility.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Buffer.o: ../../../src/Bootil/Types/Buffer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Math.o: ../../../src/Bootil/Types/Math.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String.o: ../../../src/Bootil/Types/String.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Convert.o: ../../../src/Bootil/Types/String_Convert.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Encode.o: ../../../src/Bootil/Types/String_Encode.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_File.o: ../../../src/Bootil/Types/String_File.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Format.o: ../../../src/Bootil/Types/String_Format.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Sanitize.o: ../../../src/Bootil/Types/String_Sanitize.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Test.o: ../../../src/Bootil/Types/String_Test.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_To.o: ../../../src/Bootil/Types/String_To.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_URL.o: ../../../src/Bootil/Types/String_URL.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/String_Util.o: ../../../src/Bootil/Types/String_Util.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CommandLine.o: ../../../src/Bootil/Utility/CommandLine.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Compression.o: ../../../src/Bootil/Utility/Compression.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CompressionLZMA.o: ../../../src/Bootil/Utility/CompressionLZMA.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Hasher.o: ../../../src/Bootil/Utility/Hasher.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/PackFile.o: ../../../src/Bootil/Utility/PackFile.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Processes.o: ../../../src/Bootil/Utility/Processes.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Time.o: ../../../src/Bootil/Utility/Time.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Base.o: ../../../src/Controls/Base.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Button.o: ../../../src/Controls/Button.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Canvas.o: ../../../src/Controls/Canvas.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CheckBox.o: ../../../src/Controls/CheckBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CollapsibleCategory.o: ../../../src/Controls/CollapsibleCategory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ColorControls.o: ../../../src/Controls/ColorControls.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ColorPicker.o: ../../../src/Controls/ColorPicker.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ComboBox.o: ../../../src/Controls/ComboBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/CrossSplitter.o: ../../../src/Controls/CrossSplitter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DockBase.o: ../../../src/Controls/DockBase.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/DockedTabControl.o: ../../../src/Controls/DockedTabControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Dragger.o: ../../../src/Controls/Dragger.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/GroupBox.o: ../../../src/Controls/GroupBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HorizontalScrollBar.o: ../../../src/Controls/HorizontalScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HorizontalSlider.o: ../../../src/Controls/HorizontalSlider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HorizontalSplitter.o: ../../../src/Controls/HorizontalSplitter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/HSVColorPicker.o: ../../../src/Controls/HSVColorPicker.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ImagePanel.o: ../../../src/Controls/ImagePanel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Label.o: ../../../src/Controls/Label.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/LabelClickable.o: ../../../src/Controls/LabelClickable.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ListBox.o: ../../../src/Controls/ListBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Menu.o: ../../../src/Controls/Menu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MenuItem.o: ../../../src/Controls/MenuItem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/MenuStrip.o: ../../../src/Controls/MenuStrip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/NumericUpDown.o: ../../../src/Controls/NumericUpDown.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/PageControl.o: ../../../src/Controls/PageControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ProgressBar.o: ../../../src/Controls/ProgressBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Properties.o: ../../../src/Controls/Properties.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/PropertyTree.o: ../../../src/Controls/PropertyTree.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RadioButton.o: ../../../src/Controls/RadioButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RadioButtonController.o: ../../../src/Controls/RadioButtonController.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Rectangle.o: ../../../src/Controls/Rectangle.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ResizableControl.o: ../../../src/Controls/ResizableControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Resizer.o: ../../../src/Controls/Resizer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/RichLabel.o: ../../../src/Controls/RichLabel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBar.o: ../../../src/Controls/ScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBarBar.o: ../../../src/Controls/ScrollBarBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollBarButton.o: ../../../src/Controls/ScrollBarButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ScrollControl.o: ../../../src/Controls/ScrollControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Slider.o: ../../../src/Controls/Slider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SplitterBar.o: ../../../src/Controls/SplitterBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabButton.o: ../../../src/Controls/TabButton.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabControl.o: ../../../src/Controls/TabControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TabStrip.o: ../../../src/Controls/TabStrip.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Text.o: ../../../src/Controls/Text.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TextBox.o: ../../../src/Controls/TextBox.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TextBoxNumeric.o: ../../../src/Controls/TextBoxNumeric.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TreeControl.o: ../../../src/Controls/TreeControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/TreeNode.o: ../../../src/Controls/TreeNode.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/VerticalScrollBar.o: ../../../src/Controls/VerticalScrollBar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/VerticalSlider.o: ../../../src/Controls/VerticalSlider.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/WindowCanvas.o: ../../../src/Controls/WindowCanvas.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/WindowControl.o: ../../../src/Controls/WindowControl.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FileOpen.o: ../../../src/Controls/Dialog/FileOpen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FileSave.o: ../../../src/Controls/Dialog/FileSave.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/FolderOpen.o: ../../../src/Controls/Dialog/FolderOpen.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Query.o: ../../../src/Controls/Dialog/Query.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/AllegroPlatform.o: ../../../src/Platforms/AllegroPlatform.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Null.o: ../../../src/Platforms/Null.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Windows.o: ../../../src/Platforms/Windows.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
