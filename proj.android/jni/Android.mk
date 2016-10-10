LOCAL_PATH := $(call my-dir)

#========���߱���================start
#����һ����Ŀ¼
filterdir = $(foreach obj, $(wildcard $1/*), $(if $(realpath $(wildcard $(obj)/.)), $(obj)))
# �ݹ��ҳ���Ŀ¼
rwildcard = $(foreach dir, $(call filterdir, $1), $(call rwildcard, $(dir)) $(dir))
#========���߱���================end



include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

myDir := $(LOCAL_PATH)/../../Classes
myDir += $(call rwildcard, $(myDir))
myDir := $(sort $(myDir))

LOCAL_SRC_FILES := hellocpp/main.cpp

mycpps := $(foreach dir, $(myDir), $(wildcard $(dir)/*.cpp))
mycpps := $(mycpps:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(mycpps)

LOCAL_C_INCLUDES := $(myDir)
LOCAL_C_INCLUDES += $(LOCAL_PATH)
infos = .+==================
infos += $(myDir)
$(info $(infos))  
         

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
