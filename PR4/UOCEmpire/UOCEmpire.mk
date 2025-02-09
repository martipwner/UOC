##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Test
ProjectName            :=UOCEmpire
ConfigurationName      :=Test
WorkspaceConfiguration :=Test
WorkspacePath          :=/home/uoc/Downloads/UOCEmpire_SOL_v7
ProjectPath            :=/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire
IntermediateDirectory  :=./Test
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=30/05/24
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="UOCEmpire.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_starbase.c$(ObjectSuffix) $(IntermediateDirectory)/src_ship.c$(ObjectSuffix) $(IntermediateDirectory)/src_mission.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_api.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Test || $(MakeDirCommand) ./Test


$(IntermediateDirectory)/.d:
	@test -d ./Test || $(MakeDirCommand) ./Test

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_test.c$(DependSuffix) -MM src/test.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix) src/test.c

$(IntermediateDirectory)/src_starbase.c$(ObjectSuffix): src/starbase.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_starbase.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_starbase.c$(DependSuffix) -MM src/starbase.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/starbase.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_starbase.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_starbase.c$(PreprocessSuffix): src/starbase.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_starbase.c$(PreprocessSuffix) src/starbase.c

$(IntermediateDirectory)/src_ship.c$(ObjectSuffix): src/ship.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ship.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ship.c$(DependSuffix) -MM src/ship.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/ship.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ship.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ship.c$(PreprocessSuffix): src/ship.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ship.c$(PreprocessSuffix) src/ship.c

$(IntermediateDirectory)/src_mission.c$(ObjectSuffix): src/mission.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_mission.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_mission.c$(DependSuffix) -MM src/mission.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/mission.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_mission.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_mission.c$(PreprocessSuffix): src/mission.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_mission.c$(PreprocessSuffix) src/mission.c

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_menu.c$(DependSuffix) -MM src/menu.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix) src/menu.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_api.c$(DependSuffix) -MM src/api.c
	$(CC) $(SourceSwitch) "/home/uoc/Downloads/UOCEmpire_SOL_v7/UOCEmpire/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Test/


