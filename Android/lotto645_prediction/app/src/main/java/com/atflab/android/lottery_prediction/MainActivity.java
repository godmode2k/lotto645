package com.atflab.android.lottery_prediction;

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

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import android.os.Environment;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.google.android.material.navigation.NavigationView;

import androidx.drawerlayout.widget.DrawerLayout;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.view.Menu;
import android.view.WindowManager;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";


    private AppBarConfiguration mAppBarConfiguration;

    private App m_main_app = null;

    /*
    // JNI
    //static { System.loadLibrary("lottery_prediction"); }
    private native String[] get_native_ml_module(int generate);
    */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        /*
        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
        DrawerLayout drawer = findViewById(R.id.drawer_layout);
        NavigationView navigationView = findViewById(R.id.nav_view);
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        mAppBarConfiguration = new AppBarConfiguration.Builder(
                R.id.nav_home, R.id.nav_gallery, R.id.nav_slideshow,
                R.id.nav_tools, R.id.nav_share, R.id.nav_send)
                .setDrawerLayout(drawer)
                .build();
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        NavigationUI.setupActionBarWithNavController(this, navController, mAppBarConfiguration);
        NavigationUI.setupWithNavController(navigationView, navController);
*/

        // Permission
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.INTERNET) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                new String[]{
                        Manifest.permission.INTERNET,
                        Manifest.permission.READ_EXTERNAL_STORAGE,
                        Manifest.permission.ACCESS_NETWORK_STATE,
                        Manifest.permission.INTERNET
                },
                100);   // 100: my request code
        }
        else {
            Log.d( TAG, "granted already..." );
        }

        // Prevent soft-keyboard slide-out
        getWindow().setSoftInputMode (WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN );

        m_main_app = (App)getApplicationContext();
        if ( m_main_app == null ) {
            this.finish();
        }

        /*
        // JNI
        load_jni( this.getApplicationContext() );
        int generate = 300;
        //get_native_ml_module( generate );
        List<String> result = new ArrayList( Arrays.asList(get_native_ml_module(generate)) );
        for ( int i = 0; i < result.size(); i++ ) {
            Log.d( TAG, "[" + i + "] " + result.get(i).toString() );
        }
        */
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        //getMenuInflater().inflate(R.menu.main, menu);
        //return true;

        return false;
    }

    @Override
    public boolean onSupportNavigateUp() {
        //NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        //return NavigationUI.navigateUp(navController, mAppBarConfiguration)
        //        || super.onSupportNavigateUp();

        return false;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if ( m_main_app != null ) {
            m_main_app.release();
        }

        System.gc();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onPostResume() {
        super.onPostResume();
    }

    //@Override
    //public void onBackPressed() {
    //    super.onBackPressed();
    //}

    // Permission
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case 100: {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Log.d( TAG, "granted..." );
                }
            }
        }
    }

    /*
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
        }
        else {
            Log.d( TAG,"load ML module: downloaded" );
            System.load( ml_so_app_full_pathname );
        }
    }
    */
}
