/*
* Project:  lotto645 prediction
* Purpose:
* Author:   Ho-Jung Kim (godmode2k@hotmail.com)
* Date:     Since April 25, 2021
*
* modified:    Mar 28, 2024
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

#include "model_lotto645_predicts_method.h"
#include "model_lotto645_results_winning_numbers.h"



int odd_even(std::vector<char*>*& ret_result, std::vector<float*>*& ret_result_float) {
//int odd_even(int _total_generate, int _total_games, std::vector<char*>*& ret_result) {
//int odd_even(void) {
/*
# ------------------------------
# for Odd, Even
# ------------------------------
# 1. split 10 rows from result
# 2. picks odd, even each 3 (odd, even:  3:3)

#        1     2     3     4     5      6  bonus    sum
#43   0.00  0.00  0.00  2.00 30.00 118.00     35 185.00
#...
#20   5.00 31.00 61.00 34.00 16.00   4.00     25 176.00
# -----
#14  31.00 52.00 46.00 25.00  1.00   0.00     21 176.00
#...
#6   82.00 44.00 12.00  3.00  0.00   0.00     31 172.00
# -----
#31   0.00  4.00 23.00 57.00 44.00  17.00     26 171.00
#...
#16  22.00 38.00 48.00 31.00  3.00   0.00     26 168.00
# -----
#21   8.00 29.00 40.00 45.00 20.00   3.00     22 167.00
#...
#28   0.00  4.00 36.00 38.00 42.00  11.00     21 152.00
# -----
#23   3.00 23.00 36.00 49.00 18.00   4.00     18 151.00
#41   0.00  0.00  0.00 10.00 52.00  72.00     15 149.00
#29   1.00  5.00 32.00 41.00 46.00   9.00     14 148.00
#22   5.00 21.00 43.00 38.00 19.00   3.00     14 143.00
#9   39.00 54.00 18.00  4.00  1.00   0.00     24 140.00
*/


    // float odd_even_code[45][9] = { ... };
    const int max_numbers = (sizeof(odd_even_code) / sizeof(float)) / (sizeof(odd_even_code[0]) / sizeof(float));
    const int select_max_size = 6;
    const int split_row_size = 10;
    std::cout << "size = " << max_numbers << std::endl;

    std::vector<float*> result_odd_even_3_3;
    std::vector<float> odd_even_3_3;
    std::vector<float> odd_even_3_3_not_selected;


    srand( (unsigned int)time(NULL) );

    for ( int i = 0; i < max_numbers; i++ ) {
        odd_even_3_3.push_back( odd_even_code[i][0] );

        // split 10 rows
        if ( (i > 0 && (i+1) % split_row_size == 0) || (i+1 == max_numbers) ) {
            std::vector<float> result_select;

            // last row (5 values) + un-selected values(?)
            if ( result_odd_even_3_3.size() == 4 ) {
                for ( auto x: odd_even_3_3_not_selected ) {
                    odd_even_3_3.push_back( x );
                }
            }

            // [0] odd count
            // [1] even count
            int _odd_even_count_per_10rows[2] = { 0, };
            int odd_count = 0;
            int even_count = 0;
            int loop_cnt = 0;

            // odd, even count
            [](std::vector<float> odd_even_3_3, int* ret_count) {
                for ( auto x: odd_even_3_3 ) {
                    if ( (int)x%2 != 0 ) ++ret_count[0];
                    else ++ret_count[1];
                }
            } (odd_even_3_3, _odd_even_count_per_10rows);

#ifdef ENABLE_LOG
            std::cout << "odd_even_3_3 = [";
            for ( auto x: odd_even_3_3 ) { std::cout << x << ", "; }
            std::cout << "], odd = " << _odd_even_count_per_10rows[0] << ", even = " <<  _odd_even_count_per_10rows[1] << std::endl;
#endif

            while ( result_select.size() < 6 ) {
                int sel = -1;
                int index = 0;

                index = rand() % split_row_size + 0; // range: 0 ~ 9 (10 rows)
                //for ( int r = 0; r < (int)odd_even_3_3.size(); r++ ) {
                //    // picks number one between 0 and 9
                //    index = rand() % split_row_size + 0; // range: 0 ~ 9 (10 rows)
                //}
                sel = (int)odd_even_3_3[index];

                auto ret = std::find( result_select.begin(), result_select.end(), sel );
                if ( ret == result_select.end() ) {
                    if ( sel%2 != 0 ) {
                        // odd
                        if ( odd_count < 3 ) {
                            odd_count += 1;
                            result_select.push_back( odd_even_3_3[index] );
                            //std::cout << "index = " << index << ", sel = " << sel << ", odd_count = " << odd_count << std::endl;
                        }
                        else if ( i+1 == max_numbers ) {
                            //std::cout << "odd_count = " << odd_count << ", even_count = " << even_count << std::endl;

                            if ( _odd_even_count_per_10rows[1] <= 1 ) { // [1]: even
                                int sel_new = -1;

                                for ( int j: odd_even_3_3 ) {
                                    if ( j%2 != 0 ) {
                                        sel_new = j - 1;
                                        if ( sel_new <= 0 ) sel_new += 1;

                                        auto ret = std::find( result_select.begin(), result_select.end(), sel_new );
                                        if ( (result_select.size() < select_max_size) &&
                                                (ret == result_select.end()) ) {
                                            result_select.push_back( sel_new );
                                        }
                                    }
                                }
                            }
                        }
                    } // if: odd
                    else {
                        // even
                        if ( even_count < 3 ) {
                            even_count += 1;
                            result_select.push_back( odd_even_3_3[index] );
                            //std::cout << "index = " << index << ", sel = " << sel << ", odd_count = " << even_count << std::endl;
                        }
                        else if ( i+1 == max_numbers ) {
                            //std::cout << "odd_count = " << odd_count << ", even_count = " << even_count << std::endl;

                            if ( _odd_even_count_per_10rows[0] <= 1 ) { // [0]: odd
                                int sel_new = -1;

                                for ( int j: odd_even_3_3 ) {
                                    if ( j%2 == 0 ) {
                                        sel_new = j + 1;
                                        if ( sel_new > 45 ) sel_new -= 1;

                                        auto ret = std::find( result_select.begin(), result_select.end(), sel_new );
                                        if ( (result_select.size() < select_max_size) &&
                                                (ret == result_select.end()) ) {
                                            result_select.push_back( sel_new );
                                        }
                                    }
                                }
                            }
                        }
                    } // else: even
                } // if ( ret == result_select.end() ) {}

                loop_cnt += 1;
                if ( loop_cnt >= 10 ) {
                    while ( result_select.size() < 6 ) {
                        int new_sel = -1;
                        int new_index = 0;

                        //std::cout << "select anyone either even or odd" << std::endl;
                        new_index = rand() % split_row_size + 0; // range: 0 ~ 9 (10 rows)
                        new_sel = (int)odd_even_3_3[new_index];

                        auto ret = std::find( result_select.begin(), result_select.end(), new_sel );
                        if ( ret == result_select.end() ) {
                            // odd
                            if ( _odd_even_count_per_10rows[0] == odd_count ) {}
                            else {
                                odd_count += 1;
                            }

                            // even
                            if ( _odd_even_count_per_10rows[1] == even_count ) {}
                            else {
                                even_count += 1;
                            }

                            result_select.push_back( odd_even_3_3[new_index] );
                        }
                    }
                }
            } // while ( result_select.size() < 6 ) {}

            int j = 0;
            float* selected_numbers = new float[select_max_size];
            //float selected_numbers[select_max_size] = { 0, };
            //std::cout << "[";
            for ( auto x: result_select ) {
                selected_numbers[j++] = x;
                //std::cout << x << ", ";
            }
            //std::cout << "]" << std::endl;
            result_odd_even_3_3.push_back( selected_numbers );

            if ( ret_result_float != NULL ) {
                j = 0;
                float* ret_selected_numbers = new float[select_max_size];
                for ( auto x: result_select ) {
                    ret_selected_numbers[j++] = x;
                }
                ret_result_float->push_back( ret_selected_numbers );
            }

            // last row (5 values) + un-selected values(?)
            if ( result_odd_even_3_3.size() < 5 ) {
                //std::cout << "odd_even_3_3 len = " << odd_even_3_3.size() << std::endl;

                for ( auto x: odd_even_3_3) {
                    //std::cout << x << ", ";
                    auto pos = std::find( result_select.begin(), result_select.end(), x );
                    if ( pos == result_select.end() ) {
                        odd_even_3_3_not_selected.push_back( x );
                    }
                }

                for ( auto x: odd_even_3_3_not_selected ) {
                    odd_even_3_3.push_back( x );
                }
            }

            odd_even_3_3.clear();
        } // if ( (i > 0 && (i+1) % 10 == 0) || (i+1 == max_numbers) ) {}
    } // for ( int i = 0; i < max_numbers; i++ ) {}


    const int BUF_LEN = 12 + 5 + 10 + 1; // 12 (numbers: 2*6), 5 (','), 10 ('  ': 2*5)
    const int BUF_DESC_LEN = 100;

    // for display last game (number of games: no.1 ~ present)
    {
        if ( ret_result != NULL ) {
            char* buf_last_game = new char[BUF_DESC_LEN];
            snprintf( buf_last_game, BUF_DESC_LEN, "%s", LAST_GAME );
            ret_result->push_back( buf_last_game );
        }
    }

#ifdef ENABLE_LOG
    std::cout << "------------------------------" << std::endl;
    std::cout << "result:" << std::endl;
#endif
    for ( auto x: result_odd_even_3_3 ) {
#ifdef ENABLE_LOG
        std::cout << "["
            << x[0] << ", " << x[1] << ", " << x[2] << ", "
            << x[3] << ", " << x[4] << ", " << x[5]
            << "]" << std::endl;
#endif

        if ( ret_result != NULL ) {
            char* buf = new char[BUF_LEN];
            snprintf( buf, BUF_LEN, "%02d,  %02d,  %02d,  %02d,  %02d,  %02d",
                        (int)x[0], (int)x[1], (int)x[2], (int)x[3], (int)x[4], (int)x[5] );
            ret_result->push_back( buf );
        }
    }
#ifdef ENABLE_LOG
    std::cout << "------------------------------" << std::endl;
#endif
    for ( auto x: result_odd_even_3_3 ) {
        float* val = x;
        delete[] val;
    }

    result_odd_even_3_3.clear();

    return 0;
}

int method3(std::vector<char*>*& ret_result, std::vector<float*>*& in) {
    std::vector<float> result_odd_even_3_3_flatten;
    for ( auto x: *in ) {
        for ( int y = 0; y < 6; y++ ) { // 6 values per row (5 rows)
            result_odd_even_3_3_flatten.push_back( x[y] );
            //std::cout << y << std::endl;
        }
    }

    {
        std::cout << "release allocated... [" << std::endl;
        std::vector<float*>::iterator iter;
        for ( iter = in->begin(); iter != in->end(); ++iter ) {
            float* numbers = (*iter);
            delete numbers;
            numbers = NULL;
        }
        in->clear();
        delete in;
        in = NULL;
        std::cout << "release allocated... ]" << std::endl;
    }

    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
    std::cout << "]" << std::endl;


    std::vector<std::vector<float>*> result_random_choice;
    std::vector<float> duplicate_sel;
    auto func_search_val = [](auto src, auto val) {
        auto pos = std::find( src.begin(), src.end(), val );
        if ( pos == src.end() ) {
            //std::cout << "pos (not found): " << std::distance(src.begin(), pos) << std::endl;
            return (int)-1;
        }
        //std::cout << "pos (duplicated): " << std::distance(src.begin(), pos) << std::endl;
        return (int)std::distance(src.begin(), pos);
    };

    while ( result_random_choice.size() < 5 ) {
        std::vector<float>* random_choice = new std::vector<float>;

        while ( random_choice->size() < 6 ) {
            if ( result_odd_even_3_3_flatten.size() == 0 ) break;

            //std::cout << result_odd_even_3_3_flatten.size() << ", " << duplicate_sel.size() << std::endl;

            bool sel_found = false;
            int index = rand() % result_odd_even_3_3_flatten.size() + 0; // range: 0 ~ 30 (6 val per row(5 rows)
            int sel = (int)result_odd_even_3_3_flatten[index];
            //std::cout << "index = " << index << ", sel = " << sel << std::endl;

            if ( result_random_choice.size() == 0 ) {
                if ( random_choice->size() > 0 ) {
                    for ( auto x: *random_choice ) {
                        //std::cout << "sel: " << sel << ", random_choice: " << x << std::endl;
                        if ( sel == x ) {
                            sel_found = true;

                            int idx = func_search_val( result_odd_even_3_3_flatten, sel );
                            if ( idx >= 0 ) {
                                //std::cout << "#0: found: idx = " << idx << ", " << sel << std::endl;
                                if ( func_search_val(result_odd_even_3_3_flatten, idx) >= 0 ) {
                                    duplicate_sel.push_back( result_odd_even_3_3_flatten[idx] );
                                }
                                result_odd_even_3_3_flatten.erase( result_odd_even_3_3_flatten.begin() + idx );
//{
//    std::cout << "deleted:" << std::endl;
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//
//    std::cout << "dup len = " << duplicate_sel.size() << ", [";
//    for ( auto x: duplicate_sel ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}

                            }
                            break;
                        } // if ( sel == x ) {}
                    } // for ( auto x: *random_choice ) {}
                } // if ( random_choice->size() > 0 ) {}

                if ( sel_found == false ) {
                    random_choice->push_back( sel );

                    //std::cout << "   -> not found... add: " << sel << std::endl;
                    //std::cout << "[";
                    //for ( auto x: random_choice ) std::cout << x ", ";
                    //std::cout << "]" << std::endl;
                    int idx = func_search_val( result_odd_even_3_3_flatten, sel );
                    if ( idx >= 0 ) {
                        result_odd_even_3_3_flatten.erase( result_odd_even_3_3_flatten.begin() + idx );
//{
//    std::cout << "deleted:" << std::endl;
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}
                    }
                }
            } // if ( result_random_choice.size() == 0 ) {}
            else {
                //std::cout << "list = " << std::endl;
                //for ( auto x: result_odd_even_3_3_flatten ) std::cout << x << ", ";
                //std::cout << std::endl;

                for ( auto x: *random_choice ) {
                    //std::cout << "sel: " << sel << ", random_choice: " << x << std::endl;
                    if ( sel == x ) {
                        sel_found = true;

                        int idx = func_search_val( result_odd_even_3_3_flatten, sel );
//{
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}

                        //std::cout << "#1: found: idx = " << idx << ", " << sel << std::endl;
                        if ( idx >= 0 ) {
                            if ( func_search_val(duplicate_sel, result_odd_even_3_3_flatten[idx]) >= 0 ) {
                                duplicate_sel.push_back( result_odd_even_3_3_flatten[idx] );
                            }
                            result_odd_even_3_3_flatten.erase( result_odd_even_3_3_flatten.begin() + idx );
//{
//    std::cout << "deleted:" << std::endl;
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//
//    std::cout << "dup len = " << duplicate_sel.size() << ", [";
//    for ( auto x: duplicate_sel ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}
                            break;
                        }
                    } // if ( sel == x ) {}
                } // for ( auto x: *random_choice ) {}


                if ( sel_found == true ) break;


                //sel_found = false;
                for ( int i = 0; i < result_random_choice.size(); i++ ) {
                    //std::cout << "sel = " << sel << ", " << result_random_choice[i] << std::endl;

                    for ( auto x: *result_random_choice[i] ) {
                        if ( sel == x ) {
                            int idx = func_search_val( result_odd_even_3_3_flatten, sel );
                            if ( idx >= 0 ) {
//{
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}

                                sel_found = true;
                                //std::cout << "#2: found: idx = " << idx << ", " << sel << std::endl;

                                if ( func_search_val(duplicate_sel, result_odd_even_3_3_flatten[idx]) >= 0 ) {
                                    duplicate_sel.push_back( result_odd_even_3_3_flatten[idx] );
                                }
                                result_odd_even_3_3_flatten.erase( result_odd_even_3_3_flatten.begin() + idx );
//{
//    std::cout << "deleted:" << std::endl;
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//
//    std::cout << "dup len = " << duplicate_sel.size() << ", [";
//    for ( auto x: duplicate_sel ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}
                                break;
                            } // if ( idx >= 0 ) {}
                        } // if ( sel == x ) {}
                    } // for ( auto x: *result_random_choice[i] ) {}
                    if ( sel_found == true ) break;
                } // for ()


                if ( sel_found == false ) {
                    random_choice->push_back( sel );

                    //std::cout << "   -> not found... add: " << sel << std::endl;
                    //std::cout << "[";
                    //for ( auto x: random_choice ) std::cout << x ", ";
                    //std::cout << "]" << std::endl;
                    int idx = func_search_val( result_odd_even_3_3_flatten, sel );
                    if ( idx >= 0 ) {
                        result_odd_even_3_3_flatten.erase( result_odd_even_3_3_flatten.begin() + idx );
//{
//    std::cout << "deleted:" << std::endl;
//    std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
//    for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}
                    }
                }
            } // else {}
//{
//    std::cout << "random_choice len = " << random_choice->size() << ", [";
//    for ( auto x: *random_choice) { std::cout << x << ", "; }
//    std::cout << "]" << std::endl;
//}
        } // while ( random_choice.size() < 6 ) {}

        std::cout << "random choice size = " << random_choice->size() << std::endl;
        result_random_choice.push_back( random_choice );

        //std::cout << "\n\nresult total: " << result_random_choice.size() << std::endl;
        //for ( auto x: result_random_choice ) for ( auto y: x ) std::cout << y << ", ";
        //std::cout << std::endl;
        //std::cout << "---" << std::endl;

        //std::cout << "list len = " << result_odd_even_3_3_flatten.size() << ", [";
        //for ( auto x: result_odd_even_3_3_flatten ) { std::cout << x << ", "; }
        //std::cout << "]" << std::endl;

        //std::cout << "\n\n" << std::endl;
    } // while ( result_random_choice.size() < 5 ) {}

    const int BUF_LEN = 12 + 5 + 10 + 1; // 12 (numbers: 2*6), 5 (','), 10 ('  ': 2*5)
    const int BUF_DESC_LEN = 100;

    // for display last game (number of games: no.1 ~ present)
    {
        char* buf_last_game = new char[BUF_DESC_LEN];
        snprintf( buf_last_game, BUF_DESC_LEN, "%s", LAST_GAME );
        ret_result->push_back( buf_last_game );
    }

#ifdef ENABLE_LOG
    std::cout << "------------------------------" << std::endl;
    std::cout << "result:" << std::endl;
#endif
    //for ( auto x: result_random_choice ) std::cout << x << ", ";
    //std::cout << std::endl;
    for ( int i; i < result_random_choice.size(); i++ ) {
#ifdef ENABLE_LOG
        std::cout << i << ", [";
#endif
        //for ( auto x: *result_random_choice[i] )
        auto x = *result_random_choice[i];
        {
#ifdef ENABLE_LOG
            //std::cout << x << ", ";
            std::cout
                << x[0] << ", " << x[1] << ", " << x[2] << ", "
                << x[3] << ", " << x[4] << ", " << x[5];
#endif

            char* buf = new char[BUF_LEN];
            snprintf( buf, BUF_LEN, "%02d,  %02d,  %02d,  %02d,  %02d,  %02d",
                        (int)x[0], (int)x[1], (int)x[2], (int)x[3], (int)x[4], (int)x[5] );
            ret_result->push_back( buf );
        }
#ifdef ENABLE_LOG
        std::cout << "]" << std::endl;
#endif
        delete result_random_choice[i];
    }
#ifdef ENABLE_LOG
    std::cout << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;
#endif
    result_random_choice.clear();

    return 0;
}

//std::vector<int*>*& result_matched_total
void comparison(std::vector<char*>*& ret_result, std::vector<float*>*& in) {
    int test_start_from = 0;
    int result_matched_total_1 = 0;
    int result_matched_total_2 = 0;
    int result_matched_total_3 = 0;
    int result_matched_total_4 = 0;
    int result_matched_total_5 = 0;
    int result_matched_total_6 = 0;

    std::vector<int*> result_matched_total;
    const int winning_numbers_with_bonus_size_per_game = 6+1; // 1, 2, 3, 4, 5, 6, bonus

    for ( auto x: results_winning_numbers ) {
        //std::cout << "(win) " << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << ", "
        //          << x[4] << ", " << x[5] << ", " << x[6] << ", " << x[7] << std::endl;

        for ( auto y: *in ) {
            int matched_count = 0;
            //std::cout << "(gen) " << y[0] << ", " << y[1] << ", " << y[2] << ", " << y[3] << ", "
            //          << y[4] << ", " << y[5] << std::endl;

            for ( int y_one = 0; y_one < 6; y_one++ ) {
                for ( int z = 0; z < winning_numbers_with_bonus_size_per_game; z++ ) {
                    // x: (1+7) => (no., 1,2,3,4,5,6,bonus)
                    // y: (6)
                    if ( (int)x[z+1] == (int)y[y_one] ) {
                        matched_count += 1;
                        //std::cout << "matched: " << ", " << z << std::endl;
                    }
                }
            }

            switch ( matched_count ) {
                case 1: result_matched_total_1 += 1; break;
                case 2: result_matched_total_2 += 1; break;
                case 3: result_matched_total_3 += 1; break;
                case 4: result_matched_total_4 += 1; break;
                case 5: result_matched_total_5 += 1; break;
                case 6: result_matched_total_6 += 1; break;
            }

            if ( matched_count > 3 ) {
                //std::cout << "(matched: " << matched_count << ")"
                //    << ", no.: " << x[0] << " ==> "
                //    << x[1] << ", " << x[2] << ", " << x[3] << ", " << x[4] << ", "
                //    << x[5] << ", " << x[6] << ", " << x[7]
                //    << << std::endl;


                const int elem_size = 1+1+7; // matched count, no., 1,2,3,4,5,6,bonus
                int* elem = new int[elem_size];

                //memcpy( elem, (int*)x, elem_size );

                elem[0] = matched_count; // matched count
                elem[1] = x[0]; // no.
                elem[2] = x[1]; // 1
                elem[3] = x[2]; // 2
                elem[4] = x[3]; // 3
                elem[5] = x[4]; // 4
                elem[6] = x[5]; // 5
                elem[7] = x[6]; // 6
                elem[8] = x[7]; // bonus

                result_matched_total.push_back( elem );
            }
        }
    }

    //std::cout << "------------------------------" << std::endl;
    //std::cout << "[comparison]" << std::endl;
    //std::cout << "matched total from 1 to last game result" << std::endl;
    //std::cout << "matched total 1: " << result_matched_total_1 << std::endl;
    //std::cout << "matched total 2: " << result_matched_total_2 << std::endl;
    //std::cout << "matched total 3: " << result_matched_total_3 << std::endl;
    //std::cout << "matched total 4: " << result_matched_total_4 << std::endl;
    //std::cout << "matched total 5: " << result_matched_total_5 << std::endl;
    //std::cout << "matched total 6: " << result_matched_total_6 << std::endl;
    //std::cout << std::endl;


    // sort
    //auto func_sort = [](auto src1, auto src2) -> bool { return (int)src1[0] < (int)src2[0]; }; // asc
    auto func_sort = [](auto src1, auto src2) -> bool { return (int)src1[0] > (int)src2[0]; }; // desc
    std::sort( result_matched_total.begin(), result_matched_total.end(), func_sort );

    {
        // add matched total counts...
        const int elem_size = 1+1+7;
        int* elem = new int[elem_size];

        elem[0] = result_matched_total_1;
        elem[1] = result_matched_total_2;
        elem[2] = result_matched_total_3;
        elem[3] = result_matched_total_4;
        elem[4] = result_matched_total_5;
        elem[5] = result_matched_total_6;
        elem[6] = 0;
        elem[7] = 0;
        elem[8] = 0;

        // result_matched_total[0]: matched total counts info
        //result_matched_total.push_back( elem );
        auto it = result_matched_total.begin();
        it = result_matched_total.insert( it, elem );
    }

    /*
    std::cout << "result:" << std::endl;
    for ( auto x: result_matched_total ) {
        //if ( *(result_matched_total)->begin() == x ) {
        if ( result_matched_total.begin() == x ) {
            std::cout << "[comparison]" << std::endl;
            std::cout << "matched total from 1 to last game result" << std::endl;
            std::cout << "matched total 1: " << x[0] << std::endl;
            std::cout << "matched total 2: " << x[1] << std::endl;
            std::cout << "matched total 3: " << x[2] << std::endl;
            std::cout << "matched total 4: " << x[3] << std::endl;
            std::cout << "matched total 5: " << x[4] << std::endl;
            std::cout << "matched total 6: " << x[5] << std::endl;
            continue;
        }
        std::cout << "(matched: " << x[0] << ")"
            << ", no.: " << x[1] << " ==> "
            << x[2] << ", " << x[3] << ", " << x[4] << ", " << x[5] << ", "
            << x[6] << ", " << x[7] << ", " << x[8] << std::endl;
    }
    */
    //std::cout << "------------------------------" << std::endl;



    // scores info only
    //const int BUF_LEN = 40 + 12 + 6 + 12 + 1; // 40 ((matched: %d), no.: %d => ), 12 (numbers: 2*6), 6 (','), 12 ('  ': 2*6)
    const int BUF_LEN_SCORES = 256;
    //const int BUF_DESC_LEN = 100;
    int prev_count = -1;

    // for display last game (number of games: no.1 ~ present)
    //{
    //    if ( ret_result != NULL ) {
    //        char* buf_last_game = new char[BUF_DESC_LEN];
    //        snprintf( buf_last_game, BUF_DESC_LEN, "%s", LAST_GAME );
    //        ret_result->push_back( buf_last_game );
    //    }
    //}

#ifdef ENABLE_LOG
    std::cout << "------------------------------" << std::endl;
    std::cout << "result:" << std::endl;
#endif
    for ( auto x: result_matched_total ) {
        //if ( *(result_matched_total)->begin() == x ) {
        if ( *(result_matched_total.begin()) == x ) {
#ifdef ENABLE_LOG
            std::cout << "[comparison]" << std::endl;
            std::cout << "matched total from 1 to last game result" << std::endl;
            std::cout << "matched total 1: " << x[0] << std::endl;
            std::cout << "matched total 2: " << x[1] << std::endl;
            std::cout << "matched total 3: " << x[2] << std::endl;
            std::cout << "matched total 4: " << x[3] << std::endl;
            std::cout << "matched total 5: " << x[4] << std::endl;
            std::cout << "matched total 6: " << x[5] << std::endl;
#endif
            char* buf = new char[BUF_LEN_SCORES];
            snprintf( buf, BUF_LEN_SCORES,
                "[scores]\n" \
                "%s 비교\n" \
                "1개 일치: %d\n" \
                "2개 일치: %d\n" \
                "3개 일치: %d\n" \
                "4개 일치: %d\n" \
                "5개 일치: %d\n" \
                "6개 일치: %d\n", LAST_GAME, x[0], x[1], x[2], x[3], x[4], x[5] );
            ret_result->push_back( buf );

            char* buf1 = new char[BUF_LEN_SCORES];
            snprintf( buf1, BUF_LEN_SCORES, "일치개수 | 회차 | 당첨번호 1~6, bonus" );
            ret_result->push_back( buf1 );

            continue;
        }
#ifdef ENABLE_LOG
        std::cout << "(matched: " << x[0] << ")"
            << ", no.: " << x[1] << " ==> "
            << "[" << << x[2] << ", " << x[3] << ", " << x[4] << ", " << x[5] << ", "
            << x[6] << ", " << x[7] << ", " << x[8] << "]" << std::endl;
#endif

        if ( ret_result != NULL ) {
            char* buf_delim = new char[BUF_LEN_SCORES];
            char* buf = new char[BUF_LEN_SCORES];

            if ( prev_count >= 0 && prev_count != (int)x[0] ) {
                snprintf( buf_delim, BUF_LEN_SCORES, "-----" );
                ret_result->push_back( buf_delim );
            }
            prev_count = (int)x[0];

            // "일치개수 | 회차 | 당첨번호 1~6, bonus"
            snprintf( buf, BUF_LEN_SCORES,
                        "(%d), %d\n" \
                        "  => [%02d,  %02d,  %02d,  %02d,  %02d,  %02d,  %02d]",
                        (int)x[0], (int)x[1], (int)x[2], (int)x[3], (int)x[4],
                        (int)x[5], (int)x[6], (int)x[7], (int)x[8] );
            ret_result->push_back( buf );
        }
    }
#ifdef ENABLE_LOG
    std::cout << "------------------------------" << std::endl;
#endif



    for ( auto x: result_matched_total ) {
        int* _x = x;
        delete[] x;
    }
    result_matched_total.clear();


    {
        std::cout << "release allocated... [" << std::endl;
        std::vector<float*>::iterator iter;
        for ( iter = in->begin(); iter != in->end(); ++iter ) {
            float* numbers = (*iter);
            delete numbers;
            numbers = NULL;
        }
        in->clear();
        delete in;
        in = NULL;
        std::cout << "release allocated... ]" << std::endl;
    }
}


/*
int main(int argc, char* argv[]) {
    {
        std::vector<float*>* result = NULL;
        odd_even( result );
        std::cout << "\n\n" << std::endl;
    }

    {
        std::vector<float*>* result = new std::vector<float*>;

        odd_even( result );
        std::cout << "\n\n" << std::endl;
        method3( result );
        std::cout << "\n\n" << std::endl;


        //std::cout << "release allocated... [" << std::endl;
        //std::vector<float*>::iterator iter;
        //for ( iter = result->begin(); iter != result->end(); ++iter ) {
        //    float* numbers = (*iter);
        //    delete numbers;
        //    numbers = NULL;
        //}
        //result->clear();
        //delete result;
        //result = NULL;
        //std::cout << "release allocated... ]" << std::endl;
    }

    {
        std::vector<float*>* result = new std::vector<float*>;
        odd_even( result );
        std::cout << "\n\n" << std::endl;

        std::vector<int*>* result2 = new std::vector<int*>;
        comparison( result, result2 );
        std::cout << "\n\n" << std::endl;


        std::cout << "------------------------------" << std::endl;
        std::cout << "[comparison]" << std::endl;
        std::cout << "result:" << std::endl;
        for ( auto x: *result2 ) {
            if ( *(result2)->begin() == x ) {
                std::cout << "[comparison]" << std::endl;
                std::cout << "matched total from 1 to last game result" << std::endl;
                std::cout << "matched total 1: " << x[0] << std::endl;
                std::cout << "matched total 2: " << x[1] << std::endl;
                std::cout << "matched total 3: " << x[2] << std::endl;
                std::cout << "matched total 4: " << x[3] << std::endl;
                std::cout << "matched total 5: " << x[4] << std::endl;
                std::cout << "matched total 6: " << x[5] << std::endl;
                continue;
            }
            std::cout << "(matched: " << x[0] << ")"
                << ", no.: " << x[1] << " ==> "
                << x[2] << ", " << x[3] << ", " << x[4] << ", " << x[5] << ", "
                << x[6] << ", " << x[7] << ", " << x[8] << std::endl;
        }
        std::cout << "------------------------------" << std::endl;


        std::cout << "release allocated... [" << std::endl;
        std::vector<float*>::iterator iter;
        for ( iter = result->begin(); iter != result->end(); ++iter ) {
            float* numbers = (*iter);
            delete[] numbers;
            numbers = NULL;
        }
        result->clear();
        delete result;
        result = NULL;
        std::cout << "release allocated... ]" << std::endl;

        // ----------

        std::cout << "release allocated... [" << std::endl;
        //std::vector<int*>::iterator iter2;
        //for ( iter2 = result2->begin(); iter2 != result2->end(); ++iter2 ) {
        //    int* val = (*iter2);
        //    delete[] val;
        //    val = NULL;
        //}
        //result2->clear();
        //delete result2;
        //result2 = NULL;
        for ( auto x: *result2 ) {
            int* _x = x;
            delete[] x;
        }
        result2->clear();
        std::cout << "release allocated... ]" << std::endl;

    }

    return 0;
}
*/

