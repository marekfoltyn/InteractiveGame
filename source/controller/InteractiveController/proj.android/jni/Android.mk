LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp

FILE_LIST1 := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST2 := $(wildcard $(LOCAL_PATH)/../../../../shared/network/*.cpp)
FILE_LIST3 := $(wildcard $(LOCAL_PATH)/../../../../shared/messages/*.cpp)
FILE_LIST4 := $(wildcard $(LOCAL_PATH)/../../../../shared/messages/*.cc)
FILE_LIST5 := $(wildcard $(LOCAL_PATH)/../../../../shared/game/*.cpp)

FILE_LIST7 := $(wildcard $(LOCAL_PATH)/../../../../shared/google/protobuf/*.cc)
FILE_LIST8 := $(wildcard $(LOCAL_PATH)/../../../../shared/google/protobuf/io/*.cc)
FILE_LIST9 := $(wildcard $(LOCAL_PATH)/../../../../shared/google/protobuf/stubs/*.cc)

LOCAL_SRC_FILES += $(FILE_LIST0:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST1:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST2:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST3:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST4:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST5:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += $(FILE_LIST7:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST8:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST9:$(LOCAL_PATH)/%=%)
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/network
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/messages
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/game
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/testing

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/google/protobuf
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/google/protobuf/io
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/google/protobuf/stubs
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/google/protobuf/testing

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_WHOLE_STATIC_LIBRARIES += RakNet

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
$(call import-module,RakNet)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END



