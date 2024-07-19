#APP_ABI := all
# DO NOT USE (no longer supported): armeabi
#APP_ABI := armeabi armeabi-v7a arm64-v8a x86 x86_64
APP_ABI := armeabi-v7a arm64-v8a
#APP_ABI := x86

APP_PLATFORM := android-21

#APP_STL := gnustl_static

# system stlport_static stlport_shared gnustl_static gnustl_shared c++_static c++_shared none
APP_STL := c++_static

# -std=c++14 or -std=gnu++14
APP_CPPFLAGS := -frtti -fexceptions -std=c++14

#NDK_TOOLCHAIN_VERSION := clang