/*
* Project:  lotto645 prediction
* Purpose:
* Author:   Ho-Jung Kim (godmode2k@hotmail.com)
* Date:     Since April 25, 2021
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

#include <iostream>
#include <cstdio>
#include <cstdlib> // rand()
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

//#include <unistd.h> // usleep()

#include <cstdarg>
#include <cmath>
#include "model_lotto645.h"

/*
//! FIXED
float compute_kernel(float *x, ...) {
//    va_list w;
//    va_start(w, 6);
//    float kernel = 0.0;
//
//    for (uint16_t i = 0; i < 6; i++) {
//        kernel += pow(x[i] - va_arg(w, double), 2);
//    }
//
//    return exp(-0.001 * kernel);

    const int size = 9 + 3; // variable arguments (...) + 3 (for ignore first 3bytes)
    va_list w;
    va_start(w, size);
    float kernel = 0.0;

    double _x[size] = { 0, };
    for (int i = 0; i < size; i++) { _x[i] = va_arg(w, double); }
    printf("input = (%f, %f, %f, %f, %f, %f, %f, %f, %f)\n",
        _x[3], _x[4], _x[5], _x[6], _x[7], _x[8], _x[9], _x[10], _x[11]);

    // ignore 3 bytes garbage data
    for (uint16_t i = 0; i < (size - 3); i++) {
            kernel += pow(x[i] - _x[i+3], 2);
    }

    return exp(-0.001 * kernel);
}
*/

#ifdef __cplusplus
extern "C" {
#endif

#define INT_ARR_TO_STRING(str, arr) \
    do { \
        int len = sizeof(arr) / sizeof(int); \
        for ( int _i = 0; _i < len; _i++ ) { \
            str += ((arr[_i] > 9) ? "":"0") + std::to_string(arr[_i]) + ((_i+1 < len) ? ",  ":""); \
        } \
    } while (0)

#define VEC_INT_ARR_TO_STRING(str, arr) \
    do { \
        for ( int _i = 0; _i < arr.size(); _i++ ) { \
            str += ((arr[_i] > 9) ? "":"0") + std::to_string(arr[_i]) + ((_i+1 < len) ? ",  ":""); \
        } \
    } while (0)


#define MAX_MATCH_NUMBER  6

// for display last game (number of games: no.1 ~ present)
//#define LAST_GAME   "1 ~ 1125회\n(2024년 06월 22일 추첨까지)"
// SEE: model_lotto645_predicts_method.h


#include "lotto645_predicts_method.cpp"


//int main(int argc, char* argv[]) {
//    if ( argc < 2 ) {
//        printf( "Usage: %s [total generate (int)]\n", argv[0] );
//        return 0;
//    }
int main_ml(int _total_generate, int _total_games, std::vector<char*>*& ret_result) {
    //int total_generate = atoi( argv[1] );
    //int total_generate = (100*5) * 3;
    //int total_games = 5;

    int total_generate = _total_generate;
    int total_games = _total_games;

    // for display last game (number of games: no.1 ~ present)
    //const char* last_game = "no.1057"; // range: no.1 ~ present
    // SEE: model_lotto645_predicts_method.h

    //int result_won[] = { 8, 13, 19, 27, 40, 45, 12 }; // ignore
    // SEE: model_lotto645_predicts_method.h
    //
    const char* result_won_game = last_game; // ignore
    std::vector<int> result_matched_all;
    std::vector<int> result_matched_one_game;
    std::vector<std::array<int, MAX_MATCH_NUMBER>> result_predict_all;

    std::string str;
    //for ( int i: result_won )
    //    str += std::to_string(i) + ",";
    //std::cout << "str = " << str << std::endl;
    int len = sizeof(result_won) / sizeof(int);
    for ( int i = 0; i < len; i++ ) {
        str += std::to_string(result_won[i]) + ((i+1 < len) ? ",":"");
    }
#ifdef ENABLE_LOG
    printf( "result won (%s): %s\n", result_won_game, str.c_str() );
    LOGD( "main_ml(): result won (%s): %s\n", result_won_game, str.c_str() );
#endif


    std::string to_str;
    std::string to_str_vec;

    srand( (unsigned int)time(NULL) );

    for ( int x_gen = 0; x_gen < total_generate; x_gen++ ) {
        for ( int i = 0; i < total_games; i++ ) { // 5 results
            int result[MAX_MATCH_NUMBER] = { 0, }; // 1 ~ 6, bonus

            for ( int j = 0; j < MAX_MATCH_NUMBER; j++ ) { // 1 ~ 6, bonus
                while (1) {
#ifdef ENABLE_LOG
                    printf( "[%d/%d, %d/%d, %d/%d]\n", x_gen, total_generate, i, total_games, j, MAX_MATCH_NUMBER );
                    LOGD( "main_ml(): [%d/%d, %d/%d, %d/%d]\n", x_gen, total_generate, i, total_games, j, MAX_MATCH_NUMBER );
#endif
                    float input_val[MAX_MATCH_NUMBER] = { 0, }; // 1 ~ 6, bonus

                    for ( int r = 0; r < MAX_MATCH_NUMBER; r++ ) {
                        input_val[r] = rand() % 45 + 1; // range: 1 ~ 45
                    }
                    INT_ARR_TO_STRING( to_str, input_val );
                    //std::cout << "input val = " << to_str << std::endl;
                    //printf( "input val = %s\n", to_str.c_str() );
                    //LOGD( "main_ml(): input val = %s\n", to_str.c_str() );

                    Eloquent::ML::Port::SVM classifier;
                    int _result = classifier.predict( input_val ); // 0 ~ 44
                    _result += 1; // start at 1
                    //std::cout << "result = " << _result << std::endl;
                    //printf( "result = %d\n", _result );
                    //LOGD( "main_ml(): result = %d\n", _result );

                    //# Note
                    //#        1     2     3     4     5      6  bonus    sum
                    //#1  134.00   nan   nan   nan   nan    nan     29 163.00
                    //#45    nan   nan   nan   nan   nan 134.00     15 149.00


                    if ( _result == 1 || _result == 45 ) {
                        to_str = "";
                        INT_ARR_TO_STRING( to_str, input_val );
                        //std::cout << "input val = " << to_str << std::endl;
                        //printf( "input val = %s\n", to_str.c_str() );
                        //LOGD( "main_ml(): input val = %s\n", to_str.c_str() );
                        _result = rand() % 45 + 1; // one number (range: 1 ~ 45)
                    }
                        
                    {
                        bool found = false;
                        for ( int res = 0; res < MAX_MATCH_NUMBER; res++ ) {
                            if ( _result == result[res] ) {
                                found = true;
                                break;
                            }
                        }
                        if ( found ) continue;
                    }

                    result[j] = _result;
                    break;
                } // while (1)
            } // for ()


/*
            std::array<int, 6> new_arr;
            for ( int x = 0; x < 6; x++ ) {
                new_arr[x] = result[x];
                to_str = "";
                INT_ARR_TO_STRING( to_str, new_arr );
                printf( "result = [%s]\n", to_str.c_str() );
                LOGD( "main_ml(): result = [%s]\n", to_str.c_str() );
            }
            result_predict_all.push_back( new_arr );
*/
            result_predict_all.push_back(
                    reinterpret_cast<std::array<int, MAX_MATCH_NUMBER>&>(result) );

            // comparison
            std::vector<int> result_matched;
            for ( int x = 0; x < MAX_MATCH_NUMBER; x++ ) {
#ifdef ENABLE_LOG
                printf( "result[%d] = %d\n", x, result[x] );
                LOGD( "main_ml(): result[%d] = %d\n", x, result[x] );
#endif
                int* p = std::find( result_won, result_won + MAX_MATCH_NUMBER, result[x] );
                if ( p != result_won + MAX_MATCH_NUMBER) {
                    //printf( "result_matched: found, add... (%d == %d(found))\n", result[x], *p );
                    //LOGD( "main_ml(): result_matched: found, add... (%d == %d(found))\n", result[x], *p );
                    result_matched.push_back( result[x] );

                    if ( result_matched_all.empty() ) {
                        //printf( "result_matched_all: empty, add a new, (%d)\n", result[x] );
                        //LOGD( "main_ml(): result_matched_all: empty, add a new, (%d)\n", result[x] );
                        result_matched_all.push_back( result[x] );
                    }
                    else {
                        int val = 0;
                        for ( int y = 0; y < result_matched_all.size(); y++ ) {
                            //printf( "result_matched_all[%d] = %d\n", y, result_matched_all[y] );
                            //LOGD( "main_ml(): result_matched_all[%d] = %d\n", y, result_matched_all[y] );
                            if ( result[x] == result_matched_all[y] ) {
                                //printf( "result_matched_all: found a duplocated, skip... (%d, %d(found))\n",
                                //     result_matched_all[y], result[x] );
                                //LOGD( "main_ml(): result_matched_all: found a duplocated, skip... (%d, %d(found))\n",
                                //     result_matched_all[y], result[x] );
                                val = 0;
                                break;
                            }
                            val = result[x];
                        }
                        if ( val > 0 ) {
                            //printf( "result_matched_all: add a new, (%d)\n", result[x] );
                            //LOGD( "main_ml(): result_matched_all: add a new, (%d)\n", result[x] );
                            result_matched_all.push_back( result[x] );
                        }
                    }
                }
                else {
#ifdef ENABLE_LOG
                    printf( "result_matched: not found...\n" );
                    LOGD( "main_ml(): result_matched: not found...\n" );
#endif
                }
            } // for ()

            to_str = "";
            INT_ARR_TO_STRING( to_str, result );
            to_str_vec = "";
            VEC_INT_ARR_TO_STRING( to_str_vec, result_matched );
#ifdef ENABLE_LOG
            printf( "result = [%s] ==> %s matched( %d ), [%s]\n",
                    to_str.c_str(), result_won_game, result_matched.size(), to_str_vec.c_str() );
            LOGD( "main_ml(): result = [%s] ==> %s matched( %d ), [%s]\n",
                    to_str.c_str(), result_won_game, result_matched.size(), to_str_vec.c_str() );
#endif

            if ( result_matched_one_game.size() < result_matched.size() ) {
                result_matched_one_game.clear();
                for ( int x = 0; x < result_matched.size(); x++ ) {
                    //result_matched_one_game.push_back( result_matched[x] );

                    // remove duplicated item
                    std::vector<int>::iterator p =
                        std::find( result_matched_all.begin(), result_matched_all.end(), result_matched[x] );
                    if ( p != result_matched_all.end() ) {
#ifdef ENABLE_LOG
                        printf( "result_matched_one_game: add a new\n" );
                        LOGD( "main_ml(): result_matched_one_game: add a new\n" );
#endif
                        result_matched_one_game.push_back( result_matched[x] );
                    }
                    else {
#ifdef ENABLE_LOG
                        printf( "result_matched_one_game: found a duplicated, skip...\n" );
                        LOGD( "main_ml(): result_matched_one_game: found a duplicated, skip...\n" );
#endif
                    }
                }
            }

            //result:
            //    
            //result won (no.960): 2, 18, 24, 30, 32, 45 + 14
            //result = [19. 27. 30.  1. 31. 35.] ==> no.960 matched( 1 ) [30.0]
            //result = [ 9. 24. 25.  7. 37. 32.] ==> no.960 matched( 2 ) [24.0, 32.0]
            //result = [ 2. 44. 19.  1. 18. 11.] ==> no.960 matched( 2 ) [2.0, 18.0]
            //result = [ 3.  9. 38. 28. 23. 18.] ==> no.960 matched( 1 ) [18.0]
            //result = [24. 30. 12. 27. 22. 31.] ==> no.960 matched( 2 ) [24.0, 30.0]
            //result all (accumulative) (no.960) = [30.0, 24.0, 32.0, 2.0, 18.0] ==> count = 5
            //result (no.960) = [24.0, 32.0] ==> count = 2
        } // for ()


        // pick a last one
        if ( x_gen < (total_generate - 1) ) {
            result_matched_all.clear();
            result_matched_one_game.clear();
            result_predict_all.clear();
        }
#ifdef ENABLE_LOG
        printf( "total random generated = %d/%d\n", x_gen, total_generate - 1 );
        LOGD( "main_ml(): total random generated = %d/%d\n", x_gen, total_generate - 1 );
#endif
    } // for ()


    to_str_vec = "";
    VEC_INT_ARR_TO_STRING( to_str_vec, result_matched_all );
#ifdef ENABLE_LOG
    printf( "result all (accumulative) (%s) = [%s] ==> count = %d\n",
            result_won_game, to_str_vec.c_str(), result_matched_all.size() );
    LOGD( "main_ml(): result all (accumulative) (%s) = [%s] ==> count = %d\n",
            result_won_game, to_str_vec.c_str(), result_matched_all.size() );
#endif

    to_str_vec = "";
    VEC_INT_ARR_TO_STRING( to_str_vec, result_matched_one_game );
#ifdef ENABLE_LOG
    printf( "result (%s) = %s ==> count = %d\n",
            result_won_game, to_str_vec.c_str(), result_matched_one_game.size() );
    LOGD( "main_ml(): result (%s) = %s ==> count = %d\n",
            result_won_game, to_str_vec.c_str(), result_matched_one_game.size() );
#endif

#ifdef ENABLE_LOG
    printf("\n");
    LOGD( "main_ml(): " );

    printf( "result predict all =\n" );
    LOGD( "main_ml(): result predict all =\n" );
#endif
    for ( int i = 0; i < result_predict_all.size(); i++ ) {
        int arr[MAX_MATCH_NUMBER] = { 0, };
        std::copy_n( std::begin(result_predict_all[i]), result_predict_all[i].size(), arr );

        to_str = "";
        INT_ARR_TO_STRING( to_str, arr );
#ifdef ENABLE_LOG
        printf( "%d [%s]\n", i, to_str.c_str() );
        LOGD( "main_ml(): %d [%s]\n", i, to_str.c_str() );
#endif


        const int BUF_LEN = 12 + 5 + 10 + 1; // 12 (numbers: 2*6), 5 (','), 10 ('  ': 2*5)
        const int BUF_DESC_LEN = 100;

        // for display last game (number of games: no.1 ~ present)
        if ( i == 0 ) {
            char* buf_last_game = new char[BUF_DESC_LEN];
            snprintf( buf_last_game, BUF_DESC_LEN, "%s", LAST_GAME );
            ret_result->push_back( buf_last_game );
        }

        char* buf = new char[BUF_LEN];
        snprintf( buf, BUF_LEN, "%s", to_str.c_str() );
        ret_result->push_back( buf );
    }

//    {
//        int i = 0;
//        std::vector<char*>::iterator iter;
//        for ( iter = ret_result->begin(); iter != ret_result->end(); ++iter ) {
//            char* numbers = (*iter);
//            LOGD( "(): %d %s", i++, numbers );
//        }
//    }


    //result:
    //
    //result predict all =
    //0 [19. 27. 30.  1. 31. 35.]
    //1 [ 9. 24. 25.  7. 37. 32.]
    //2 [ 2. 44. 19.  1. 18. 11.]
    //3 [ 3.  9. 38. 28. 23. 18.]
    //4 [24. 30. 12. 27. 22. 31.]


    return 0;
}

#ifdef __cplusplus
}
#endif

/*
for x_gen in range(total_generate):
    for i in range(total_games): # 5 results
        result = np.zeros(6) # 1 ~ 6, bonus
        
        for j in range(6): # 1 ~ 6, bonus
            while True:
                #input_val = randint( 1, 45, 7 ) # 1 ~ 6, bonus
                input_val = randint( 1, 45, 6 ) # 1 ~ 6 (without bonus)
                #print( input_val )
            
                _result = classifier.predict( [input_val] ) # 0 ~ 44
                _result += 1 # start at 1
                
                # Note
                #        1     2     3     4     5      6  bonus    sum
                #1  134.00   nan   nan   nan   nan    nan     29 163.00
                #45    nan   nan   nan   nan   nan 134.00     15 149.00
                
                if _result == 1 or _result == 45:
                    #input_val = randint( 2, 44, 6 ) # 1 ~ 6 (without bonus)
                    #_result = classifier.predict( [input_val] ) # 0 ~ 44
                    #_result += 1 # start at 1
                    #
                    input_val = randint( 1, 45, 1 ) # one number
                    _result = input_val
                    
                if _result in result:
                    continue
                
                result[j] = _result
                break
            
        result_predict_all.append( result )
        
        # comparison
        result_matched = []
        for x in range(6):
            if result[x] in result_won:
                result_matched.append( result[x] )

        result_matched_all.extend( result_matched )
        print( "result =", result, "==>", result_won_game + " matched(", len(result_matched), ")", result_matched )
        if len(result_matched_one_game) < len(result_matched):
            result_matched_one_game.clear()
            result_matched_one_game.extend( result_matched )
    
        '''
        result:
            
        result won (no.960): 2, 18, 24, 30, 32, 45 + 14
        result = [19. 27. 30.  1. 31. 35.] ==> no.960 matched( 1 ) [30.0]
        result = [ 9. 24. 25.  7. 37. 32.] ==> no.960 matched( 2 ) [24.0, 32.0]
        result = [ 2. 44. 19.  1. 18. 11.] ==> no.960 matched( 2 ) [2.0, 18.0]
        result = [ 3.  9. 38. 28. 23. 18.] ==> no.960 matched( 1 ) [18.0]
        result = [24. 30. 12. 27. 22. 31.] ==> no.960 matched( 2 ) [24.0, 30.0]
        result all (accumulative) (no.960) = [30.0, 24.0, 32.0, 2.0, 18.0] ==> count = 5
        result (no.960) = [24.0, 32.0] ==> count = 2
        '''
        
    if (x_gen < (total_generate - 1)):
        result_matched_all.clear()
        result_matched_one_game.clear()
        result_predict_all.clear()
    print( "total random generated = {}/{}".format(x_gen, total_generate - 1) )


result_matched_all = list( set(result_matched_all) ) # remove duplicate item
result_matched_one_game = list( set(result_matched_one_game) ) # remove duplicate item
print( "result all (accumulative) " + "(" + result_won_game + ") =", result_matched_all, "==> count =", len(result_matched_all) )
print( "result " + "(" + result_won_game + ") =", result_matched_one_game, "==> count =", len(result_matched_one_game) )
print()
print( "result predict all =" )
for i in range(len(result_predict_all)):
    print( i, result_predict_all[i] )

'''
result:

result predict all =
0 [19. 27. 30.  1. 31. 35.]
1 [ 9. 24. 25.  7. 37. 32.]
2 [ 2. 44. 19.  1. 18. 11.]
3 [ 3.  9. 38. 28. 23. 18.]
4 [24. 30. 12. 27. 22. 31.]
'''
*/