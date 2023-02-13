LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#opencv
#OPENCVROOT:= D:\dev__in_progress\_lib_\OpenCV-android-sdk
#OPENCV_CAMERA_MODULES:=on
#OPENCV_INSTALL_MODULES:=on
#OPENCV_LIB_TYPE:=SHARED
#
#include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk
#
# Gesture [
#LOCAL_INCLUDES_GESTURE := gesture/handDetectionCV-master/LinuxVersion
#LOCAL_SRC_GESTURE := \
#$(LOCAL_INCLUDES_GESTURE)/myImage.cpp \
#$(LOCAL_INCLUDES_GESTURE)/handGesture.cpp \
#$(LOCAL_INCLUDES_GESTURE)/roi.cpp
#LOCAL_SRC_FILES := main.cpp $(LOCAL_SRC_GESTURE)
#LOCAL_CFLAGS += -I$(LOCAL_PATH)/$(LOCAL_INCLUDES_GESTURE)
# Gesture ]

LOCAL_SRC_FILES := lottery_prediction.cpp

# undefined reference to '__atomic_exchange_4': USE -latomic
# SEE: https://developer.android.com/ndk/guides/common-problems?hl=en
LOCAL_LDLIBS += -llog -latomic

# .so name
LOCAL_MODULE := lottery_prediction

include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)

