package com.atflab.android.lottery_prediction.ui.home;

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

import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.text.Html;
import android.text.InputType;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.atflab.android.lottery_prediction.App;
import com.atflab.android.lottery_prediction.R;
import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;

public class HomeFragment extends Fragment {
    private static final String TAG = "HomeFragment";

    private HomeViewModel homeViewModel;


    // JNI
    //static { System.loadLibrary("lottery_prediction"); }
    private native String[] get_native_ml_module(int algorithm, int generate, int total_games);
    private native int get_native_max_algorithm();
    private int MAX_ALGORITHM = 4;

    // Donation URL
    private final String DONATION_URL = "https://github.com/godmode2k/godmode2k";

    private TextView m_textview_result = null;

    private Boolean m_cancel_process = false;
    private ProgressDialog m_progress_dialog = null;

    private ArrayList<int[]> m_generated_numbers = new ArrayList<int[]>();
    private int m_this_weekly_winning_numbers[] = new int[7];

    private EditText m_edittext_winning_num1 = null;
    private EditText m_edittext_winning_num2 = null;
    private EditText m_edittext_winning_num3 = null;
    private EditText m_edittext_winning_num4 = null;
    private EditText m_edittext_winning_num5 = null;
    private EditText m_edittext_winning_num6 = null;
    private EditText m_edittext_winning_num7_b = null;

    private App m_main_app = null;


    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        /*
        homeViewModel =
                ViewModelProviders.of(this).get(HomeViewModel.class);
        View root = inflater.inflate(R.layout.fragment_home, container, false);
        final TextView textView = root.findViewById(R.id.text_home);
        homeViewModel.getText().observe(this, new Observer<String>() {
            @Override
            public void onChanged(@Nullable String s) {
                textView.setText(s);
            }
        });

        return root;
        */

        // Prevent soft-keyboard slide-out
        this.getActivity().getWindow().setSoftInputMode (WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN );
        m_main_app = (App)this.getActivity().getApplicationContext();

        View root = inflater.inflate(R.layout.fragment_home, container, false);

        {
            // JNI
            load_jni( this.getActivity().getApplicationContext() );
            //int generate = 300;
            //get_native_ml_module( generate );
            //List<String> result = new ArrayList( Arrays.asList(get_native_ml_module(generate)) );
            //for ( int i = 0; i < result.size(); i++ ) {
            //    Log.d( TAG, "[" + i + "] " + result.get(i).toString() );
            //}

            String res = m_main_app.get_current_updates_info();
            if ( res == null ) {
                res = "...";
            }
            // updates.txt: 1,2024.07.26
            TextView tv = (TextView)root.findViewById(R.id.TextView_update_status);
            if ( tv != null ) {
                tv.setText( res );
            }

            MAX_ALGORITHM = call_get_native_max_algorithm();
        }

        final EditText edittext_algorithm = (EditText)root.findViewById(R.id.EditText_algorithm);
        Button button_algorithm = (Button)root.findViewById(R.id.Button_algorithm);
        final EditText edittext_generate = (EditText)root.findViewById(R.id.EditText_generate);
        final EditText editText_total_games = (EditText)root.findViewById(R.id.EditText_total_games);
        //final TextView textview_result = (TextView)root.findViewById(R.id.TextView_result);
        Button button_generate = (Button)root.findViewById(R.id.Button_generate);

        m_textview_result = (TextView)root.findViewById(R.id.TextView_result);

        m_edittext_winning_num1 = (EditText)root.findViewById(R.id.EditText_winning_num1);
        m_edittext_winning_num2 = (EditText)root.findViewById(R.id.EditText_winning_num2);
        m_edittext_winning_num3 = (EditText)root.findViewById(R.id.EditText_winning_num3);
        m_edittext_winning_num4 = (EditText)root.findViewById(R.id.EditText_winning_num4);
        m_edittext_winning_num5 = (EditText)root.findViewById(R.id.EditText_winning_num5);
        m_edittext_winning_num6 = (EditText)root.findViewById(R.id.EditText_winning_num6);
        m_edittext_winning_num7_b = (EditText)root.findViewById(R.id.EditText_winning_num7_bonus);
        final Button button_checks_numbers = (Button)root.findViewById(R.id.Button_checks_numbers);
        Button button_checks_numbers_clear = (Button)root.findViewById(R.id.Button_checks_numbers_clear);
        Button button_checks_update = (Button)root.findViewById(R.id.Button_checks_update);

        Arrays.fill( m_this_weekly_winning_numbers, -1 );

        Button button_donation_link = (Button)root.findViewById(R.id.Button_donation_link);

        if ( edittext_algorithm != null ) {
            final String _val = "  /  " + MAX_ALGORITHM;
            String val = "1" + _val;
            edittext_algorithm.setText( val );
        }

        // load history generated
        m_main_app.load_history( false, m_textview_result, m_generated_numbers );



        if ( button_algorithm != null ) {
            button_algorithm.setOnClickListener(new View.OnClickListener() {
                final String _val = "  /  " + MAX_ALGORITHM;
                @Override
                public void onClick(View view) {
                    //int algorithm = Integer.parseInt( edittext_algorithm.getText().toString() );
                    int algorithm = Integer.parseInt( edittext_algorithm.getText().toString().split("/")[0].trim() );
                    if ( algorithm+1 > MAX_ALGORITHM ) {
                        String val = "1" + _val;
                        edittext_algorithm.setText( val );

                        edittext_generate.setEnabled( true );
                        editText_total_games.setEnabled( true );
                    }
                    else {
                        String val = (algorithm + 1) + _val;
                        edittext_algorithm.setText( val );
                        edittext_generate.setEnabled( false );
                        editText_total_games.setEnabled( false );
                    }
                }
            });
        }

        if ( button_generate != null ) {
            button_generate.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    //View view = getActivity().getCurrentFocus();
                    if (view != null) {
                        InputMethodManager imm = (InputMethodManager)getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                    }

                    if ( button_checks_numbers != null ) {
                        button_checks_numbers.setEnabled( true );
                    }


                    // JNI
                    //int generate = 300;
                    //get_native_ml_module( generate );

                    //int algorithm = Integer.parseInt( edittext_algorithm.getText().toString() );
                    int algorithm = Integer.parseInt( edittext_algorithm.getText().toString().split("/")[0].trim() );
                    int generate = Integer.parseInt( edittext_generate.getText().toString() );
                    int total_games = Integer.parseInt( editText_total_games.getText().toString() );

                    /*
                    String result = "";
                    List<String> list_result = new ArrayList( Arrays.asList(get_native_ml_module(generate, total_games)) );
                    for ( int i = 0; i < list_result.size(); i++ ) {
                        if ( i == 0 ) {
                            result += "게임 범위: " + list_result.get(i).toString() + "\n\n";
                            continue;
                        }
                        //Log.d( TAG, "[" + i + "] " + list_result.get(i).toString() );

                        if ( (i % 5) == 1) {
                            result += "(" + (i + 4) + " / " + (list_result.size() - 1) + ")" + "\n";
                        }
                        if ( i > 5 ) {
                            result += "[" + (((i % 5) == 0) ? 5 : (i % 5)) + "] " + list_result.get(i).toString() + "\n";
                        }
                        else {
                            result += "[" + i + "] " + list_result.get(i).toString() + "\n";
                        }

                        if ( (i % 5) == 0 ) result += "\n";
                    }
                    Log.d( TAG, result );

                    m_textview_result.setText( result );
                    */

                    call_get_native_ml_module( algorithm, generate, total_games, m_textview_result );
                }
            });
        }

        if ( button_checks_numbers != null ) {
            button_checks_numbers.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if (view != null) {
                        InputMethodManager imm = (InputMethodManager)getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                    }

                    if ( button_checks_numbers != null ) {
                        button_checks_numbers.setEnabled( false );
                    }

                    if ( m_edittext_winning_num1 != null &&
                            m_edittext_winning_num2 != null &&
                            m_edittext_winning_num3 != null &&
                            m_edittext_winning_num4 != null &&
                            m_edittext_winning_num5 != null &&
                            m_edittext_winning_num6 != null &&
                            m_edittext_winning_num7_b!= null ) {
                        if ( m_edittext_winning_num1.getText().toString().isEmpty() ||
                                m_edittext_winning_num2.getText().toString().isEmpty() ||
                                m_edittext_winning_num3.getText().toString().isEmpty() ||
                                m_edittext_winning_num4.getText().toString().isEmpty() ||
                                m_edittext_winning_num5.getText().toString().isEmpty() ||
                                m_edittext_winning_num6.getText().toString().isEmpty() ||
                                m_edittext_winning_num7_b.getText().toString().isEmpty() ) {
                            Log.d( TAG, "[Error] Empty winning numbers..." );
                            button_checks_numbers.setEnabled( true );
                            Toast.makeText(m_main_app,
                                    //"당첨번호 확인에 번호가 없습니다.\n[제발!] 버튼을 눌러서 번호를 먼저 생성해 주세요.", Toast.LENGTH_SHORT).show();
                                    "당첨번호 확인에 번호가 없습니다. 가져오는 중.. 한 번 더 눌러주세요.", Toast.LENGTH_SHORT).show();

                            // get this weekly winning numbers if an empty.
                            new Thread(
                                    () -> {
                                        Log.d(TAG, "fetching winning numbers...");
                                        get_this_weekly_winning_numbers();
                                    })
                                    .start();
                            return;
                        }
                        int n1 = Integer.parseInt(m_edittext_winning_num1.getText().toString());
                        int n2 = Integer.parseInt(m_edittext_winning_num2.getText().toString());
                        int n3 = Integer.parseInt(m_edittext_winning_num3.getText().toString());
                        int n4 = Integer.parseInt(m_edittext_winning_num4.getText().toString());
                        int n5 = Integer.parseInt(m_edittext_winning_num5.getText().toString());
                        int n6 = Integer.parseInt(m_edittext_winning_num6.getText().toString());
                        int n7_b = Integer.parseInt(m_edittext_winning_num7_b.getText().toString());

                        int result_matched_total_1 = 0;
                        int result_matched_total_2 = 0;
                        int result_matched_total_3 = 0;
                        int result_matched_total_4 = 0;
                        int result_matched_total_5 = 0;
                        int result_matched_total_6 = 0;
                        int result_matched_total_7 = 0; // bonus

                        int winning_numbers[] = new int[7];
                        winning_numbers[0] = n1;
                        winning_numbers[1] = n2;
                        winning_numbers[2] = n3;
                        winning_numbers[3] = n4;
                        winning_numbers[4] = n5;
                        winning_numbers[5] = n6;
                        winning_numbers[6] = n7_b;

                        String res_str = "\n--------------------\n\n[당첨번호와 비교]\n";
                        ArrayList<String[]> res_str_numbers = new ArrayList<String[]>();

                        for ( int val_arr[]: m_generated_numbers ) {
                            int matched_count = 0;
                            int val_arr_i = 0;
                            int val_arr_pos[] = { 0, 0, 0, 0, 0, 0 };

                            for ( int val: val_arr ) {
                                for( int wnum: winning_numbers ) {
                                    if ( val == wnum ) {
                                        // bonus
                                        if ( val == winning_numbers[6] ) {
                                            result_matched_total_7 += 1;
                                            val_arr_pos[val_arr_i] = 1;
                                            continue;
                                        }

                                        matched_count += 1;
                                        val_arr_pos[val_arr_i] = 1;
                                    }
                                }
                                val_arr_i++;
                            }

                            if ( matched_count == 1 ) result_matched_total_1 += 1;
                            else if ( matched_count == 2 ) result_matched_total_2 += 1;
                            else if ( matched_count == 3 ) result_matched_total_3 += 1;
                            else if ( matched_count == 4 ) result_matched_total_4 += 1;
                            else if ( matched_count == 5 ) result_matched_total_5 += 1;
                            else if ( matched_count == 6 ) result_matched_total_6 += 1;

                            if ( matched_count > 0 ) {
                                //int res[] = {
                                //    matched_count,
                                //    val_arr[0],
                                //    val_arr[1],
                                //    val_arr[2],
                                //    val_arr[3],
                                //    val_arr[4],
                                //    val_arr[5]
                                //};

                                String str_numbers[] = {
                                    String.format( "%d", matched_count ),
                                    ((val_arr_pos[0] > 0) ? ((val_arr[0] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[0] > 9) ? val_arr[0] : "0" + val_arr[0]) ) + ((val_arr_pos[0] > 0) ? "</b>" : ""),
                                    ((val_arr_pos[1] > 0) ? ((val_arr[1] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[1] > 9) ? val_arr[1] : "0" + val_arr[1]) ) + ((val_arr_pos[1] > 0) ? "</b>" : ""),
                                    ((val_arr_pos[2] > 0) ? ((val_arr[2] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[2] > 9) ? val_arr[2] : "0" + val_arr[2]) ) + ((val_arr_pos[2] > 0) ? "</b>" : ""),
                                    ((val_arr_pos[3] > 0) ? ((val_arr[3] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[3] > 9) ? val_arr[3] : "0" + val_arr[3]) ) + ((val_arr_pos[3] > 0) ? "</b>" : ""),
                                    ((val_arr_pos[4] > 0) ? ((val_arr[4] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[4] > 9) ? val_arr[4] : "0" + val_arr[4]) ) + ((val_arr_pos[4] > 0) ? "</b>" : ""),
                                    ((val_arr_pos[5] > 0) ? ((val_arr[5] != n7_b) ? "<b> <font color='red'>" : "<b> <font color='blue'>") : "") + String.format( "%s", ((val_arr[5] > 9) ? val_arr[5] : "0" + val_arr[5]) ) + ((val_arr_pos[5] > 0) ? "</b>" : "")
                                };
                                res_str_numbers.add( str_numbers );
                            }
                            else {
                                String str_numbers[] = {
                                    String.format( "%d", matched_count ),
                                    String.format( "<del>%s</del>", ((val_arr[0] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[0] > 9) ? val_arr[0] : "0" + val_arr[0]) ),
                                    String.format( "<del>%s</del>", ((val_arr[1] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[1] > 9) ? val_arr[1] : "0" + val_arr[1]) ),
                                    String.format( "<del>%s</del>", ((val_arr[2] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[2] > 9) ? val_arr[2] : "0" + val_arr[2]) ),
                                    String.format( "<del>%s</del>", ((val_arr[3] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[3] > 9) ? val_arr[3] : "0" + val_arr[3]) ),
                                    String.format( "<del>%s</del>", ((val_arr[4] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[4] > 9) ? val_arr[4] : "0" + val_arr[4]) ),
                                    String.format( "<del>%s</del>", ((val_arr[5] == n7_b) ? "<b> <font color='blue'>" : "") + ((val_arr[5] > 9) ? val_arr[5] : "0" + val_arr[5]) )
                                };
                                res_str_numbers.add( str_numbers );
                            }
                        }

                        res_str += "1개 일치: " + ((result_matched_total_1 >= 0) ? result_matched_total_1 : 0) + "\n";
                        res_str += "2개 일치: " + ((result_matched_total_2 >= 0) ? result_matched_total_2 : 0) + "\n";
                        res_str += "3개 일치: " + ((result_matched_total_3 >= 0) ? result_matched_total_3 : 0) + "\n";
                        res_str += "4개 일치: " + ((result_matched_total_4 >= 0) ? result_matched_total_4 : 0) + "\n";
                        res_str += "5개 일치: " + ((result_matched_total_5 >= 0) ? result_matched_total_5 : 0) + "\n";
                        res_str += "6개 일치: " + ((result_matched_total_6 >= 0) ? result_matched_total_6 : 0) + "\n";
                        res_str += "보너스 일치: " + result_matched_total_7 + "\n\n";
                        res_str += "일치 개수 (보너스 제외) => 예측 번호" + "\n";

                        Collections.sort(res_str_numbers, new Comparator<String[]>() {
                            @Override
                            public int compare(String[] strings, String[] t1) {
                                //return strings[0].compareTo(t1[0]); // ASC
                                return t1[0].compareTo(strings[0]); // DESC
                            }
                        });

                        for ( String val_arr[]: res_str_numbers ) {
                            res_str += "(" + val_arr[0] + ") => [ ";
                            res_str += val_arr[1] + ", " ;
                            res_str += val_arr[2] + ", " ;
                            res_str += val_arr[3] + ", " ;
                            res_str += val_arr[4] + ", " ;
                            res_str += val_arr[5] + ", " ;
                            res_str += val_arr[6];
                            res_str += " ]\n";
                        }
                        m_textview_result.append( Html.fromHtml(res_str.replace("\n", "<br>")) );

                        Toast.makeText(m_main_app,
                                "[완료] 내용이 추가되었습니다.", Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }

        if ( button_checks_numbers_clear != null ) {
            button_checks_numbers_clear.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if ( m_this_weekly_winning_numbers == null ) {
                        Log.d( TAG, "this_weekly_winning_numbers == NULL" );
                        return;
                    }
                    Arrays.fill( m_this_weekly_winning_numbers, -1 );

                    if ( m_edittext_winning_num1 != null &&
                            m_edittext_winning_num2 != null &&
                            m_edittext_winning_num3 != null &&
                            m_edittext_winning_num4 != null &&
                            m_edittext_winning_num5 != null &&
                            m_edittext_winning_num6 != null &&
                            m_edittext_winning_num7_b!= null ) {
                        m_edittext_winning_num1.setText("");
                        m_edittext_winning_num2.setText("");
                        m_edittext_winning_num3.setText("");
                        m_edittext_winning_num4.setText("");
                        m_edittext_winning_num5.setText("");
                        m_edittext_winning_num6.setText("");
                        m_edittext_winning_num7_b.setText("");
                    }
                }
            });
        }

        if ( button_checks_update != null ) {
            button_checks_update.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    m_main_app.updates( getActivity() );
                }
            });
        }

        if ( button_donation_link != null ) {
            button_donation_link.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    // Donation URL
                    Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(DONATION_URL));
                    startActivity( intent );
                }
            });
        }

        return root;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    @Override
    public void onPause() {
        super.onPause();

        //if ( m_main_app != null && m_textview_result != null ) {
        //    m_main_app.set_str_result( m_textview_result.getText().toString() );
        //}
    }

    @Override
    public void onResume() {
        super.onResume();

        // reload result
        //if ( m_main_app != null && m_textview_result != null ) {
        //    m_textview_result.setText(m_main_app.get_str_result());
        //}
    }


    // JNI
    private static void load_jni(Context context) {
        //System.loadLibrary("lottery_prediction");

        // /data/
        String path_base_internal = Environment.getDataDirectory().getPath();
        // /storage/emulated/0/
        String path_base_external = Environment.getExternalStorageDirectory().getPath();

        // base path: /data/media/0/Download/
        //String path_base = path_base_internal + "/media/0/Download";
        // base path: /storage/emulated/0/Download
        String path_base_download = path_base_external + "/Download";

        // app base path: /data/data/<package>/files/
        String app_path_base = context.getFilesDir().getAbsolutePath();

        String ml_so_name = "lottery_prediction";
        String ml_so = "liblottery_prediction.so";
        String ml_so_app_full_pathname = app_path_base + "/" + ml_so;
        String ml_so_download_full_pathname = path_base_download + "/" + ml_so;

        FileOutputStream outputStream;
        FileInputStream inputStream;

        Log.d(TAG, "internal path = " + path_base_internal);
        Log.d(TAG, "app full path filename = " + ml_so_app_full_pathname);
        Log.d(TAG, "external path = " + path_base_external);
        Log.d(TAG, "download full path filename = " + ml_so_download_full_pathname);


        //try {
        //    // /data/data/<package>/files/liblottery_prediction.so
        //    if ((new File(ml_so_app_full_pathname).exists())) {
        //        if ((new File(ml_so_app_full_pathname)).delete()) {
        //            Log.d(TAG, "deleted directory: " + ml_so_app_full_pathname);
        //        } else {
        //            Log.d(TAG, "[Error] deleted directory: " + ml_so_app_full_pathname);
        //        }
        //    }
        //} catch (Exception e_all) {
        //    e_all.printStackTrace();
        //}

        //! FIXME:
        // FIX or DELETE
        // SEE: App.java: download_update_file() -> getFilesDir()
        if ((new File(ml_so_download_full_pathname).exists())) {
            try {
                // /data/data/<package>/files/liblottery_prediction.so
                if ((new File(ml_so_app_full_pathname).exists())) {
                    if ((new File(ml_so_app_full_pathname)).delete()) {
                        Log.d(TAG, "deleted directory: " + ml_so_app_full_pathname);
                    } else {
                        Log.d(TAG, "[Error] deleted directory: " + ml_so_app_full_pathname);
                    }
                }

                // /Download/liblottery_prediction.so
                inputStream = new FileInputStream(new File(ml_so_download_full_pathname));
                outputStream = new FileOutputStream(new File(ml_so_app_full_pathname));
                //openFileOutput(ml_so, Context.MODE_PRIVATE);

                FileChannel inChannel = inputStream.getChannel();
                FileChannel outChannel = outputStream.getChannel();
                inChannel.transferTo(0, inChannel.size(), outChannel);
                inputStream.close();
                outputStream.close();

                Log.d( TAG,"load ML module: copied .so file from downloaded (external-storage:/Download/) to internal (" + ml_so_app_full_pathname + ")" );


                //if ((new File(ml_so_download_full_pathname)).delete()) {
                //    Log.d(TAG, "deleted Downloaded: " + ml_so_download_full_pathname);
                //} else {
                //    Log.d(TAG, "[Error] deleted Downloaded: " + ml_so_download_full_pathname);
                //}
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else {
            //
        }

        if (!(new File(ml_so_app_full_pathname).exists())) {
            Log.d( TAG,"load ML module: pre-installed" );
            System.loadLibrary( ml_so_name );
            Log.d( TAG,"load ML module: pre-installed done..." );
        }
        else {
            Log.d( TAG,"load ML module: downloaded (" + ml_so_app_full_pathname +")" );
            // System.load()
            // Risky but, load a .so file (Internal Storage)/Download/lotto645/liblottery_prediction.so
            System.load( ml_so_app_full_pathname );
            Log.d( TAG,"load ML module: downloaded done..." );
        }
    }

    public int call_get_native_max_algorithm() {
        return get_native_max_algorithm();
    }
    public void call_get_native_ml_module(int algorithm, int generate, int total_games, TextView textview_result) {
        //get_native_ml_module( generate, total_games );

        JNITask task = new JNITask();

        m_progress_dialog = new ProgressDialog( getActivity() );
        if ( m_progress_dialog == null ) {
            Log.d( TAG, "call_get_native_ml_module(): ProgressDialog == NULL" );
            return;
        }

        m_progress_dialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        m_progress_dialog.setMessage("번호 생성 중...\n\n('반복 생성', '게임 수'가 크면 시간이 좀 더 소요됩니다.)");
        m_progress_dialog.setCancelable(true);
        m_progress_dialog.setOnCancelListener(new DialogInterface.OnCancelListener() {
            @Override
            public void onCancel(DialogInterface dialog) {
                m_cancel_process = true;
            }
        });
        m_progress_dialog.show();

        if ( task == null ) {
            Log.d( TAG, "call_get_native_ml_module(): JNITask == NULL" );
            m_progress_dialog.dismiss();
            return;
        }

        //Toast.makeText(this.getActivity(),
        //        "[네트워크] 당첨번호를 가져옵니다.\n"
        //                + "[+] 수동으로 입력해도 됩니다.\n"
        //                + "[+] 초기화된 경우에만 동작합니다.",
        //        Toast.LENGTH_SHORT).show();

        task.execute( algorithm, generate, total_games, textview_result );
    }

    public class JNITask extends AsyncTask<Object, Object, Object> {
        private TextView m_textview_result = null;
        private String m_datetime = null;
        private String m_datetime_num = null;
        private int m_algorithm = 0;

        @Override
        protected Object doInBackground(Object... objects) {
            //return null;

            final int algorithm = (Integer)objects[0];
            final int generate = (Integer)objects[1];
            final int total_games = (Integer)objects[2];

            m_textview_result = (TextView)objects[3];
            m_algorithm = algorithm;


            // SEE: button_checks_numbers.setOnClickListener()
            //get_this_weekly_winning_numbers();


            {
                java.util.TimeZone tz;
                java.text.SimpleDateFormat df = new java.text.SimpleDateFormat(
                        "yyyy-MM-dd (E) a hh:mm:ss", Locale.KOREAN);
                tz = java.util.TimeZone.getTimeZone( "Asia/Seoul" );
                df.setTimeZone( tz );
                java.util.Date date = new java.util.Date();

                m_datetime = "[번호 생성]\n날짜: " + df.format(date) + "\n";
                m_datetime += "알고리즘: " + m_algorithm + "\n\n";
            }
            {
                // history generated
                // file path: /Download/lotto645/generated.json

                // 24 hour format
                java.util.TimeZone tz;
                java.text.SimpleDateFormat df = new java.text.SimpleDateFormat(
                        "yyyyMMddHHmmss", Locale.KOREAN);
                tz = java.util.TimeZone.getTimeZone( "Asia/Seoul" );
                df.setTimeZone( tz );
                java.util.Date date = new java.util.Date();

                // timestamp
                //final String timestamp = String.valueOf( date.getTime() );
                //Log.d( TAG, "timestamp = " + timestamp );
                //Log.d( TAG, "timestamp to DateFormat = " + df.format(timestamp) );

                m_datetime_num = "" + df.format(date);
            }

            m_cancel_process = false;
            return work( algorithm, generate, total_games );
        }

        @Override
        protected void onProgressUpdate(Object... values) {
            super.onProgressUpdate(values);

            String progress = (String)values[0];

            if ( m_progress_dialog != null ) {
                m_progress_dialog.setMessage( progress );
            }
        }

        @Override
        protected void onPostExecute(Object o) {
            //super.onPostExecute(o);

            if ( m_progress_dialog != null ) {
                m_progress_dialog.dismiss();
            }

            String result = "";
            List<String> list_result = (List<String>)o;
            if ( list_result == null ) {
                Log.d( TAG, "onPostExecute(): Error: list_result" );
                return;
            }

            if ( m_generated_numbers != null ) {
                m_generated_numbers.clear();
            }

            boolean flag_scores = false;

            for ( int i = 0; i < list_result.size(); i++ ) {
                if ( m_cancel_process ) {
                    Log.d( TAG, "work(): cancelled" );
                    break;
                }

                if ( i == 0 ) {
                    result += "회차 데이터 사용: " + list_result.get(i).toString() + "\n\n";
                    result += m_datetime;
                    continue;
                }
                //Log.d( TAG, "[" + i + "] " + list_result.get(i).toString() );

                if ( list_result.get(i).toString().contains("[scores]") ) {
                    flag_scores = true;
                    //Log.d( TAG, "======> pos = " + i ); // 6
                }
                if ( flag_scores == true ) {
                    // skip details
                    if ( list_result.get(i).toString().contains("일치개수") ) {
                        // 6개 일치: ...
                        // \n
                        // 일치개수 | 회차 | 당첨번호 1~6, bonus
                        // ...

                        break;
                    }

                    result += list_result.get(i).toString() + "\n";
                    continue;
                }

                if ( (i % 5) == 1) {
                    //result += "(" + (i + 4) + " / " + (list_result.size() - 1) + ")" + "\n";

                    int row_size = (list_result.size() - 1);

                    if ( row_size > 6) { // [0]: info, [1]~[5]: numbers generated
                        if (list_result.get(1+5).toString().contains("[scores]")) {
                            row_size = 5; // algorithm #2 result is 5 rows.
                        }
                    }

                    result += "(" + (i + 4) + " / " + row_size + ")" + "\n";
                }
                if ( i > 5 ) {
                    result += "[" + (((i % 5) == 0) ? 5 : (i % 5)) + "] " + list_result.get(i).toString() + "\n";
                }
                else {
                    result += "[" + i + "] " + list_result.get(i).toString() + "\n";
                }

                String a[] = list_result.get(i).toString().split(",");

                //! TODO: sort (algorithm 1 ~: cpp files)
                /*
                {
                    //Arrays.sort(a);
                    Arrays.sort(a, new Comparator<String>() {
                        @Override
                        public int compare(String s, String t1) {
                            //return 0;
                            int n1 = Integer.parseInt( s.trim() );
                            int n2 = Integer.parseInt( t1.trim() );
                            return Integer.compare( n1, n2 );
                        }
                    });
                }
                */

                //Log.d( TAG, "==> " + list_result.get(i).toString() );
                //Log.d( TAG, "--> " + a[0].trim() + "-" + a[1].trim() + "-" + a[2].trim() + "-" + a[3].trim() + "-" + a[4].trim() + "-" + a[5].trim() + "-" );
                int generated_numbers[] = {
                        Integer.parseInt(a[0].trim()),
                        Integer.parseInt(a[1].trim()),
                        Integer.parseInt(a[2].trim()),
                        Integer.parseInt(a[3].trim()),
                        Integer.parseInt(a[4].trim()),
                        Integer.parseInt(a[5].trim())
                };
                m_generated_numbers.add( generated_numbers );

                if ( (i % 5) == 0 ) result += "\n";
            }
            Log.d( TAG, result );

            if ( m_textview_result != null ) {
                m_textview_result.setText( Html.fromHtml(result.replace("\n", "<br>")) );
            }

            {
                // history generated
                // file path: /Download/lotto645/generated.json
                // {
                //     "generated": [
                //         { "date": "20251022090000", "numbers": [ [0, ], ], "algorithm": 1, "result": "..." }
                //     ]
                // }
                m_main_app.save_history( m_generated_numbers, m_datetime_num, m_algorithm, result );
            }
        }

        public List<String> work(int _algorithm, int _generate, int _total_games) {
            // JNI
            //int generate = 300;
            //get_native_ml_module( generate );

            int algorithm = _algorithm;
            int generate = _generate;
            int total_games = _total_games;

            return new ArrayList( Arrays.asList(get_native_ml_module(algorithm, generate, total_games)) );
        }
    }

    public void get_this_weekly_winning_numbers() {
        // https://dhlottery.co.kr/gameResult.do?method=byWin
        //
        //<!DOCTYPE html>
        //<html lang="ko">
        //<head>
        //<meta charset="EUC-KR">
        //<meta id="utitle" name="title" content="동행복권">
        //<meta id="desc" name="description" content="동행복권 1127회 당첨번호 10,15,24,30,31,37+32. 1등 총 12명, 1인당 당첨금액 2,267,891,969원.">
        //<title>로또6/45 - 회차별 당첨번호</title>
        //<title>동행복권</title>

        if ( !this.m_main_app.network_online() ) {
            return;
        }

        if ( m_this_weekly_winning_numbers == null ) {
            Log.d( TAG, "this_weekly_winning_numbers == NULL" );
            return;
        }
        if ( m_this_weekly_winning_numbers[0] != -1 &&
                m_this_weekly_winning_numbers[1] != -1 &&
                m_this_weekly_winning_numbers[2] != -1 &&
                m_this_weekly_winning_numbers[3] != -1 &&
                m_this_weekly_winning_numbers[4] != -1 &&
                m_this_weekly_winning_numbers[5] != -1 &&
                m_this_weekly_winning_numbers[6] != -1 ) {
            Log.d( TAG, "this_weekly_winning_numbers != -1" );
            return;
        }

        String m_cookie = null;
        try {
            String REQ_URL = "https://dhlottery.co.kr/gameResult.do?method=byWin";
            java.net.HttpURLConnection conn = null;

            //java.io.InputStream in_stream = null;
            java.io.OutputStream out_stream = null;
            java.io.BufferedReader breader = null;
            java.io.BufferedWriter bwriter = null;

            int response_code = 0;
            String response = null;

            java.net.URL url = new java.net.URL( REQ_URL );
            if ( url == null ) {
                Log.d( TAG, "URL == NULL" );
                return;
            }

            conn = (java.net.HttpURLConnection)url.openConnection();
            if ( conn == null ) {
                Log.d( TAG, "URLConnection == NULL" );
                return;
            }

            //conn.setRequestProperty( "User-Agent", "mobile_app" );
            //conn.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
            conn.setReadTimeout( 15000 );
            conn.setConnectTimeout( 15000 );
            conn.setRequestMethod( "POST" );
            conn.setDoInput( true);
            conn.setDoOutput( true );
            conn.setInstanceFollowRedirects( true );

            //! session id
            //{
            //    if ( m_cookie != null ) {
            //        conn.setRequestProperty( "cookie", m_cookie );
            //    }
            //}

            out_stream = conn.getOutputStream();
            if ( out_stream == null ) {
                Log.d( TAG, "Output Stream == NULL" );
                return;
            }

            bwriter = new java.io.BufferedWriter( new java.io.OutputStreamWriter(out_stream, "UTF-8") );
            if ( bwriter == null ) {
                Log.d( TAG, "BufferedWriter == NULL" );
                return;
            }

            StringBuilder data = new StringBuilder();
            if ( data == null ) {
                Log.d( TAG, "StringBuilder == NULL" );
                return;
            }

            {
                    /*
                    data.append( URLEncoder.encode(POST_VAR_ID, "UTF-8") );
                    data.append( "=" );
                    data.append( URLEncoder.encode(user_id, "UTF-8") );
                    data.append( "&" );
                    data.append( URLEncoder.encode(POST_VAR_PASSWD, "UTF-8") );
                    data.append( "=" );
                    data.append( URLEncoder.encode(user_passwd, "UTF-8") );
                    */
                data.append( "" );
            }

            bwriter.write( data.toString() );
            bwriter.flush();
            bwriter.close();

            if ( out_stream != null )
                out_stream.close();

            response_code = conn.getResponseCode();
            Log.d( TAG, "response code = " + response_code );
            if ( response_code == javax.net.ssl.HttpsURLConnection.HTTP_OK ) {
                Log.d(TAG, "response code = HttpsURLConnection.HTTP_OK");

                String line = null;

                breader = new java.io.BufferedReader(new java.io.InputStreamReader(conn.getInputStream()));
                if (breader == null) {
                    Log.d(TAG, "BufferedReader == NULL");
                    return;
                }

                response = "";
                int limit_line = 0; // 30
                while ((line = breader.readLine()) != null) {
                    if (line.contains("<br>")) {
                        line = line.replace("<br>", "\r\n");
                    }
                    response += line;

                    if ( ++limit_line == 30 ) break;
                }

                //! session id
                // Save the session id
                //{
                //    final String cookie = conn.getHeaderField("Set-Cookie");
                //    if (cookie != null) {
                //        // To preserve stored previous cookie
                //        m_cookie = cookie;
                //    }
                //
                //    // Cookie = PHPSESSID=qqgkmjl5sade1rljfftupj9ei3; path=/
                //    Log.d(TAG, "Cookie = " + m_cookie);
                //}
                breader.close();
                conn.disconnect();
                breader = null;
                conn = null;

                //Log.d(TAG, "response = " + response);

                response = response.replace("\uFEFF", "");    // remove UTF-8 BOM
                if ((response != null) && !response.isEmpty()) {
                    //Log.d(TAG, "response = " + response);

                    String content[] = response.split("content=" );
                    //for ( String val: content ) { Log.d(TAG, "content = " + val); }

                    String content_1[] = content[2].split(" " );
                    for ( String val: content_1 ) {
                        //Log.d(TAG, "content_1 = " + val);

                        String val1[] = val.split(",");
                        String val2[] = val.split("\\+");

                        //Log.d( TAG, val1.length + ", " + val2.length );

                        if ( val1.length == 6 && val2.length == 2 ) {
                            //Log.d( TAG, "" + val2[1].charAt(val2[1].length()-1) );

                            if ( val2[1].charAt(val2[1].length()-1) == '.' ) {
                                Log.d(TAG, ">>>> found: " + val);

                                // >>>> found: 10,15,24,30,31,37+32.

                                String str1[] = val2[0].split(",");
                                String str2[] = val2[1].split("\\.");

                                //for ( String x: str1 ) { Log.d(TAG, "str1 = " + x ); }
                                //for ( String x: str2 ) { Log.d(TAG, "str2 = " + x ); }

                                try {
                                    m_this_weekly_winning_numbers[0] = Integer.parseInt( str1[0] ); // #1
                                    m_this_weekly_winning_numbers[1] = Integer.parseInt( str1[1] ); // #2
                                    m_this_weekly_winning_numbers[2] = Integer.parseInt( str1[2] ); // #3
                                    m_this_weekly_winning_numbers[3] = Integer.parseInt( str1[3] ); // #4
                                    m_this_weekly_winning_numbers[4] = Integer.parseInt( str1[4] ); // #5
                                    m_this_weekly_winning_numbers[5] = Integer.parseInt( str1[5] ); // #6
                                    m_this_weekly_winning_numbers[6] = Integer.parseInt( str2[0] ); // bonus

                                    //Log.d( TAG, "--> [ " +
                                    //        m_this_weekly_winning_numbers[0] + ", " +
                                    //        m_this_weekly_winning_numbers[1] + ", " +
                                    //        m_this_weekly_winning_numbers[2] + ", " +
                                    //        m_this_weekly_winning_numbers[3] + ", " +
                                    //        m_this_weekly_winning_numbers[4] + ", " +
                                    //        m_this_weekly_winning_numbers[5] + ", " +
                                    //        m_this_weekly_winning_numbers[6] + " ]" );

                                    m_edittext_winning_num1.setText( "" + m_this_weekly_winning_numbers[0] );
                                    m_edittext_winning_num2.setText( "" + m_this_weekly_winning_numbers[1] );
                                    m_edittext_winning_num3.setText( "" + m_this_weekly_winning_numbers[2] );
                                    m_edittext_winning_num4.setText( "" + m_this_weekly_winning_numbers[3] );
                                    m_edittext_winning_num5.setText( "" + m_this_weekly_winning_numbers[4] );
                                    m_edittext_winning_num6.setText( "" + m_this_weekly_winning_numbers[5] );
                                    m_edittext_winning_num7_b.setText( "" + m_this_weekly_winning_numbers[6] );
                                } catch ( Exception e ) {
                                    e.printStackTrace();
                                }
                            }
                        }
                    }
                }
            }
        }
        catch ( Exception e) {
            e.printStackTrace();
            return;
        }
    }
}