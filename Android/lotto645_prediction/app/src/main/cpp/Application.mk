#APP_ABI := all
APP_ABI := armeabi armeabi-v7a arm64-v8a x86 x86_64
#APP_ABI := x86

APP_PLATFORM := android-21

#APP_STL := gnustl_static

# system stlport_static stlport_shared gnustl_static gnustl_shared c++_static c++_shared none
APP_STL := c++_static

# -std=c++11 or -std=gnu++11
APP_CPPFLAGS := -frtti -fexceptions -std=c++11

#NDK_TOOLCHAIN_VERSION := clang