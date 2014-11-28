LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

define all-cpp-files-under
$(patsubst ./%,%, $(shell find $(LOCAL_PATH)/../../Classes -name "*.cpp" -and -not -name ".*"))
endef
define all-subdir-cpp-files
$(call all-cpp-files-under,.)
endef

define all-c-files-under
$(patsubst ./%,%, $(shell find $(LOCAL_PATH)/../../Classes -name "*.c" -and -not -name ".*"))
endef
define all-subdir-c-files
$(call all-c-files-under,.)
endef

CPP_FILE_LIST := $(call all-subdir-cpp-files)
C_FILE_LIST := $(call all-subdir-c-files)

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%) \
                   $(C_FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,CocosDenshion/android) 
