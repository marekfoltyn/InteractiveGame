LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
		../../../../shared/network/Connector.cpp \
		../../../../shared/network/Blok.cpp \
		../../../../shared/bloks/AccelerationBlok.cpp \
		../../../../shared/bloks/ServerNameBlok.cpp \
		../../../../shared/bloks/StringBlok.cpp \
		../../../../shared/bloks/CollisionBlok.cpp \
		../../../../shared/bloks/KickBlok.cpp \
		../../../../shared/bloks/TackleBlok.cpp \
		../../../../shared/bloks/AdminBlok.cpp \
		../../../../shared/bloks/ResetScoreBlok.cpp \
		../../Classes/AppDelegate.cpp \
		../../Classes/ServerListScene.cpp \
		../../Classes/LobbyScene.cpp
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/network
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../shared/bloks

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



