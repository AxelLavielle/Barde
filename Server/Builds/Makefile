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

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DSOURCEMARKOV=\"${CURDIR}/../Software/Source/markovSource/\" -DJUCER_LINUX_MAKE_7741F3E5=1 -DJUCE_APP_VERSION=1.0.0 -DJUCE_APP_VERSION_HEX=0x10000 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../JuceLibraryCode -I../../Software/JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CPPFLAGS_APP := -DJucePlugin_Build_VST=0 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0
  JUCE_TARGET_APP := Server

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -I../../Software/JsoncppLibrary/ -I../../Software/LuaLibrary/include -I../../Software/Source -W -Wall -Wextra $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0) -ldl -lpthread -lrt -lboost_system -llua $(LDFLAGS)

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

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DSOURCEMARKOV=\"${CURDIR}/../Software/Source/markovSource/\" -DJUCER_LINUX_MAKE_7741F3E5=1 -DJUCE_APP_VERSION=1.0.0 -DJUCE_APP_VERSION_HEX=0x10000 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../JuceLibraryCode -I../../Software/JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CPPFLAGS_APP := -DJucePlugin_Build_VST=0 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0
  JUCE_TARGET_APP := Server

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -O3 -I../../Software/JsoncppLibrary/ -I../../Software/LuaLibrary/include -I../../Software/Source -W -Wall -Wextra $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0) -fvisibility=hidden -ldl -lpthread -lrt -lboost_system -llua $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_APP := \
  $(JUCE_OBJDIR)/jsoncpp_db041a9.o \
  $(JUCE_OBJDIR)/AI_1eb60778.o \
  $(JUCE_OBJDIR)/Chords_7f424607.o \
  $(JUCE_OBJDIR)/Disposition_293eb491.o \
  $(JUCE_OBJDIR)/MusicGenerator_f3c71e1e.o \
  $(JUCE_OBJDIR)/ObjectMarkov_62c849c3.o \
  $(JUCE_OBJDIR)/Pattern_3658f66a.o \
  $(JUCE_OBJDIR)/PatternGenerator_f5e763d3.o \
  $(JUCE_OBJDIR)/Resolution_27b1971c.o \
  $(JUCE_OBJDIR)/StyleSettings_8a15460e.o \
  $(JUCE_OBJDIR)/ADatabasManager_f4dc750.o \
  $(JUCE_OBJDIR)/SQLiteManager_5d80b1ad.o \
  $(JUCE_OBJDIR)/AEncryptionManager_4121386f.o \
  $(JUCE_OBJDIR)/SSLManager_327e4927.o \
  $(JUCE_OBJDIR)/AGraphManager_a6dda851.o \
  $(JUCE_OBJDIR)/JuceManager_47b181d1.o \
  $(JUCE_OBJDIR)/LoginComponent_fb4a57ad.o \
  $(JUCE_OBJDIR)/MainComponent_5d478015.o \
  $(JUCE_OBJDIR)/MainWindow_6b2432a2.o \
  $(JUCE_OBJDIR)/MusicStyleButton_fd160ef7.o \
  $(JUCE_OBJDIR)/Theme_93f7701a.o \
  $(JUCE_OBJDIR)/AMidiManager_cbd584af.o \
  $(JUCE_OBJDIR)/Midi_4bb9bda5.o \
  $(JUCE_OBJDIR)/MidiManager_d02602d2.o \
  $(JUCE_OBJDIR)/ARestClient_a87f69f4.o \
  $(JUCE_OBJDIR)/RestClient_aa36c0d5.o \
  $(JUCE_OBJDIR)/RestClientException_2f053944.o \
  $(JUCE_OBJDIR)/ASoundManager_b81e714f.o \
  $(JUCE_OBJDIR)/JuceSound_65d474d2.o \
  $(JUCE_OBJDIR)/Synthesizer_c10c278.o \
  $(JUCE_OBJDIR)/SynthesizerInstrument_37460f3f.o \
  $(JUCE_OBJDIR)/AView_873000e8.o \
  $(JUCE_OBJDIR)/HomePage_393c0e16.o \
  $(JUCE_OBJDIR)/ViewManager_a33684ca.o \
  $(JUCE_OBJDIR)/Authentification_58fb777c.o \
  $(JUCE_OBJDIR)/CmdManager_821f7e14.o \
  $(JUCE_OBJDIR)/Configuration_673ad5f.o \
  $(JUCE_OBJDIR)/Core_cc9c9fa0.o \
  $(JUCE_OBJDIR)/FileManager_da885e7a.o \
  $(JUCE_OBJDIR)/Instrument_a90e26e8.o \
  $(JUCE_OBJDIR)/Music_3f76eb0e.o \
  $(JUCE_OBJDIR)/MusicParameters_ad1098d8.o \
  $(JUCE_OBJDIR)/MusicStyle_43ca370d.o \
  $(JUCE_OBJDIR)/Player_5d7916e2.o \
  $(JUCE_OBJDIR)/Playlist_552eda53.o \
  $(JUCE_OBJDIR)/Subscription_e913ce1e.o \
  $(JUCE_OBJDIR)/SynchronizeManager_131d043e.o \
  $(JUCE_OBJDIR)/ThreadPool_41c000c7.o \
  $(JUCE_OBJDIR)/Tools_1075fbc4.o \
  $(JUCE_OBJDIR)/User_d892e5cc.o \
  $(JUCE_OBJDIR)/UserSettings_f98b258f.o \
  $(JUCE_OBJDIR)/Connection_1bc85ff8.o \
  $(JUCE_OBJDIR)/main_e838ccf3.o \
  $(JUCE_OBJDIR)/Server_eb81d05d.o \
  $(JUCE_OBJDIR)/BinaryData_371e9b63.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_10901fdb.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_a5008791.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_57e78a90.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_4e18d77.o \
  $(JUCE_OBJDIR)/include_juce_core_9b13c06c.o \
  $(JUCE_OBJDIR)/include_juce_cryptography_12f98f39.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_f830b4b2.o \
  $(JUCE_OBJDIR)/include_juce_events_29769ee6.o \
  $(JUCE_OBJDIR)/include_juce_graphics_2525d958.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_567cf56.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_e29f2629.o \

.PHONY: clean all

all : $(JUCE_OUTDIR)/$(JUCE_TARGET_APP)

$(JUCE_OUTDIR)/$(JUCE_TARGET_APP) : check-pkg-config $(OBJECTS_APP) $(RESOURCES)
	@echo Linking "Server - App"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_APP) $(OBJECTS_APP) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_APP) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OBJDIR)/jsoncpp_db041a9.o: ../../Software/JsoncppLibrary/jsoncpp.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling jsoncpp.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AI_1eb60778.o: ../../Software/Source/AI/AI.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AI.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Chords_7f424607.o: ../../Software/Source/AI/Chords.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Chords.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Disposition_293eb491.o: ../../Software/Source/AI/Disposition.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Disposition.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicGenerator_f3c71e1e.o: ../../Software/Source/AI/MusicGenerator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicGenerator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ObjectMarkov_62c849c3.o: ../../Software/Source/AI/ObjectMarkov.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ObjectMarkov.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Pattern_3658f66a.o: ../../Software/Source/AI/Pattern.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Pattern.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PatternGenerator_f5e763d3.o: ../../Software/Source/AI/PatternGenerator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PatternGenerator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Resolution_27b1971c.o: ../../Software/Source/AI/Resolution.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Resolution.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StyleSettings_8a15460e.o: ../../Software/Source/AI/StyleSettings.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StyleSettings.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ADatabasManager_f4dc750.o: ../../Software/Source/DatabaseManager/ADatabasManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ADatabasManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SQLiteManager_5d80b1ad.o: ../../Software/Source/DatabaseManager/SQLiteManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SQLiteManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AEncryptionManager_4121386f.o: ../../Software/Source/EncryptionManager/AEncryptionManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AEncryptionManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SSLManager_327e4927.o: ../../Software/Source/EncryptionManager/SSLManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SSLManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AGraphManager_a6dda851.o: ../../Software/Source/GraphManager/AGraphManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AGraphManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/JuceManager_47b181d1.o: ../../Software/Source/GraphManager/JuceManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling JuceManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LoginComponent_fb4a57ad.o: ../../Software/Source/GraphManager/LoginComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LoginComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainComponent_5d478015.o: ../../Software/Source/GraphManager/MainComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainWindow_6b2432a2.o: ../../Software/Source/GraphManager/MainWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicStyleButton_fd160ef7.o: ../../Software/Source/GraphManager/MusicStyleButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicStyleButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Theme_93f7701a.o: ../../Software/Source/GraphManager/Theme.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Theme.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AMidiManager_cbd584af.o: ../../Software/Source/MidiManager/AMidiManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AMidiManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Midi_4bb9bda5.o: ../../Software/Source/MidiManager/Midi.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Midi.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MidiManager_d02602d2.o: ../../Software/Source/MidiManager/MidiManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MidiManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ARestClient_a87f69f4.o: ../../Software/Source/SocketManager/ARestClient.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ARestClient.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/RestClient_aa36c0d5.o: ../../Software/Source/SocketManager/RestClient.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling RestClient.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/RestClientException_2f053944.o: ../../Software/Source/SocketManager/RestClientException.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling RestClientException.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ASoundManager_b81e714f.o: ../../Software/Source/SoundManager/ASoundManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ASoundManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/JuceSound_65d474d2.o: ../../Software/Source/SoundManager/JuceSound.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling JuceSound.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Synthesizer_c10c278.o: ../../Software/Source/SoundManager/Synthesizer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Synthesizer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SynthesizerInstrument_37460f3f.o: ../../Software/Source/SoundManager/SynthesizerInstrument.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SynthesizerInstrument.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AView_873000e8.o: ../../Software/Source/ViewManager/AView.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AView.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/HomePage_393c0e16.o: ../../Software/Source/ViewManager/HomePage.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling HomePage.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ViewManager_a33684ca.o: ../../Software/Source/ViewManager/ViewManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ViewManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Authentification_58fb777c.o: ../../Software/Source/Authentification.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Authentification.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CmdManager_821f7e14.o: ../../Software/Source/CmdManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CmdManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Configuration_673ad5f.o: ../../Software/Source/Configuration.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Configuration.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Core_cc9c9fa0.o: ../../Software/Source/Core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/FileManager_da885e7a.o: ../../Software/Source/FileManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling FileManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Instrument_a90e26e8.o: ../../Software/Source/Instrument.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Instrument.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Music_3f76eb0e.o: ../../Software/Source/Music.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Music.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicParameters_ad1098d8.o: ../../Software/Source/MusicParameters.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicParameters.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MusicStyle_43ca370d.o: ../../Software/Source/MusicStyle.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MusicStyle.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Player_5d7916e2.o: ../../Software/Source/Player.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Player.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Playlist_552eda53.o: ../../Software/Source/Playlist.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Playlist.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Subscription_e913ce1e.o: ../../Software/Source/Subscription.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Subscription.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/SynchronizeManager_131d043e.o: ../../Software/Source/SynchronizeManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling SynchronizeManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ThreadPool_41c000c7.o: ../../Software/Source/ThreadPool.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ThreadPool.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Tools_1075fbc4.o: ../../Software/Source/Tools.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Tools.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/User_d892e5cc.o: ../../Software/Source/User.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling User.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/UserSettings_f98b258f.o: ../../Software/Source/UserSettings.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling UserSettings.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Connection_1bc85ff8.o: ../Source/Connection.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Connection.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/main_e838ccf3.o: ../Source/main.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling main.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Server_eb81d05d.o: ../Source/Server.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Server.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_371e9b63.o: ../JuceLibraryCode/BinaryData.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_10901fdb.o: ../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_a5008791.o: ../JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_57e78a90.o: ../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_4e18d77.o: ../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_9b13c06c.o: ../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_cryptography_12f98f39.o: ../JuceLibraryCode/include_juce_cryptography.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_f830b4b2.o: ../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_29769ee6.o: ../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_2525d958.o: ../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_567cf56.o: ../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_e29f2629.o: ../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_APP) $(JUCE_CFLAGS_APP) -o "$@" -c "$<"

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl x11 xext xinerama webkit2gtk-4.0 gtk+-x11-3.0

clean:
	@echo Cleaning Server
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Server
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_APP:%.o=%.d)
