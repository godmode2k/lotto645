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
import android.content.res.Configuration;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
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

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.atflab.android.lottery_prediction.App;
import com.atflab.android.lottery_prediction.R;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class HomeFragment extends Fragment {
    private static final String TAG = "HomeFragment";

    private HomeViewModel homeViewModel;


    // JNI
    //static { System.loadLibrary("lottery_prediction"); }
    private native String[] get_native_ml_module(int generate, int total_games);

    private TextView m_textview_result = null;

    private Boolean m_cancel_process = false;
    private ProgressDialog m_progress_dialog = null;

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
        }

        final EditText edittext_generate = (EditText)root.findViewById(R.id.EditText_generate);
        final EditText editText_total_games = (EditText)root.findViewById(R.id.EditText_total_games);
        //final TextView textview_result = (TextView)root.findViewById(R.id.TextView_result);
        Button button_generate = (Button)root.findViewById(R.id.Button_generate);

        m_textview_result = (TextView)root.findViewById(R.id.TextView_result);

        if ( button_generate != null ) {
            button_generate.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    //View view = getActivity().getCurrentFocus();
                    if (view != null) {
                        InputMethodManager imm = (InputMethodManager)getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
                    }

                    // JNI
                    //int generate = 300;
                    //get_native_ml_module( generate );

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

                    call_get_native_ml_module( generate, total_games, m_textview_result );
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

        if ( m_main_app != null && m_textview_result != null ) {
            m_main_app.set_str_result( m_textview_result.getText().toString() );
        }
    }

    @Override
    public void onResume() {
        super.onResume();

        // reload result
        if ( m_main_app != null && m_textview_result != null ) {
            m_textview_result.setText(m_main_app.get_str_result());
        }
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


        try {
            // /data/data/<package>/files/liblottery_prediction.so
            if ((new File(ml_so_app_full_pathname).exists())) {
                if ((new File(ml_so_app_full_pathname)).delete()) {
                    Log.d(TAG, "deleted directory: " + ml_so_app_full_pathname);
                } else {
                    Log.d(TAG, "[Error] deleted directory: " + ml_so_app_full_pathname);
                }
            }
        } catch (Exception e_all) {
            e_all.printStackTrace();
        }

        if ((new File(ml_so_download_full_pathname).exists())) {
            try {
                // /Download/liblottery_prediction.so
                inputStream = new FileInputStream(new File(ml_so_download_full_pathname));
                outputStream = new FileOutputStream(new File(ml_so_app_full_pathname));
                //openFileOutput(ml_so, Context.MODE_PRIVATE);

                FileChannel inChannel = inputStream.getChannel();
                FileChannel outChannel = outputStream.getChannel();
                inChannel.transferTo(0, inChannel.size(), outChannel);
                inputStream.close();
                outputStream.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        if (!(new File(ml_so_app_full_pathname).exists())) {
            Log.d( TAG,"load ML module: pre-installed" );
            System.loadLibrary( ml_so_name );
            Log.d( TAG,"load ML module: pre-installed done..." );
        }
        else {
            Log.d( TAG,"load ML module: downloaded (external-storage:/Download/" );
            System.load( ml_so_app_full_pathname );
            Log.d( TAG,"load ML module: downloaded done..." );
        }
    }

    public void call_get_native_ml_module(int generate, int total_games, TextView textview_result) {
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

        task.execute( generate, total_games, textview_result );
    }

    public class JNITask extends AsyncTask<Object, Object, Object> {
        private TextView m_textview_result = null;

        @Override
        protected Object doInBackground(Object... objects) {
            //return null;

            final int generate = (Integer)objects[0];
            final int total_games = (Integer)objects[1];
            m_textview_result = (TextView)objects[2];

            m_cancel_process = false;
            return work( generate, total_games );
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

            for ( int i = 0; i < list_result.size(); i++ ) {
                if ( m_cancel_process ) {
                    Log.d( TAG, "work(): cancelled" );
                    break;
                }

                if ( i == 0 ) {
                    result += "회차 데이터: " + list_result.get(i).toString() + "\n\n";
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

            if ( m_textview_result != null ) {
                m_textview_result.setText(result);
            }
        }

        public List<String> work(int _generate, int _total_games) {
            // JNI
            //int generate = 300;
            //get_native_ml_module( generate );

            int generate = _generate;
            int total_games = _total_games;

            return new ArrayList( Arrays.asList(get_native_ml_module(generate, total_games)) );
        }
    }
}