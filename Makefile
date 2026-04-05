export SOURCE_DATE_EPOCH := 1609459200


# compilers
CC = x86_64-w64-mingw32-gcc
WINDRES = x86_64-w64-mingw32-windres

# flags
CFLAGS = -O3 -D_MINGW_USE_STD_THREAD -fstack-protector -mwindows -ffunction-sections -fdata-sections
LDFLAGS =  -Wl,--dynamicbase -Wl,--nxcompat   -Wl,--gc-sections -mwindows -Wl,-subsystem,windows

# directories
INC_DIR = ./inc
SRC_DIR = ./src
OBJ_DIR = ./obj
VER_DIR = ./ver

# files
RC_FILE = $(VER_DIR)/version.rc
RES_FILE = $(OBJ_DIR)/version.res
MANIFEST_FILE = $(VER_DIR)/app.manifest
CONFIG_FILES = $(INC_DIR)/lucky_net_configs.h  $(INC_DIR)/lucky_obf_configs.h


OUT_FILE = filezilla.exe


# source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# default target
all: $(CONFIG_FILES) $(OUT_FILE)
	


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


# compile C sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@


# link step
$(OUT_FILE): $(OBJ) $(RES_FILE) 
	@echo "Linking the executable with resources and manifest..."
	$(CC) $(LDFLAGS) $(OBJ) $(RES_FILE) -o $@
	strip $(OUT_FILE)

# compile version resources
$(RES_FILE): $(RC_FILE) | $(OBJ_DIR)
	@echo "Compiling version resources..."
	$(WINDRES) $< -O coff -o $@


clean:
	rm -rf $(OUT_FILE)  $(OBJ_DIR) $(RES_FILE) 

cleanConfig:
	rm -f $(CONFIG_FILES)

cleanAll: clean cleanConfig
	
rebuild: cleanAll all



config: $(CONFIG_FILES) 


$(CONFIG_FILES):
	./luckySpark.sh -c 
