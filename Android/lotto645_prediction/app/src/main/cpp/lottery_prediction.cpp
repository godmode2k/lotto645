// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("lottery_prediction");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("lottery_prediction")
//      }
//    }



/*
* Project:  lotto645 prediction
* Purpose:
* Author:   Ho-Jung Kim (godmode2k@hotmail.com)
* Date:     Since February 10, 2023
*
* modified:    February 10, 2023
* License:
*
*
* Copyright (C) 2023 Ho-Jung Kim (godmode2k@hotmail.com)
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*
* Source:
* Note: {
}
* -----------------------------------------------------------------
* TODO:
*
* URGENT!!!
* TODO:
*
*/

#include <android/log.h>
#include <jni.h>

#define TAG				"NATIVE_ML_MODULE"
#define LOGD(...)		__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...)		__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

//#define ENABLE_LOG

#include "ml_module.cpp"

//extern "C"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL
Java_com_atflab_android_lottery_1prediction_ui_home_HomeFragment_get_1native_1max_1algorithm(
    JNIEnv *env, jobject thiz) {
    // TODO: implement get_native_max_algorithms()

    LOGD( "get_native_max_algorithms(): internal" );
    LOGD( "get_native_max_algorithms(): MAX_ALGORITHM = %d", MAX_ALGORITHM );

    return MAX_ALGORITHM;
}

JNIEXPORT jobjectArray JNICALL
// /MainActivity.java
//Java_com_atflab_android_lottery_1prediction_MainActivity_get_1native_1ml_1module(JNIEnv *env, jobject thiz, jint _generate) {
// /ui/home/HomeFragment.java
Java_com_atflab_android_lottery_1prediction_ui_home_HomeFragment_get_1native_1ml_1module(
    JNIEnv *env, jobject thiz, jint _algorithm, jint _generate, jint _total_games) {
    // TODO: implement get_native_ml_module()

    LOGD( "get_native_ml_module(): internal" );

    jobjectArray ret;

    const int generate = (int)_generate;
    const int total_games = (int)_total_games;
    std::vector<char*>* result = new std::vector<char*>;
    std::vector<char*>* result_score = new std::vector<char*>;
    std::vector<float*>* result_float = new std::vector<float*>;
    std::vector<char*>* null_result = NULL;

    switch ( _algorithm ) {
        case 1:
            main_ml( generate, total_games, result );
            break;
        case 2:
            // TODO: adds total_games
            odd_even( result, result_float );
            comparison( result_score, result_float );
            for ( auto x: *result_score ) { result->push_back( x ); }
            break;
        case 3:
            // TODO: adds total_games
            odd_even( null_result, result_float );
            method3( result, result_float );
            break;
        case 4:
            method4( total_games, result );
            break;
        default:
            main_ml( generate, total_games, result );
            break;
    }

    ret = (jobjectArray)env->NewObjectArray( result->size(), env->FindClass("java/lang/String"), env->NewStringUTF("") );

    LOGD( "get_native_ml_module(): algorithm: %d", _algorithm );
    LOGD( "get_native_ml_module(): generate (repeat): %d", generate );
    LOGD( "get_native_ml_module(): total games: %d", total_games );
    LOGD( "get_native_ml_module(): results: size = %d", result->size() );
    LOGD( "get_native_ml_module(): results:" );
    int i = 0;
    std::vector<char*>::iterator iter;
    for ( iter = result->begin(); iter != result->end(); ++iter ) {
        char* numbers = (*iter);
        //LOGD( "get_native_ml_module(): %d %s", i, numbers );

        env->SetObjectArrayElement( ret, i, env->NewStringUTF(numbers) );

        delete[] numbers;
        numbers = NULL;

        i++;
    }
    result->clear();
    delete result;
    result = NULL;

    // algorithm #2
    // SEE: switch ( _algorithm ) { case 2: ...
    //for ( iter = result_score->begin(); iter != result_score->end(); ++iter ) {
    //    char* val = (*iter);
    //    if ( val != NULL ) {
    //        delete[] val;
    //    }
    //}
    result_score->clear();
    delete result_score;
    result_score = NULL;

    return ret;
}

#ifdef __cplusplus
}
#endif
