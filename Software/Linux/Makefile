# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_46060D4=1 -DJUCE_APP_VERSION=1.0.0 -DJUCE_APP_VERSION_HEX=0x10000 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../JuceLibraryCode -I../JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -I../JsoncppLibrary/ -I../LuaLibrary/include -W -Wall -Wextra $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -lGL -ldl -lpthread -lrt -llua -L../LuaLibrary $(LDFLAGS)

  TARGET := BardeClient
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_46060D4=1 -DJUCE_APP_VERSION=1.0.0 -DJUCE_APP_VERSION_HEX=0x10000 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../JuceLibraryCode -I../JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -O3 -I../JsoncppLibrary/ -I../LuaLibrary/include -W -Wall -Wextra $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -fvisibility=hidden $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -lGL -ldl -lpthread -lrt -llua -L../LuaLibrary $(LDFLAGS)

  TARGET := BardeClient
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/ThreadPool_dd677260.o \
  $(JUCE_OBJDIR)/Tools_90322e8b.o \
  $(JUCE_OBJDIR)/SynchronizeManager_e9a9ccd7.o \
  $(JUCE_OBJDIR)/AView_4c0b412f.o \
  $(JUCE_OBJDIR)/HomePage_9fb9146f.o \
  $(JUCE_OBJDIR)/ViewManager_527c33d1.o \
  $(JUCE_OBJDIR)/Chords_8c89bd4e.o \
  $(JUCE_OBJDIR)/Disposition_da31b1aa.o \
  $(JUCE_OBJDIR)/MusicGenerator_b8a25e65.o \
  $(JUCE_OBJDIR)/ObjectMarkov_d034efca.o \
  $(JUCE_OBJDIR)/Resolution_ca4e12e3.o \
  $(JUCE_OBJDIR)/StyleSettings_ca3d60e7.o \
  $(JUCE_OBJDIR)/Instrument_44b59881.o \
  $(JUCE_OBJDIR)/jsoncpp_7b1ce7b0.o \
  $(JUCE_OBJDIR)/ADatabasManager_7f537f57.o \
  $(JUCE_OBJDIR)/SQLiteManager_99d2bf74.o \
  $(JUCE_OBJDIR)/AEncryptionManager_13e06cc8.o \
  $(JUCE_OBJDIR)/SSLManager_f25fe680.o \
  $(JUCE_OBJDIR)/AGraphManager_4508c7ea.o \
  $(JUCE_OBJDIR)/JuceManager_8121b3aa.o \
  $(JUCE_OBJDIR)/MainComponent_fb729fae.o \
  $(JUCE_OBJDIR)/MainWindow_1a69e1a9.o \
  $(JUCE_OBJDIR)/MusicStyleButton_39681cbe.o \
  $(JUCE_OBJDIR)/AMidiManager_545b688.o \
  $(JUCE_OBJDIR)/Midi_8be1d87e.o \
  $(JUCE_OBJDIR)/MidiManager_7f6bb1d9.o \
  $(JUCE_OBJDIR)/ASocketManager_7ac741c8.o \
  $(JUCE_OBJDIR)/TCPSocket_b03f596f.o \
  $(JUCE_OBJDIR)/ASoundManager_564990e8.o \
  $(JUCE_OBJDIR)/JuceSound_212948eb.o \
  $(JUCE_OBJDIR)/Authentification_99239255.o \
  $(JUCE_OBJDIR)/CmdManager_1dc6efad.o \
  $(JUCE_OBJDIR)/Configuration_a9102926.o \
  $(JUCE_OBJDIR)/Core_d0bb77f9.o \
  $(JUCE_OBJDIR)/FileManager_b3cf2001.o \
  $(JUCE_OBJDIR)/main_e838ccf3.o \
  $(JUCE_OBJDIR)/Music_bf331dd5.o \
  $(JUCE_OBJDIR)/MusicParameters_1a7d3edf.o \
  $(JUCE_OBJDIR)/MusicStyle_df71a8a6.o \
  $(JUCE_OBJDIR)/Player_d5433cfb.o \
  $(JUCE_OBJDIR)/Playlist_307de2c.o \
  $(JUCE_OBJDIR)/Subscription_38a53d77.o \
  $(JUCE_OBJDIR)/User_dcb1be25.o \
  $(JUCE_OBJDIR)/BinaryData_371e9b63.o \
  $(JUCE_OBJDIR)/juce_audio_basics_14202532.o \
  $(JUCE_OBJDIR)/juce_audio_devices_13712d1a.o \
  $(JUCE_OBJDIR)/juce_audio_formats_c6583019.o \
  $(JUCE_OBJDIR)/juce_audio_processors_bb10f4e.o \
  $(JUCE_OBJDIR)/juce_audio_utils_3074e8ee.o \
  $(JUCE_OBJDIR)/juce_core_e46e0cc3.o \
  $(JUCE_OBJDIR)/juce_cryptography_16899490.o \
  $(JUCE_OBJDIR)/juce_data_structures_8d0e1bfb.o \
  $(JUCE_OBJDIR)/juce_events_856f317d.o \
  $(JUCE_OBJDIR)/juce_graphics_6544222f.o \
  $(JUCE_OBJDIR)/juce_gui_basics_b7173e6d.o \
  $(JUCE_OBJDIR)/juce_gui_extra_a649f832.o \
  $(JUCE_OBJDIR)/juce_opengl_80215e13.o \
  $(JUCE_OBJDIR)/juce_video_5a052da1.o \

.PHONY: clean

$(JUCE_OUTDIR)/$(TARGET): check-pkg-config $(OBJECTS) $(RESOURCES)
	@echo Linking BardeClient
	-@mkdir -p $(JUCE_BINDIR)
	-@mkdir -p $(JUCE_LIBDIR)
	-@mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(BLDCMD)

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl x11 xext xinerama

clean:
	@echo Cleaning BardeClient
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping BardeClient
	-@$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

$(JUCE_OBJDIR)/ThreadPool_dd677260.o: ../Source/ThreadPool.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ThreadPool.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Tools_90322e8b.o: ../Source/Tools.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Tools.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SynchronizeManager_e9a9ccd7.o: ../Source/SynchronizeManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SynchronizeManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AView_4c0b412f.o: ../Source/ViewManager/AView.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/HomePage_9fb9146f.o: ../Source/ViewManager/HomePage.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling HomePage.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ViewManager_527c33d1.o: ../Source/ViewManager/ViewManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ViewManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Chords_8c89bd4e.o: ../Source/AI/Chords.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Chords.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Disposition_da31b1aa.o: ../Source/AI/Disposition.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Disposition.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicGenerator_b8a25e65.o: ../Source/AI/MusicGenerator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicGenerator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ObjectMarkov_d034efca.o: ../Source/AI/ObjectMarkov.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ObjectMarkov.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Resolution_ca4e12e3.o: ../Source/AI/Resolution.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Resolution.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StyleSettings_ca3d60e7.o: ../Source/AI/StyleSettings.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StyleSettings.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Instrument_44b59881.o: ../Source/Instrument.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Instrument.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/jsoncpp_7b1ce7b0.o: ../JsoncppLibrary/jsoncpp.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling jsoncpp.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ADatabasManager_7f537f57.o: ../Source/DatabaseManager/ADatabasManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ADatabasManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SQLiteManager_99d2bf74.o: ../Source/DatabaseManager/SQLiteManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SQLiteManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AEncryptionManager_13e06cc8.o: ../Source/EncryptionManager/AEncryptionManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AEncryptionManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SSLManager_f25fe680.o: ../Source/EncryptionManager/SSLManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SSLManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AGraphManager_4508c7ea.o: ../Source/GraphManager/AGraphManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AGraphManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/JuceManager_8121b3aa.o: ../Source/GraphManager/JuceManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling JuceManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainComponent_fb729fae.o: ../Source/GraphManager/MainComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainWindow_1a69e1a9.o: ../Source/GraphManager/MainWindow.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicStyleButton_39681cbe.o: ../Source/GraphManager/MusicStyleButton.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicStyleButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AMidiManager_545b688.o: ../Source/MidiManager/AMidiManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AMidiManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Midi_8be1d87e.o: ../Source/MidiManager/Midi.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Midi.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MidiManager_7f6bb1d9.o: ../Source/MidiManager/MidiManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MidiManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ASocketManager_7ac741c8.o: ../Source/SocketManager/ASocketManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ASocketManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/TCPSocket_b03f596f.o: ../Source/SocketManager/TCPSocket.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling TCPSocket.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ASoundManager_564990e8.o: ../Source/SoundManager/ASoundManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ASoundManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/JuceSound_212948eb.o: ../Source/SoundManager/JuceSound.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling JuceSound.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Authentification_99239255.o: ../Source/Authentification.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Authentification.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CmdManager_1dc6efad.o: ../Source/CmdManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CmdManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Configuration_a9102926.o: ../Source/Configuration.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Configuration.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Core_d0bb77f9.o: ../Source/Core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FileManager_b3cf2001.o: ../Source/FileManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FileManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/main_e838ccf3.o: ../Source/main.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling main.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Music_bf331dd5.o: ../Source/Music.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Music.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicParameters_1a7d3edf.o: ../Source/MusicParameters.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicParameters.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicStyle_df71a8a6.o: ../Source/MusicStyle.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicStyle.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Player_d5433cfb.o: ../Source/Player.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Player.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Playlist_307de2c.o: ../Source/Playlist.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Playlist.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Subscription_38a53d77.o: ../Source/Subscription.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Subscription.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/User_dcb1be25.o: ../Source/User.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling User.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_371e9b63.o: ../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_basics_14202532.o: ../JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_devices_13712d1a.o: ../JuceLibraryCode/juce_audio_devices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_formats_c6583019.o: ../JuceLibraryCode/juce_audio_formats.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_processors_bb10f4e.o: ../JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_utils_3074e8ee.o: ../JuceLibraryCode/juce_audio_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_e46e0cc3.o: ../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_cryptography_16899490.o: ../JuceLibraryCode/juce_cryptography.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_8d0e1bfb.o: ../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_856f317d.o: ../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_6544222f.o: ../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_b7173e6d.o: ../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_extra_a649f832.o: ../JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_opengl_80215e13.o: ../JuceLibraryCode/juce_opengl.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_video_5a052da1.o: ../JuceLibraryCode/juce_video.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_video.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
