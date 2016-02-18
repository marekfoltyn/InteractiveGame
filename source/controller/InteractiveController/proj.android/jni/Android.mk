LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp

FILE_LIST1 := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST2 := $(wildcard $(LOCAL_PATH)/../../../../shared/network/*.cpp)
FILE_LIST3 := $(wildcard $(LOCAL_PATH)/../../../../shared/messages/*.cpp)

LOCAL_SRC_FILES += $(FILE_LIST1:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST2:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST3:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(FILE_LIST4:$(LOCAL_PATH)/%=%)
				   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/network
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/messages

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



