/*
* Project:  lotto645 prediction
* Purpose:
* Author:   Ho-Jung Kim (godmode2k@hotmail.com)
* Date:     Since August 20, 2025
*
* modified:    Aug 20, 2025
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
// method4
// hjkim, 2025.08.20

/*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib> // rand()
#include <ctime> // time(), localtime()

#include <algorithm> // std::shuffle
#include <random> // std::default_random_engine and std::random_device
#include <chrono> // std::chrono::system_clock
*/

#include "model_lotto645_predicts_method.h"
#include "model_lotto645_results_winning_numbers.h"



#define MAX_PICK_RANGE          5 // [01..09, 10..19, 20..29, 30..39, 40..45]
#define MAX_PICK                3 // default: 3, available: 3, 4
#define MAX_PICK_OTHERS         (MAX_PICK_RANGE - MAX_PICK)
#define MAX_PREDICTIONS         5 // 10 games: 6 numbers x 10
#define MAX_NUMBERS_PER_GAME    6 // 1 game: 6 numbers


void _method4(int total_games, std::vector<char*>*& ret_result) {
//void method4(void) {
    const int stats_result_size = sizeof(results_winning_numbers)/sizeof(results_winning_numbers[0]);
    int stats_idx = 0;
    int stats_result[stats_result_size][1+6] = { {0,}, };
    
    int predictions_results[MAX_PREDICTIONS][MAX_NUMBERS_PER_GAME] = { {0,}, };

    //auto func_sort = [](auto src1, auto src2) -> bool { return src1 < src2; };
    // usage: std::sort( src_array_begin, src_array_end, func_sort );
    //
    //float arr[5] = { 1.f, 2.f, 3.f, 4.f, 5.f };
    //std::sort( arr, arr + 5, std::greater<float>() );
    //std::sort( std::begin(arr), std::end(arr), std::greater<float>() );
    //
    //std::array<int, 2> arr[5] = { { 5, 50 }, { 2, 20 }, { 4, 40 }, { 1, 10 }, { 3, 30 } };
    //std::sort( arr, arr + 5 ); std::sort( std::begin(arr), std::end(arr) );
    //auto sort_arr = []( const array<int, 2>& s1, const array<int, 2>& s2 ) { return s1[1] < s2[1]; };
    //std::sort( arr, arr + 5, sort_arr ); std::sort( std::begin(arr), std::end(arr), sort_arr );
    //
    // sort 2d array: 2d array to vector, sort
    //{
    //    int arr[9][2] = { {0, 0} };
    //    for ( int i = 1; i < 10; i++ ) {
    //        arr[i-1][0] = arr[i-1];
    //        arr[i-1][1] = i;
    //    }
    //
    //    std::vector<std::vector<int>> vec_arr;
    //    for ( int i = 1; i < 10; i++ ) {
    //        vec_arr.push_back( { arr[i-1], i } );
    //    }
    //    auto comp_2d_array_asc = [](const std::vector<int>& row1, const std::vector<int>& row2) {
    //        return row1[0] < row2[0];
    //    };
    //    auto comp_2d_array_desc = [](const std::vector<int>& row1, const std::vector<int>& row2) {
    //        return row1[0] > row2[0];
    //    };
    //    std::sort( vec_arr.begin(), vec_arr.end(), comp_2d_array_desc );
    //}


    //auto comp_2d_array_asc = [](const std::vector<int>& row1, const std::vector<int>& row2) {
    //    return row1[0] < row2[0];
    //};
    //auto comp_2d_array_desc = [](const std::vector<int>& row1, const std::vector<int>& row2) {
    //    return row1[0] > row2[0];
    //};
    auto comp_2d_array_desc = [](const auto& row1, const auto& row2) {
        return row1[0] > row2[0];
    };


    auto shuffle_range_and_pick_one = [](const int start, const int end) {
        //int result[end-start] = { 0, };
        std::vector<int> result( end - start );
        //if ( end > 0 ) { for ( int i = start; i < end; i++ ) { result[i] = i; } }
        if ( end > 0 ) {
            for ( int i = 0; i < (end - start); i++ ) {
                result[i] = (i + start);
                //printf( "%d ", result[i] );
            }
            //printf( "\n" );
        }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed); // or std::mt19937

        //std::random_device rd;
        //std::mt19937 rng(rd());

        //std::shuffle( std::begin(result), std::end(result), rng );
        std::shuffle( result.begin(), result.end(), rng );

        // pick one
        return result[0];
    };


    for ( auto x: results_winning_numbers ) {
        int count01 = 0;
        int count10 = 0;
        int count20 = 0;
        int count30 = 0;
        int count40 = 0;

        for ( int y = 1; y < (int)sizeof(x); y++ ) {
            if      ( x[y] >  0  && x[y] <  10 ) ++count01;
            else if ( x[y] >= 10 && x[y] <  20 ) ++count10;
            else if ( x[y] >= 20 && x[y] <  30 ) ++count20;
            else if ( x[y] >= 30 && x[y] <  40 ) ++count30;
            else if ( x[y] >= 40 && x[y] <= 45 ) ++count40;
        }
        stats_result[stats_idx][0] = x[0];
        stats_result[stats_idx][1] = count01;
        stats_result[stats_idx][2] = count10;
        stats_result[stats_idx][3] = count20;
        stats_result[stats_idx][4] = count30;
        stats_result[stats_idx][5] = count40;
        stats_result[stats_idx][6] = count01 + count40;
        stats_idx++;
    }

    printf( "total: %d\n", stats_result_size );


    // --------------------------------------------------------------
    // Statistics
    // --------------------------------------------------------------
    {
        // float type but int
        float sum01 = 0.f;
        float sum10 = 0.f;
        float sum20 = 0.f;
        float sum30 = 0.f;
        float sum40 = 0.f;
        float sum_01_40 = 0.f;

        for ( auto x: stats_result ) {
            //printf( "%4d: %2d, %2d, %2d, %2d, %2d, %2d\n", x[0], x[1], x[2], x[3], x[4], x[5], x[6] );
            sum01 += x[1]; sum10 += x[2]; sum20 += x[3]; sum30 += x[4]; sum40 += x[5]; sum_01_40 += x[6];
        }
        printf( "sum: %2.1f, %2.1f, %2.1f, %2.1f, %2.1f\n", sum01, sum10, sum20, sum30, sum40 );
        //printf( "01..10, 40..45 included: %d, %d (not)\n", sum_01_40, (stats_result_size-sum_01_40) );



        // pick number ranges by desc
        float sums_sort[MAX_PICK_RANGE] = { sum01, sum10, sum20, sum30, sum40 };
        int sums_sort_idx[MAX_PICK_RANGE] = { 0, };
        //char tag_pick_3[20];
        //char tag_pick_2[20];
        char tag_pick[20];
        char tag_pick_others[20];
        //float tag_pick_3_sum = sums_sort[0] + sums_sort[1] + sums_sort[2];
        //float tag_pick_2_sum = sums_sort[3] + sums_sort[4];
        float tag_pick_sum = 0.f;
        float tag_pick_sum_others = 0.f;
        //float tag_pick_3_avg = (tag_pick_3_sum / stats_result_size);
        //float tag_pick_2_avg = (tag_pick_2_sum / stats_result_size);
        float tag_pick_avg = 0.f;
        float tag_pick_avg_others = 0.f;

        //printf( "(sorted) sum = " );
        ////for ( auto x: sums_sort ) { printf( "%2.1f ", x ); } printf( "\n" );
        ////std::sort( sums_sort, sums_sort + MAX_PICK_RANGE, std::greater<float>() );
        //
        //! FIXME: if sum01 == sum10 ?
        // SEE: below vector sort
        //std::sort( std::begin(sums_sort), std::end(sums_sort), std::greater<float>() );

        {
            std::vector<std::vector<float>> vec_sums_sort;
            for ( int i = 0; i < MAX_PICK_RANGE; i++ ) {
                vec_sums_sort.push_back( { sums_sort[i], (i < 1)? 1 : (float)(i*10) } );
            }
            std::sort( vec_sums_sort.begin(), vec_sums_sort.end(), comp_2d_array_desc );
            for ( int i = 0; i < MAX_PICK_RANGE; i++ ) {
                sums_sort[i] = vec_sums_sort[i][0]; // value
                sums_sort_idx[i] = vec_sums_sort[i][1]; // actual array position
            }
        }
        printf( "(sorted) sum = " );
        for ( auto x: sums_sort ) { printf( "%2.1f ", x ); } printf( "\n" );


        /*
        {
            // checks max sum of a pair:
            // (01, 10), (10, 20), (20, 30), (30, 40), (40, 01)
            // (01, 10, 20), (10, 20, 30), (20, 30, 40), (30, 40, 01), (40, 01, 10)
            // (01, 10, 20, 30), (10, 20, 30, 40), (20, 30, 40, 01), (30, 40, 01, 10), (40, 01, 10, 20)

            // not sorted
            float _sums_sort[MAX_PICK_RANGE] = { sum01, sum10, sum20, sum30, sum40 };
            for ( int i = 0; i < (int)(sizeof(_sums_sort)/sizeof(_sums_sort)[0]); i++ ) {
                float old = 0.f;
                float cur = _sums_sort[i];
            }

            // sorted
            for ( int i = 0; i < (int)(sizeof(sums_sort)/sizeof(sums_sort)[0]); i++ ) {
                float old = 0.f;
                float cur = sums_sort[i];
            }
        }
        */


        // default: 3, available: 3, 4
        if ( MAX_PICK == 3) {
            tag_pick_sum = sums_sort[0] + sums_sort[1] + sums_sort[2];
            tag_pick_sum_others = sums_sort[3] + sums_sort[4];
        }
        else if ( MAX_PICK == 4) {
            tag_pick_sum = sums_sort[0] + sums_sort[1] + sums_sort[2] + sums_sort[3];
            tag_pick_sum_others = sums_sort[4];
        }
        tag_pick_avg = (tag_pick_sum / stats_result_size);
        tag_pick_avg_others = (tag_pick_sum_others / stats_result_size);


        {
            //for ( int i = 0; i < (int)(sizeof(sums_sort)/sizeof(sums_sort)[0]); i++ ) {
            //    //! FIXME: if sum01 == sum10 ?
            //    // SEE: above vector sort
            //    if      ( sums_sort[i] == sum01 ) sums_sort_idx[i] = 1;
            //    else if ( sums_sort[i] == sum10 ) sums_sort_idx[i] = 10;
            //    else if ( sums_sort[i] == sum20 ) sums_sort_idx[i] = 20;
            //    else if ( sums_sort[i] == sum30 ) sums_sort_idx[i] = 30;
            //    else if ( sums_sort[i] == sum40 ) sums_sort_idx[i] = 40;
            //}

            int sort_pick_idx[MAX_PICK] = { 0, };
            int sort_pick_idx_others[MAX_PICK_OTHERS] = { 0, };
            // pick first 3 index sorted by desc(greater)
            memcpy( sort_pick_idx, sums_sort_idx, sizeof(sums_sort_idx[0]) * 3 );
            // pick others (2 index) sorted by desc(greater)
            memcpy( sort_pick_idx_others, sums_sort_idx + 3, sizeof(sums_sort_idx[0]) * 2 );

            printf( "sort_pick_idx = " );
            for ( auto x: sort_pick_idx ) { printf( "%2d ", x ); } printf( "\n" );
            std::sort( std::begin(sort_pick_idx), std::end(sort_pick_idx), std::less<int>() );
            printf( "(sorted) sort_pick_idx = " );
            for ( auto x: sort_pick_idx ) { printf( "%2d ", x ); } printf( "\n" );

            printf( "sort_pick_idx_others = " );
            for ( auto x: sort_pick_idx_others ) { printf( "%2d ", x ); } printf( "\n" );
            std::sort( std::begin(sort_pick_idx_others), std::end(sort_pick_idx_others), std::less<int>() );
            printf( "(sorted) sort_pick_idx_others_ = " );
            for ( auto x: sort_pick_idx_others ) { printf( "%2d ", x ); } printf( "\n" );


            /*
            // pick (default: 3)
            {
                int offset = 0;
                for ( int i = 0; i < (int)(sizeof(sort_pick_idx)/sizeof(sort_pick_idx[0])); i++ ) {
                    char str_number[3] = "";

                    if      ( sort_pick_idx[i] == 1  ) { memcpy( str_number, "01", 2 ); }
                    else if ( sort_pick_idx[i] == 10 ) { memcpy( str_number, "10", 2 ); }
                    else if ( sort_pick_idx[i] == 20 ) { memcpy( str_number, "20", 2 ); }
                    else if ( sort_pick_idx[i] == 30 ) { memcpy( str_number, "30", 2 ); }
                    else if ( sort_pick_idx[i] == 40 ) { memcpy( str_number, "40", 2 ); }
                    str_number[sizeof(str_number)-1] = '\0';

                    offset += snprintf( tag_pick + offset, sizeof(tag_pick) - offset,
                            ((i == 0)? "%s" : "+%s"), str_number );
                }
                tag_pick[sizeof(tag_pick)-1] = '\0';
            }

            // pick (others)
            {
                int offset = 0;
                for ( int i = 0; i < (int)(sizeof(sort_pick_idx_others)/sizeof(sort_pick_idx_others[0])); i++ ) {
                    char str_number[3] = "";

                    if      ( sort_pick_idx_others[i] == 1  ) { memcpy( str_number, "01", 2 ); }
                    else if ( sort_pick_idx_others[i] == 10 ) { memcpy( str_number, "10", 2 ); }
                    else if ( sort_pick_idx_others[i] == 20 ) { memcpy( str_number, "20", 2 ); }
                    else if ( sort_pick_idx_others[i] == 30 ) { memcpy( str_number, "30", 2 ); }
                    else if ( sort_pick_idx_others[i] == 40 ) { memcpy( str_number, "40", 2 ); }
                    str_number[sizeof(str_number)-1] = '\0';

                    offset += snprintf( tag_pick_others + offset, sizeof(tag_pick_others) - offset,
                            ((i == 0)? "%s" : "+%s"), str_number );
                }
                tag_pick_others[sizeof(tag_pick_others)-1] = '\0';
            }
            */

            auto get_tag_pick = [](const auto src_pick_idx, const int src_len, auto& result, const int result_len) {
                int offset = 0;
                for ( int i = 0; i < src_len; i++ ) {
                    char str_number[3] = "";

                    if      ( src_pick_idx[i] == 1  ) { memcpy( str_number, "01", 2 ); }
                    else if ( src_pick_idx[i] == 10 ) { memcpy( str_number, "10", 2 ); }
                    else if ( src_pick_idx[i] == 20 ) { memcpy( str_number, "20", 2 ); }
                    else if ( src_pick_idx[i] == 30 ) { memcpy( str_number, "30", 2 ); }
                    else if ( src_pick_idx[i] == 40 ) { memcpy( str_number, "40", 2 ); }
                    str_number[sizeof(str_number)-1] = '\0';

                    offset += snprintf( result + offset, result_len - offset,
                            ((i == 0)? "%s" : "+%s"), str_number );
                }
                result[result_len-1] = '\0';
            };

            get_tag_pick( sort_pick_idx, (int)(sizeof(sort_pick_idx)/sizeof(sort_pick_idx[0])),
                    tag_pick, (int)(sizeof(tag_pick)) );
            get_tag_pick( sort_pick_idx_others, (int)(sizeof(sort_pick_idx_others)/sizeof(sort_pick_idx_others[0])),
                    tag_pick_others, (int)(sizeof(tag_pick_others)) );


            //printf( "tag pick 3 = %s\n", tag_pick_3 );
            //printf( "tag pick 2 = %s\n", tag_pick_2 );
            //printf( "tag pick = %s\n", tag_pick );
            //printf( "tag pick (others) = %s\n", tag_pick_others );
        }


        printf( "----------------------------------------------------------------\n"
                //"     01     10     20     30     40       10+20+30   01+40\n"
                "     01     10     20     30     40       %s      %6s\n"
                "----------------------------------------------------------------\n"
                //"sum: %2.1f %2.1f %2.1f %2.1f %2.1f   %2.1f     %2.1f\n"
                "sum: %2.1f %2.1f %2.1f %2.1f %2.1f   %2.1f         %2.1f\n"
                "     -----------------------------------------------------------\n"
                //"avg: %.3f  %.3f  %.3f  %.3f  %.3f    %.3f      %.3f\n"
                "avg: %.3f  %.3f  %.3f  %.3f  %.3f    %.3f          %.3f\n"
                //"     ---------------------------------------------------------\n"
                //"     %.3f  %.3f  %.3f  %.3f  %.3f    %.3f      %.3f        <-- (lower is more amount)\n"
                "----------------------------------------------------------------\n",

                tag_pick, tag_pick_others,

                sum01, sum10, sum20, sum30, sum40,

                //(sum10 + sum20 + sum30), sum_01_40,
                tag_pick_sum, tag_pick_sum_others,

                (sum01/stats_result_size), (sum10/stats_result_size), (sum20/stats_result_size),
                (sum30/stats_result_size), (sum40/stats_result_size),

                //((sum10 + sum20 + sum30)/stats_result_size), (sum_01_40/stats_result_size)
                tag_pick_avg, tag_pick_avg_others

                //(stats_result_size/sum01), (stats_result_size/sum10), (stats_result_size/sum20),
                //(stats_result_size/sum30), (stats_result_size/sum40),
                //
                //(stats_result_size/(sum10 + sum20 + sum30)), (stats_result_size/sum_01_40)
        );
    }
    printf( "\n\n" );


    /*
    // --------------------------------------------------------------
    // TEST
    // range: 10..19, 20..29, 30..39
    // --------------------------------------------------------------
    {
        int stats_10_20_30_idx = 0;
        int stats_10_20_30_result[stats_result_size][1+7] = { {0,}, };

        // range: MUST include 10..19, 20..29, 30..39
        for ( auto x: results_winning_numbers ) {
            bool found_10 = false;
            bool found_20 = false;
            bool found_30 = false;

            for ( int y = 1; y < (int)sizeof(x); y++ ) {
                if      ( x[y] >= 10 && x[y] < 20 ) found_10 = true;
                else if ( x[y] >= 20 && x[y] < 30 ) found_20 = true;
                else if ( x[y] >= 30 && x[y] < 40 ) found_30 = true;
            }

            if ( found_10 && found_20 && found_30 ) {
                stats_10_20_30_result[stats_10_20_30_idx][0] = x[0];
                stats_10_20_30_result[stats_10_20_30_idx][1] = x[1];
                stats_10_20_30_result[stats_10_20_30_idx][2] = x[2];
                stats_10_20_30_result[stats_10_20_30_idx][3] = x[3];
                stats_10_20_30_result[stats_10_20_30_idx][4] = x[4];
                stats_10_20_30_result[stats_10_20_30_idx][5] = x[5];
                stats_10_20_30_result[stats_10_20_30_idx][6] = x[6];
                stats_10_20_30_result[stats_10_20_30_idx][7] = x[7];
                stats_10_20_30_idx++;
            }
        }

        const int stat_sum_10_20_30_offset = 10;
        int stat_sum_10_20_30[10+10+10][1] = { {0,}, };
        //const int stat_sum_10_20_30_size = sizeof(stat_sum_10_20_30)/sizeof(stat_sum_10_20_30[0]);
        printf( "total (sum_10_20_30): %d (total winning: %d)\n", stats_10_20_30_idx, stats_result_size );
        printf( "(incl.10_20_30) vs (All-incl.10_20_30)\n--> %d (%3.f%%) : %4d (%3.f%%)\n",
                stats_10_20_30_idx, (((float)stats_10_20_30_idx / stats_result_size) * 100),
                (stats_result_size - stats_10_20_30_idx),
                (((float)(stats_result_size - stats_10_20_30_idx) / stats_result_size) * 100)
        );

        for ( auto x: stats_10_20_30_result ) {
            bool found = false;
            // x[0]: winning game number
            if ( x[0] <= 0 ) break; // stats_10_20_30_idx 

            //printf( "%d: %d, %d, %d, %d, %d, %d, %d\n", x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7] );

            for ( int y = 1; y < (int)sizeof(x); y++ ) {
                if      ( x[y] >= 10 && x[y] < 20 ) found = true;
                else if ( x[y] >= 20 && x[y] < 30 ) found = true;
                else if ( x[y] >= 30 && x[y] < 40 ) found = true;
                // skip value not 10~39
                else { continue; }

                if ( found ) {
                    // counting
                    int val = stat_sum_10_20_30[x[y]-stat_sum_10_20_30_offset][0] + 1;
                    // value position: x[y] = 10 -> stat_sum_10_20_30[10-offset][0] = val;
                    // start index 0: x[y] = 10 -> start_sum_10_20_30[0][0] = val;
                    stat_sum_10_20_30[x[y]-stat_sum_10_20_30_offset][0] = val;
                }
            }
        }

        //for ( int i = 10; i < 40; i++ ) { printf( "%d ", i ); } printf( "\n" );

        int val_idx = 0;
        int val = 0;
        // 1 ~ 39: 40
        for ( int i = 0; i < 30; i++ ) {
            int _val = stat_sum_10_20_30[i][0];

            // _val == 0: not found (no count)

            if ( val < _val ) {
                val = _val;
                val_idx = i;
            }

            if ( i > 0 && ((i+1) % 10 == 0) ) {
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (i+1), (i+stat_sum_10_20_30_offset),
                        (val_idx+stat_sum_10_20_30_offset), val );
                val = 0;
            }
        }


        //for ( int i = 10; i < 20; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 0; i < 10; i++ ) { printf( "%4d", stat_sum_10_20_30[i][0] ); } printf( "\n" );
        //for ( int i = 20; i < 30; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 10; i < 20; i++ ) { printf( "%4d", stat_sum_10_20_30[i][0] ); } printf( "\n" );
        //for ( int i = 30; i < 40; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 20; i < 30; i++ ) { printf( "%4d", stat_sum_10_20_30[i][0] ); } printf( "\n" );
        //printf( "----------\n" );

        //printf( "%d, %d, %d\n", stat_sum_10_20_30[0][0], stat_sum_10_20_30[10][0], stat_sum_10_20_30[20][0] );
        int sort_10_19[10] = { 0, };
        int sort_20_29[10] = { 0, };
        int sort_30_39[10] = { 0, };
        memcpy( sort_10_19, stat_sum_10_20_30[0],  sizeof(stat_sum_10_20_30[0]) * 10 );
        memcpy( sort_20_29, stat_sum_10_20_30[10], sizeof(stat_sum_10_20_30[0]) * 10 );
        memcpy( sort_30_39, stat_sum_10_20_30[20], sizeof(stat_sum_10_20_30[0]) * 10 );
        //printf( "%d, %d, %d\n", sort_10_19[0], sort_20_29[0], sort_30_39[0] );

        printf( "[10: 10..19]\n" );
        for ( int i = 10; i < 20; i++ ) { printf( "%4d", i ); } printf( "\n" );
        for ( auto x: sort_10_19 ) { printf( "%4d", x ); } printf( "\n" );
        printf( "[20: 20..29]\n" );
        for ( int i = 20; i < 30; i++ ) { printf( "%4d", i ); } printf( "\n" );
        for ( auto x: sort_20_29 ) { printf( "%4d", x ); } printf( "\n" );
        printf( "[30: 30..39]\n" );
        for ( int i = 30; i < 40; i++ ) { printf( "%4d", i ); } printf( "\n" );
        for ( auto x: sort_30_39 ) { printf( "%4d", x ); } printf( "\n" );
        //printf( "----------\n" );


        //std::sort( sort_10_19, sort_10_19, std::greater<float>() );



        // pick 4 numbers: 10..19 (2), 20..29 (1), 30..39 (1)
        printf( "pick 4 numbers: 10..19 (2), 20..29 (1), 30..39 (1)\n" );
        //max_predictions

    }
    printf( "\n" );
    */


    //printf( "--------------------------------------------------------------------\n" );

    // --------------------------------------------------------------
    // Max value of a pair
    //
    // Usage:
    // int results[5] = { 0, };
    // func_range( false, true, true, true, false, results );
    // --------------------------------------------------------------
    auto func_range = [](
            const bool _01, const bool _10, const bool _20, const bool _30, const bool _40,
            int results[])
    {
        int stats_range_idx = 0;
        int stats_range_result[stats_result_size][1+7] = { {0,}, };

        int ranges = 1; // ranges *= 1 * 10 * 20 * 30 * 40
        int ranges_count = 0;
        if ( _01 ) { ranges *= 1;  ++ranges_count; }
        if ( _10 ) { ranges *= 10; ++ranges_count; }
        if ( _20 ) { ranges *= 20; ++ranges_count; }
        if ( _30 ) { ranges *= 30; ++ranges_count; }
        if ( _40 ) { ranges *= 40; ++ranges_count; }

        //printf( "ranges count = %d\n", ranges_count );

        // range: MUST include range (01..09, 10..19, 20..29, 30..39, 40..45)
        for ( auto x: results_winning_numbers ) {
            bool found_01 = false;
            bool found_10 = false;
            bool found_20 = false;
            bool found_30 = false;
            bool found_40 = false;
            int found_ranges = 1; // ranges *= 1 * 10 * 20 * 30 * 40

            for ( int y = 1; y < (int)sizeof(x); y++ ) {
                if      ( x[y] >= 1  && x[y] <  10 ) { found_01 = true; }
                else if ( x[y] >= 10 && x[y] <  20 ) { found_10 = true; }
                else if ( x[y] >= 20 && x[y] <  30 ) { found_20 = true; }
                else if ( x[y] >= 30 && x[y] <  40 ) { found_30 = true; }
                else if ( x[y] >= 40 && x[y] <= 45 ) { found_40 = true; }
            }

            if ( _01 ) { if ( found_01 ) found_ranges *= 1;  }
            if ( _10 ) { if ( found_10 ) found_ranges *= 10; }
            if ( _20 ) { if ( found_20 ) found_ranges *= 20; }
            if ( _30 ) { if ( found_30 ) found_ranges *= 30; }
            if ( _40 ) { if ( found_40 ) found_ranges *= 40; }

            if ( found_ranges == ranges ) {
                stats_range_result[stats_range_idx][0] = x[0];
                stats_range_result[stats_range_idx][1] = x[1];
                stats_range_result[stats_range_idx][2] = x[2];
                stats_range_result[stats_range_idx][3] = x[3];
                stats_range_result[stats_range_idx][4] = x[4];
                stats_range_result[stats_range_idx][5] = x[5];
                stats_range_result[stats_range_idx][6] = x[6];
                stats_range_result[stats_range_idx][7] = x[7];
                stats_range_idx++;
            }
        }

#ifdef ENABLE_LOG
        const int stat_sum_range_offset = 10;
#endif

        int stat_sum_range[10+10+10+10+10][1] = { {0,}, }; // 01 ~ 45
        //const int stat_sum_range_size = sizeof(stat_sum_range)/sizeof(stat_sum_range[0]);
#ifdef ENABLE_LOG
        printf( "total (sum_<range>): %d (total winning: %d)\n", stats_range_idx, stats_result_size );
        printf( "[01..09]: %s, [10..19]: %s, [20..29]: %s, [30..39]: %s, [40..45]: %s\n",
                (_01)? "TRUE" : "FALSE", (_10)? "TRUE" : "FALSE", (_20)? "TRUE" : "FALSE",
                (_30)? "TRUE" : "FALSE", (_40)? "TRUE" : "FALSE" );
        printf( "(incl.<range>) vs (All-incl.<range>) --> %d (%3.f%%) : %4d (%3.f%%)\n",
                stats_range_idx, (((float)stats_range_idx / stats_result_size) * 100),
                (stats_result_size - stats_range_idx),
                (((float)(stats_result_size - stats_range_idx) / stats_result_size) * 100)
        );
#endif

        for ( auto x: stats_range_result ) {
            bool found = false;
            // x[0]: winning game number
            if ( x[0] <= 0 ) break; // stats_range_idx 

            //printf( "%d: %d, %d, %d, %d, %d, %d, %d\n", x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7] );

            for ( int y = 1; y < (int)sizeof(x); y++ ) {
                if      ( _01 && x[y] >= 1  && x[y] <  10 ) found = true;
                else if ( _10 && x[y] >= 10 && x[y] <  20 ) found = true;
                else if ( _20 && x[y] >= 20 && x[y] <  30 ) found = true;
                else if ( _30 && x[y] >= 30 && x[y] <  40 ) found = true;
                else if ( _40 && x[y] >= 40 && x[y] <= 45 ) found = true;
                else { continue; }

                if ( found ) {
                    // counting
                    int val = stat_sum_range[x[y]][0] + 1;
                    // value position: x[y] = 10 -> stat_sum_range[10][0] = val;
                    // start index 0: x[y] = 1 -> start_sum_10_20_30[0][0] = val;
                    stat_sum_range[x[y]][0] = val;
                }
            }
        }

        //for ( int i = 1; i < 46; i++ ) { printf( "%d ", i ); } printf( "\n" );

        int val_idx = 0;
        int val = 0;
        int max_count_idx[5] = { 0, };

        // 1 ~ 45: 45
        for ( int i = 0; i < 45; i++ ) {
            int _val = stat_sum_range[i][0];

            // _val == 0: not found (no count)

            if ( val < _val ) {
                val = _val;
                val_idx = i;
            }

            // 1 ~ 9
            if ( _01 && i == 9 ) {
#ifdef ENABLE_LOG
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (stat_sum_range_offset) - i, i, val_idx, val );
#endif
                max_count_idx[0] = val_idx;
                val = 0;
            }
            // 10 ~ 19
            else if ( _10 && i == 19 ) {
#ifdef ENABLE_LOG
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (i-stat_sum_range_offset) + 1, i, val_idx, val );
#endif
                max_count_idx[1] = val_idx;
                val = 0;
            }
            // 20 ~ 29
            else if ( _20 && i == 29 ) {
#ifdef ENABLE_LOG
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (i-stat_sum_range_offset) + 1, i, val_idx, val );
#endif
                max_count_idx[2] = val_idx;
                val = 0;
            }
            // 30 ~ 39
            else if ( _30 && i == 39 ) {
#ifdef ENABLE_LOG
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (i-stat_sum_range_offset) + 1, i, val_idx, val );
#endif
                max_count_idx[3] = val_idx;
                val = 0;
            }
            // 40 ~ 45
            else if ( _40 && i == 44 ) {
#ifdef ENABLE_LOG
                printf( "[%2d]: [%2d~%2d] num = %2d, count = %4d\n",
                        i, (i-4), (i + 1), val_idx, val );
#endif
                max_count_idx[4] = val_idx;
                val = 0;
            }
        }


        //for ( int i = 10; i < 20; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 0; i < 10; i++ ) { printf( "%4d", stat_sum_range[i][0] ); } printf( "\n" );
        //for ( int i = 20; i < 30; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 10; i < 20; i++ ) { printf( "%4d", stat_sum_range[i][0] ); } printf( "\n" );
        //for ( int i = 30; i < 40; i++ ) { printf( "%4d", i ); } printf( "\n" );
        //for ( int i = 20; i < 30; i++ ) { printf( "%4d", stat_sum_range[i][0] ); } printf( "\n" );
        //printf( "----------\n" );

        //printf( "%d, %d, %d\n", stat_sum_range[0][0], stat_sum_range[10][0], stat_sum_range[20][0] );
        int sort_01_09[9 ] = { 0, };
        int sort_10_19[10] = { 0, };
        int sort_20_29[10] = { 0, };
        int sort_30_39[10] = { 0, };
        int sort_40_45[6 ] = { 0, };
        memcpy( sort_01_09, stat_sum_range[1 ], sizeof(stat_sum_range[0]) * 9  ); // 1 ~ 9
        memcpy( sort_10_19, stat_sum_range[10], sizeof(stat_sum_range[0]) * 10 );
        memcpy( sort_20_29, stat_sum_range[20], sizeof(stat_sum_range[0]) * 10 );
        memcpy( sort_30_39, stat_sum_range[30], sizeof(stat_sum_range[0]) * 10 );
        memcpy( sort_40_45, stat_sum_range[40], sizeof(stat_sum_range[0]) * 6  );
        //printf( "%d, %d, %d, %d, %d\n",
        //    sort_01_09[0], sort_10_19[0], sort_20_29[0], sort_30_39[0], sort_40_45[0] );

        if ( _01 ) {
#ifdef ENABLE_LOG
            printf( "[01: 01..09]\n" );
            for ( int i = 1; i < 10; i++ ) { printf( "%4d", i ); } printf( "\n" );
            for ( auto x: sort_01_09 ) { printf( "%4d", x ); } printf( "\n" );
#endif
            //printf( "check...\n" );
            //for ( int i = 0; i < 10; i++ ) { printf( "%4d", *(stat_sum_range[i]) ); } printf( "\n" );
        }
        if ( _10 ) {
#ifdef ENABLE_LOG
            printf( "[10: 10..19]\n" );
            for ( int i = 10; i < 20; i++ ) { printf( "%4d", i ); } printf( "\n" );
            for ( auto x: sort_10_19 ) { printf( "%4d", x ); } printf( "\n" );
#endif
        }
        if ( _20 ) {
#ifdef ENABLE_LOG
            printf( "[20: 20..29]\n" );
            for ( int i = 20; i < 30; i++ ) { printf( "%4d", i ); } printf( "\n" );
            for ( auto x: sort_20_29 ) { printf( "%4d", x ); } printf( "\n" );
#endif
        }
        if ( _30 ) {
#ifdef ENABLE_LOG
            printf( "[30: 30..39]\n" );
            for ( int i = 30; i < 40; i++ ) { printf( "%4d", i ); } printf( "\n" );
            for ( auto x: sort_30_39 ) { printf( "%4d", x ); } printf( "\n" );
#endif
        }
        if ( _40 ) {
#ifdef ENABLE_LOG
            printf( "[40: 40..45]\n" );
            for ( int i = 40; i < 45+1; i++ ) { printf( "%4d", i ); } printf( "\n" );
            for ( auto x: sort_40_45 ) { printf( "%4d", x ); } printf( "\n" );
#endif
        }
        //printf( "----------\n" );


        //std::sort( sort_10_19, sort_10_19, std::greater<float>() );

        // pick 4 numbers: e.g., 10..19 (2), 20..29 (1), 30..39 (1)
        // pick 2 numbers: e.g, 01..09 (1), 40..45 (1)
//        printf( "\n[pick numbers...]\n" );
        //max_predictions

        // pick 4 numbers
        // xx ~ yy
        // 1. all : pick one number (max count) from selected ranges
        // 2. half: pick two number; [(1/2) | (1/2)]
        // 3. mid : pick one number; [(1/2) | (1/2) | (1/2)]
        // 4. pick one number in 4 numbers

        {
            //srand( (unsigned int)time(NULL) );
            //const int range = 10;
            //int val = rand() % range + 0; // range: 0 ~ 9 (10 rows)
            
            //for ( int r = 0; r < (int)odd_even_3_3.size(); r++ ) {
            //    // picks number one between 0 and 9
            //    index = rand() % range + 0; // range: 0 ~ 9 (10 rows)
            //}

            // shuffle
            // dup: -1 (ignore)
            auto shuffle_range = [](const int start, const int end, const int dup,
                    auto& result, const int result_len) {
                //if ( end > 0 ) { for ( int i = start; i < end; i++ ) { result[i] = i; } }
                if ( end > 0 ) {
                    //printf( "(not shuffle) (dup: %d -> [dup-1]) range = ", dup );
                    // -1: remove duplicate value
                    for ( int i = 0; i < (end - start) -1; i++ ) {
                        // start at 0: (dup-1)
                        if ( i == (dup-1) ) continue;
                        result[i] = (i + start);
                        //printf( "%d ", result[i] );
                    }
                    //printf( "\n" );
                }

                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::default_random_engine rng(seed); // or std::mt19937

                //std::random_device rd;
                //std::mt19937 rng(rd());

                //std::shuffle( arr.begin(), arr.end(), rng );
                std::shuffle( std::begin(result), std::end(result), rng );
            };

            //const int shuffle_result_len = 10;
            //int shuffle_result[shuffle_result_len] = { 0, };
            //shuffle_range( 0, 10, -1, shuffle_result, shuffle_result_len );
            //printf( "(shuffle) result = \n" );
            //for ( auto x: shuffle_result ) { printf( "%d ", x ); } printf( "\n" );


            // pick one number (max count) per selected ranges
            //for ( auto x: max_count_idx ) { printf( "%d ", x ); } printf( "\n" );


            // selected ranges
            for ( int i = 0; i < (int)(sizeof(max_count_idx)/sizeof(max_count_idx[0])); i++ ) {
                if ( max_count_idx[i] <= 0 ) continue;

                bool found = false;
                int numbers[10] = { 0, };
                int start = 0;
                int end = 10;
                int offset = 0;
                int val = max_count_idx[i];

                switch ( i ) {
                    case 0: { if ( _01 ) { found = true; offset = 0;  } } break;
                    case 1: { if ( _10 ) { found = true; offset = 10; } } break;
                    case 2: { if ( _20 ) { found = true; offset = 20; } } break;
                    case 3: { if ( _30 ) { found = true; offset = 30; } } break;
                    case 4: { if ( _40 ) { found = true; offset = 40; end = 5+1; } } break;
                    default: break;
                }

                if ( found ) {
                    // shuffle: 0 ~ 9
#ifdef ENABLE_LOG
                    printf( "target range: " );

                    for ( int j = start; j < end; j++ ) {
                        //numbers[j] = j;
                        if ( i == 0 && j == 0 ) continue;
                        if ( i > 0 ) printf( "%d ", j + offset );
                        else printf( "%d ", j );
                    }
                    printf( "offset = %d", offset );
                    printf( "\n" );
#endif
                    for ( int j = start; j < end; j++ ) { numbers[j] = j; }
                    //shuffle_range( 0, 0, -1, numbers, (int)(sizeof(numbers)/sizeof(numbers[0])) );


                    #define BOX_LEN 4
                    int box[BOX_LEN] = { 0, };

                    // 1. all: pick one number (max count) per selected ranges


                    // 2. half: pick two number; [(1/2) | (1/2)]

                    int pivot_halves = (end >> 1);
                    int pivot_halves_1 = (end >> 1);
                    int pivot_halves_2 = (end >> 1) + pivot_halves_1;
                    int pivot_halves_out_1 = 0;
                    int pivot_halves_out_2 = 0;
                    int _tmp[5] = { 0, };


                    // with checks duplicates
                    do {
                        // [0 ~ 5]
                        memset( _tmp, 0x0, sizeof(_tmp) );
                        shuffle_range( 0, pivot_halves_1, (val-offset),
                                _tmp, (int)(sizeof(_tmp)/sizeof(_tmp[0])) );
                        pivot_halves_out_1 = _tmp[0];

                        // 01..09: start at 1, so, +1
                        // 10, 20, 30, 40: start at 0 (SEE +offset below)
                        if ( offset == 0 ) pivot_halves_out_1 += 1;
                    } while ( (val - offset) == pivot_halves_out_1 );

                    // with checks duplicates
                    do {
                        // [5 ~ 10]
                        memset( _tmp, 0x0, sizeof(_tmp) );
                        shuffle_range( pivot_halves_1, pivot_halves_2, (val-offset),
                                _tmp, (int)(sizeof(_tmp)/sizeof(_tmp[0])) );
                        pivot_halves_out_2 = _tmp[0];

                        // 01..09: start at 1, so, +1
                        // 10, 20, 30, 40: start at 0 (SEE +offset below)
                        if ( offset == 0 ) pivot_halves_out_2 += 1;
                    } while ( ((val - offset) == pivot_halves_out_2) ||
                            (pivot_halves_out_1 == pivot_halves_out_2) );


                    // 3. mid: pick one number; [(1/2) | (1/2) | (1/2)]

                    int pivot_3rds_1 = ((pivot_halves+1) >> 1);
                    int pivot_3rds_2 = ((pivot_halves+1) >> 1) + pivot_halves - 1;
                    int pivot_3rds_out = 0;

                    // with checks duplicates
                    do {
                        memset( _tmp, 0x0, sizeof(_tmp) );
                        shuffle_range( pivot_3rds_1, pivot_3rds_2, (val-offset),
                                _tmp, (int)(sizeof(_tmp)/sizeof(_tmp[0])) );
                        pivot_3rds_out = _tmp[0];

                        // mid range: start at 1 or 10(x10)..40, so, +start(mid)
                        pivot_3rds_out += pivot_3rds_1;

                        // 01..09: start at 1, so, +1
                        // 10, 20, 30, 40: start at 0 (SEE +offset below)
                        if ( offset == 0 ) pivot_3rds_out += 1;
                    } while ( ((val - offset) == pivot_3rds_out) ||
                            (pivot_halves_out_1 == pivot_3rds_out) ||
                            (pivot_halves_out_2 == pivot_3rds_out) );


#ifdef ENABLE_LOG
                    printf( "pick positions: (%d), [mid: %d, %d, %d~%d] = %d, %d, %d\n",
                            val, pivot_halves_1, pivot_halves_2, pivot_3rds_1, pivot_3rds_2,
                            pivot_halves_out_1, pivot_halves_out_2, pivot_3rds_out );
#endif


                    // 4. pick one number in 4 numbers

                    box[0] = val; // pre-picked
                    // reset to actual value (+ offset)
                    box[1] = numbers[pivot_halves_out_1] + offset;
                    box[2] = numbers[pivot_halves_out_2] + offset;
                    box[3] = numbers[pivot_3rds_out] + offset;

#ifdef ENABLE_LOG
                    printf( "box = " );
                    for ( auto x: box ) { printf( "%d ", x ); } printf( "\n" );
#endif

                    shuffle_range( 0, 0, -1, box, BOX_LEN );

#ifdef ENABLE_LOG
                    printf( "(shuffle) box = " );
                    for ( auto x: box ) { printf( "%d ", x ); } printf( "\n" );
#endif


#ifdef ENABLE_LOG
                    // pick one: box[0]
                    printf( "pick one: box[0] = %d\n", box[0] );
#endif

                    //! NOTE: actual array position
                    // [0]: 01..09  
                    // [1]: 10..19  
                    // [2]: 20..29  
                    // [3]: 30..39  
                    // [4]: 40..45
                    // results: actual array position
                    results[i] = box[0];

//                    printf( "\n" );
                }
            }
        }
    }; // auto func_range = []() {}


    // for range 01..09
    //auto func_range_01_09_picks_2_num = [&](auto& result_picks, const bool display_info = false)
    //auto func_range_01_09_picks_2_num = [&](int (&result_picks)[2], const bool display_info = false)
    auto func_range_01_09_picks_2_num = [&](int result_picks[2], const bool display_info = false)
    {
        int stats_01_result[1+6] = { 0, };
        int count01_has_over_2 = 0;
        int count01_has_01_01_10_20_30 = 0; // [01..09]x2, ..., without [40..45]
        int stats_01_09_result[9] = { 0, };

        for ( auto x: results_winning_numbers ) {
            int count01_within_2 = 0;
            int count01 = 0;
            int count10 = 0;
            int count20 = 0;
            int count30 = 0;
            int count40 = 0;

            int _tmp = 0;
            for ( int y = 1; y < (int)sizeof(x); y++ ) {
                if      ( x[y] >  0  && x[y] <  10 ) ++_tmp;

                if ( _tmp >= 2 ) {
                    if ( x[y] >= 0 && x[y] < 10 ) { stats_01_09_result[x[y]] += 1; }
                }

                if      ( x[y] >= 0  && x[y] <  10 ) ++count01;
                else if ( x[y] >= 10 && x[y] <  20 ) ++count10;
                else if ( x[y] >= 20 && x[y] <  30 ) ++count20;
                else if ( x[y] >= 30 && x[y] <  40 ) ++count30;
                else if ( x[y] >= 40 && x[y] <= 45 ) ++count40;
            }
            if ( _tmp >= 2 ) {
                ++count01_within_2;
                if ( count01 > 0 && count10 > 0 && count20 > 0 && count30 > 0 )
                    ++count01_has_01_01_10_20_30;
            }
            else continue;

            ++count01_has_over_2;
            stats_01_result[0] += count01_within_2;
            stats_01_result[1] += count01;
            stats_01_result[2] += count10;
            stats_01_result[3] += count20;
            stats_01_result[4] += count30;
            stats_01_result[5] += count40;
            stats_01_result[6] = 0; // blank
        }


        //const float all = (stats_01_result[1] + stats_01_result[2] + stats_01_result[3]
        //        + stats_01_result[4] + stats_01_result[5]);

        // sort (desc): 60:40
        int stats_01_09_result_sort_6_to_4[9] = { 0 }; // sorted by desc: 6:4
        //int stats_01_09_result_sort[9][2] = { {0, 0} };
        //for ( int i = 1; i < 10; i++ ) {
        //    stats_01_09_result_sort[i-1][0] = stats_01_09_result[i-1];
        //    stats_01_09_result_sort[i-1][1] = i;
        //}
        std::vector<std::vector<int>> vec_stats_01_09_result_sort;
        for ( int i = 1; i < 10; i++ ) {
            vec_stats_01_09_result_sort.push_back( { stats_01_09_result[i-1], i } );
        }
        std::sort( vec_stats_01_09_result_sort.begin(), vec_stats_01_09_result_sort.end(),
                comp_2d_array_desc );
        for ( int i = 0; i < 10-1; i++ ) {
            stats_01_09_result_sort_6_to_4[i] = vec_stats_01_09_result_sort[i][1];
        }

        // random pick (60:40), each one
        auto shuffle_array_pick_one = [](const int arr[], const int len) {
            std::vector<int> v( len );

            for ( int i = 0; i < len; i++ ) { v[i] = arr[i]; }
            //for ( int i = 0; i < len; i++ ) { printf( "%2d ", v[i] ); } printf( "\n" );

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine rng(seed); // or std::mt19937

            //std::random_device rd;
            //std::mt19937 rng(rd());

            std::shuffle( std::begin(v), std::end(v), rng );

            // pick one
            return v[0];
        };


        int rate_6_idx = 0;

        if ( display_info ) {
            printf( "[01..09]: count >= 2\n" );
            printf( "----------------------------------------------------------------\n"
                    "     01     10     20     30     40     (true, false, ALL)\n"
                    "----------------------------------------------------------------\n"
                    "sum: %d   %d    %d    %d    %d    (%d, %d, %d)\n"
                    "     -----------------------------------------------------------\n"
                    "avg: %.3f  %.3f  %.3f  %.3f  %.3f            <-- ([01..09] count >= 2: %d)\n"
                    "----------------------------------------------------------------\n",
                    stats_01_result[1], stats_01_result[2], stats_01_result[3],
                    stats_01_result[4], stats_01_result[5], stats_01_result[0],
                    (stats_result_size - count01_has_over_2), stats_result_size,
                    (stats_01_result[1] / (float)stats_01_result[0]),
                    (stats_01_result[2] / (float)stats_01_result[0]),
                    (stats_01_result[3] / (float)stats_01_result[0]),
                    (stats_01_result[4] / (float)stats_01_result[0]),
                    (stats_01_result[5] / (float)stats_01_result[0]),
                    stats_01_result[0]
            );
            printf( "[40..45]: incl. %d (%.3f%%), exc. %d (%.3f%%)\n"
                    "----------------------------------------------------------------\n",
                    (stats_01_result[0] - count01_has_01_01_10_20_30),
                    (((stats_01_result[0] - count01_has_01_01_10_20_30) / (float)stats_01_result[0]) * 100),
                    count01_has_01_01_10_20_30,
                    ((count01_has_01_01_10_20_30 / (float)stats_01_result[0]) * 100)
            );
            printf( "\t[01..09]\n" );
            printf( "\t-------------------------------------------------------------------------\n" );
            printf( "\t" );
            for ( int i = 1; i < 10; i++ ) { printf( "%d\t", i ); } printf( "\n" );
            printf( "\t-------------------------------------------------------------------------\n" );
            int stats_01_09_result_sum = 0;
            for ( auto x: stats_01_09_result ) { stats_01_09_result_sum += x; }
            printf( "sum: \t" );
            for ( auto x: stats_01_09_result ) { printf( "%d\t", x ); } printf( "\n" );
            printf( "\t-------------------------------------------------------------------------\n" );
            printf( "avg: \t" );
            for ( auto x: stats_01_09_result ) {
                printf( "%.3f\t", (x / (float)stats_01_09_result_sum) * 100 );
            } printf( "\n" );
            printf( "----------------------------------------------------------------\n" );
            printf( "sorted: desc\n" );
            printf( "\t" );
            for ( auto x: vec_stats_01_09_result_sort ) { printf( "%d\t", x[1] ); } printf( "\n" );
            printf( "\t" );
            for ( auto x: vec_stats_01_09_result_sort ) { printf( "%d\t", x[0] ); } printf( "\n" );
            printf( "----------------------------------------------------------------\n" );
            printf( "range 60%% : 40%%\n" );
            float j = 0.f;
            for ( int i = 0; i < (int)vec_stats_01_09_result_sort.size(); i++ ) {
                j += ((vec_stats_01_09_result_sort[i][0] / (float)stats_01_09_result_sum) * 100);
                if ( j > 60.f ) { rate_6_idx = i; break; }
            }
            printf( "60%%: \t" );
            for ( int i = 0; i < (int)vec_stats_01_09_result_sort.size(); i++ ) {
                if ( i == rate_6_idx+1 ) { printf( "\n40%%: \t" ); }
                printf( "%d\t", vec_stats_01_09_result_sort[i][1] );
            } printf( "\n" );
            printf( "\n" );
        }


        result_picks[0] = shuffle_array_pick_one( stats_01_09_result_sort_6_to_4, (rate_6_idx + 1) );
        result_picks[1] = shuffle_array_pick_one( stats_01_09_result_sort_6_to_4 + (rate_6_idx + 1),
                (sizeof(stats_01_09_result_sort_6_to_4) / sizeof(stats_01_09_result_sort_6_to_4[0]))
                - (rate_6_idx + 1) );
        //printf( "picks: %2d, %2d\n", result_picks[0], result_picks[1] );
    }; // for range 01..09: auto func_range_01_09_picks_2_num = []() {}
    //int picks_2_num_range_01_09[2] = { 0, };
    //bool display_info = true;
    //func_range_01_09_picks_2_num( picks_2_num_range_01_09, display_info );


    //printf( "--------------------------------------------------------------------\n" );


    // --------------------------------------------------------------
    // Max value of a pair
    // --------------------------------------------------------------
    {
        //! NOTE: actual array position
        // [0]: 01..09  
        // [1]: 10..19  
        // [2]: 20..29  
        // [3]: 30..39  
        // [4]: 40..45
        int results[5] = { 0, };

        // func_range_01_09_picks_2_num() {}
        bool display_info = true; // only once at first

        for ( int i = 0; i < MAX_PREDICTIONS; i++ ) {
            memset( results, 0x0, sizeof(results) );

            // pair [10..19, 20..29, 30..39]
            func_range( false, true, true, true, false, results );

//            printf( "\n" );

            // pair [01..09, 40..45]
            func_range( true, false, false, false, true, results );

            {
                // for replace range 40..45 with range 20..29, at [4]
                // pair [20..29]
                int tmp[5] = { 0, };
                do {
                    memset( tmp, 0x0, sizeof(tmp) );
                    func_range( false, false, true, false, false, tmp );
                } while ( (results[0] == tmp[2]) ||
                        (results[1] == tmp[2]) ||
                        (results[2] == tmp[2]) ||
                        (results[3] == tmp[2]) ||
                        (results[4] == tmp[2]) );
                results[4] = tmp[2];
            }

            /*
            {
                // last game: 40..45 included
                if ( (i > 1) && i == (MAX_PREDICTIONS - 1) ) {
                    // pair [40..45]
                    int tmp[5] = { 0, };
                    func_range( false, false, false, false, true, tmp );
                    results[4] = tmp[4];
                }
            }
            */


#ifdef ENABLE_LOG
            printf( "results (5 numbers) = " );
            for ( auto x: results ) { printf( "%d ", x ); } printf( "\n" );
#endif

            // last one number
            // select ranges: 01, 10, 20, 30, 40
            //int results_last_one[5] = { 0, };
            //func_range( true, false, false, false, true, results_last_one );
            // or
            // random pick: 1 ~ 45
            int last_one = 0;
            
            do {
                last_one = shuffle_range_and_pick_one( 1, 45+1 );
#ifdef ENABLE_LOG
                printf( "result (last pick one, 1 number) = %d\n", last_one );
#endif
            } while ( (results[0] == last_one) ||
                    (results[1] == last_one) ||
                    (results[2] == last_one) ||
                    (results[3] == last_one) ||
                    (results[4] == last_one) );


            //for ( int x = 0; x < (int)(sizeof(results)/sizeof(results[0])); x++ ) {
            //    predictions_results[i][x] = results[x];
            //}
            // ignore sizeof(): sizeof(predictions_results[i][0]) > sizeof(results)
            memcpy( predictions_results[i], results, sizeof(results) );
            predictions_results[i][MAX_NUMBERS_PER_GAME-1] = last_one;


            // range 01..09 picks 2 numbers
            // this is for last row per 5 games
            {
                // MAX_PREDICTIONS (== 5)
                if ( (i > 0) && ((i+1) % 5) == 0 ) {
                    int picks_2_num_range_01_09[2] = { 0, };
                    func_range_01_09_picks_2_num( picks_2_num_range_01_09, display_info );
                    display_info = false; // only once at first

#ifdef ENABLE_LOG
                    // last row per 5 games
                    printf( "before:\n" );
                    for ( auto x: predictions_results[i] ) { printf( "%2d ", x ); } printf( "\n" );
#endif

                    predictions_results[i][0] = picks_2_num_range_01_09[0];
                    predictions_results[i][MAX_NUMBERS_PER_GAME-1] = picks_2_num_range_01_09[1];

#ifdef ENABLE_LOG
                    printf( "after:\n" );
                    for ( auto x: predictions_results[i] ) { printf( "%2d ", x ); } printf( "\n" );
#endif
                }
            }
        }
    }
    printf( "\n" );


    // --------------------------------------------------------------
    // --------------------------------------------------------------
    {
        const char* day_of_the_week[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        time_t current_time = time( NULL );
        struct tm* now = localtime( &current_time );
        printf( "%4d.%02d.%02d %s %02d:%02d:%02d\n",
                (now->tm_year + 1900), (now->tm_mon + 1), now->tm_mday,
                day_of_the_week[now->tm_wday],
                now->tm_hour + 9, now->tm_min, now->tm_sec );

        printf( "------------------------------------------\n" );
        printf( "[Predictions] %d games\n", MAX_PREDICTIONS );
        printf( "------------------------------------------\n" );
        //printf( "     " );
        //for ( int i = 0; i < MAX_NUMBERS_PER_GAME; i++ ) { printf( "%2d ", i ); } printf( "\n" );
        for ( int i = 0; i < MAX_PREDICTIONS; i++ ) {
            printf( "[%2d] ", i );
            for ( auto x: predictions_results[i] ) printf( "%2d ", x );
            if ( (i > 0) && ((i+1) % 5) == 0 ) {
                // range 01..09 picks 2 numbers
                // this is for last row per 5 games
                printf( "\t<-- (for [01..09]x2 pattern: [0] and [5] always in the range [01..09],\n"
                        "\t\t\t\tlast row per 5 games)" );
            }
            printf( "\n" );
        }
        printf( "------------------------------------------\n" );
    }
    printf( "\n" );


    ///*
    //! one game (6 numbers) only
    {
        //const int elem_size = 6;
        //int* elem = new int[elem_size];
        //elem[0] = predictions_results[0][0]
        //elem[1] = predictions_results[0][1]
        //elem[2] = predictions_results[0][2]
        //elem[3] = predictions_results[0][3]
        //elem[4] = predictions_results[0][4]
        //elem[5] = predictions_results[0][5]
        ////ret_result->push_back( elem );
        //auto it = ret_result->begin();
        //it = ret_result->insert( it, elem );

        if ( ret_result != NULL ) {
            const int BUF_LEN = 12 + 5 + 10 + 1; // 12 (numbers: 2*6), 5 (','), 10 ('  ': 2*5)
            char* buf = new char[BUF_LEN];
            snprintf( buf, BUF_LEN, "%02d,  %02d,  %02d,  %02d,  %02d,  %02d",
                        predictions_results[0][0],
                        predictions_results[0][1],
                        predictions_results[0][2],
                        predictions_results[0][3],
                        predictions_results[0][4],
                        predictions_results[0][5]
            );
            ret_result->push_back( buf );
        }
    }
    //*/
}

void method4(int total_games, std::vector<char*>*& ret_result) {
    // for display last game (number of games: no.1 ~ present)
    {
        if ( ret_result != NULL ) {
            const int BUF_DESC_LEN = 100;
            char* buf_last_game = new char[BUF_DESC_LEN];
            snprintf( buf_last_game, BUF_DESC_LEN, "%s", LAST_GAME );
            ret_result->push_back( buf_last_game );
        }
    }

    for ( int i = 0; i < total_games; i++ ) { _method4( total_games, ret_result ); }
}

#if 0
int main(void) {
    //method4();

    /*
    {
        const int total_games = 5;
        //std::vector<int*>* result = new std::vector<int*>;
        std::vector<char*>* result = new std::vector<char*>;

        method4( total_games, result );

        //printf( "------------------------------------------\n" );
        //printf( "test from main()\n" );
        //printf( "------------------------------------------\n" );
        //std::cout << "result:" << std::endl;
        //for ( auto x: *result ) { printf( "%s\n", x ); } printf( "\n" );

        // Integer
        //std::vector<int*>::iterator iter;
        //for ( iter = result->begin(); iter != result->end(); ++iter ) {
        //    int* val = (*iter); delete[] val; val = NULL;
        //}
        //result->clear();
        //delete result;
        //result = NULL;
        //
        //for ( auto x: *result ) { int* _x = x; delete[] _x; }

        for ( auto x: *result ) { char* _x = x; delete[] _x; }

        result->clear();
        delete result;
        result = NULL;
    }
    */

    return 0;
}
#endif

