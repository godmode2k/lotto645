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

import android.app.Application;
import android.content.Context;
import android.util.Log;

import java.util.List;

public class App extends Application {
    private static final String TAG = "App";

    private Context m_context = null;
    private List<String> m_list_result = null;
    private String m_str_result = null;

    @Override
    public void onCreate() {
        super.onCreate();

        init();
    }

    @Override
    public void onTerminate() {
        super.onTerminate();

        release();
    }

    public void init() {
        m_context = this.getApplicationContext();
    }

    public void release() {
        if ( m_list_result != null ) {
            m_list_result.clear();
        }
        m_list_result = null;
        m_str_result = "";
    }

    public void set_list_result(List<String> result) {
        m_list_result.addAll( result );
    }

    public List<String> get_list_result() {
        return m_list_result;
    }

    public void set_str_result(String result) {
        m_str_result = result;
    }

    public String get_str_result() {
        return m_str_result;
    }

    public boolean network_online() {
        boolean state = false;

        // Source: https://stackoverflow.com/questions/4238921/detect-whether-there-is-an-internet-connection-available-on-android
        boolean haveConnectedWifi = false;
        boolean haveConnectedMobile = false;
        android.net.ConnectivityManager cm = (android.net.ConnectivityManager) this.getSystemService(Context.CONNECTIVITY_SERVICE);
        android.net.NetworkInfo[] netInfo = cm.getAllNetworkInfo();
        for ( android.net.NetworkInfo ni : netInfo ) {
            if (ni.getTypeName().equalsIgnoreCase("WIFI"))
                if (ni.isConnected())
                    haveConnectedWifi = true;
            if (ni.getTypeName().equalsIgnoreCase("MOBILE"))
                if (ni.isConnected())
                    haveConnectedMobile = true;
        }
        state = haveConnectedWifi || haveConnectedMobile;

        if ( state ) Log.d( TAG, "Network: online" );
        else Log.d( TAG, "Network: offline" );

        return state;
    }
}
