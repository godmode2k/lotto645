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
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.Toast;

import com.atflab.android.lottery_prediction.ui.home.HomeFragment;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.List;

public class App extends Application {
    private static final String TAG = "App";

    private Context m_context = null;
    private List<String> m_list_result = null;
    private String m_str_result = null;

    private Boolean m_cancel_process = false;
    private ProgressDialog m_progress_dialog = null;

    private String m_ml_so_updates_pathname = "";
    private String m_ml_so_download_full_pathname = "";
    private String m_ml_so_name = "lottery_prediction";
    private String m_ml_so = "liblottery_prediction.so";
    private String m_ml_so_updates = "updates.txt";

    // test (HTTP)
    // NOTE: AndroidManifest.xml: android:usesCleartextTraffic="true" for HTTP
    // http://192.168.0.8:9999/updates/updates.txt
    // http://192.168.0.8:9999/updates/liblottery_prediction.so
    //private String REQ_URL_BASE = "http://192.168.0.8:9999/updates/";
    //private String REQ_URL_CHECK_UPDATE = REQ_URL_BASE + m_ml_so_updates;
    //private String REQ_URL_DOWNLOAD_UPDATES = REQ_URL_BASE + m_ml_so;
    //
    // production (HTTPS)
    // https://github.com/godmode2k/lotto645/raw/main/updates/updates.txt
    // https://github.com/godmode2k/lotto645/raw/main/updates/liblottery_prediction.so
    private String REQ_URL_BASE = "https://github.com/godmode2k/lotto645/raw/main/updates/";
    private String REQ_URL_CHECK_UPDATE = REQ_URL_BASE + m_ml_so_updates;
    private String REQ_URL_DOWNLOAD_UPDATES = REQ_URL_BASE + m_ml_so;
    private String REQ_URL_BASE_APK = "https://github.com/godmode2k/lotto645/raw/main/"; // Git repo home


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

        {
            // /data/
            String path_base_internal = Environment.getDataDirectory().getPath();
            // /storage/emulated/0/
            String path_base_external = Environment.getExternalStorageDirectory().getPath();

            // base path: /data/media/0/Download/
            //String path_base = path_base_internal + "/media/0/Download";
            // base path: /storage/emulated/0/Download
            String path_base_download = path_base_external + "/Download";

            // app base path: /data/data/<package>/files/
            String app_path_base = m_context.getFilesDir().getAbsolutePath();

            //String ml_so_name = "lottery_prediction";
            //String ml_so = "liblottery_prediction.so";
            //String ml_so_updates = "updates.txt";
            //String ml_so_updates_pathname = app_path_base + "/" + ml_so_updates;
            //String ml_so_download_full_pathname = path_base_download + "/" + ml_so;
            m_ml_so_updates = "updates.txt";
            m_ml_so_updates_pathname = app_path_base + "/" + m_ml_so_updates;
            m_ml_so_download_full_pathname = path_base_download + "/" + m_ml_so;
        }
    }

    public void release() {
        if ( m_list_result != null ) {
            m_list_result.clear();
        }
        m_list_result = null;
        m_str_result = "";
    }

    // Download directory: Environment.DIRECTORY_DOWNLOADS
    // - GetPublicPath(Environment.DIRECTORY_DOWNLOADS)
    public String GetPublicPath(String target_dir) {
        try {
            String strFilePath = "./";
            String strFilePathInt = "";
            //String strFilePathExt = "/sdcard/";
            String strFilePathExt = Environment.getExternalStoragePublicDirectory(target_dir).getPath();

            // Get absolute path of the SD card
            // e.g., "/mnt/sdcard/"
            strFilePath = strFilePathExt + "/";

            return strFilePath;
        }
        catch ( Exception e ) {
            e.printStackTrace();
            return null;
        }
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

    public void updates(Context context) {
        DownloadTask task = new DownloadTask();

        m_progress_dialog = new ProgressDialog( context );
        if ( m_progress_dialog == null ) {
            Log.d( TAG, "updates(): ProgressDialog == NULL" );
            return;
        }

        m_progress_dialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        m_progress_dialog.setMessage("업데이트 다운로드 중...");
        m_progress_dialog.setCancelable(true);
        m_progress_dialog.setOnCancelListener(new DialogInterface.OnCancelListener() {
            @Override
            public void onCancel(DialogInterface dialog) {
                m_cancel_process = true;
            }
        });
        m_progress_dialog.show();

        if ( task == null ) {
            Log.d( TAG, "updates(): DownloadTask == NULL" );
            m_progress_dialog.dismiss();
            return;
        }

        //Toast.makeText(m_context,
        //        "[title] title\n"
        //                + "[+] sub1\n"
        //                + "[+] sub2",
        //        Toast.LENGTH_LONG).show();

        task.execute();
    }

    public class DownloadTask extends AsyncTask<Object, Object, Object> {
        @Override
        protected Object doInBackground(Object... objects) {
            //return null;

            m_cancel_process = false;

            // -1: no updates, 0: false (fail), 1: true (success, download .so), 2: true (success, download .apk)
            int updated = -1;

            Object check_updates[] = check_for_updates();
            // test
            //check_updates[0] = true;
            //check_updates[1] = true;

            if ( (boolean)check_updates[0] ) {
                String REQ_URL = "";
                String save_filename = "";
                String save_dir = "";

                // Download .so: liblottery_prediction.so
                REQ_URL = REQ_URL_DOWNLOAD_UPDATES;
                save_filename = "liblottery_prediction.so";
                updated = download_update_file( REQ_URL, save_filename )? 1 : 0;

                // Download APK: app-release_YYYY.MM.DD_lotto645번호생성.apk
                if ( (boolean)check_updates[1] ) {
                    //save_filename = "app-release_" + "2024.11.04" + "_lotto645번호생성.apk"; // test
                    save_filename = "app-release_" + (String)check_updates[2] + "_lotto645번호생성.apk";
                    save_dir = "lotto645"; // (Download)/lotto645
                    REQ_URL = REQ_URL_BASE_APK + save_filename;

                    final int old_updated = updated;
                    updated += download_file( REQ_URL, save_filename, true, save_dir )? 1 : 0;

                    // fail
                    if ( old_updated == updated ) updated = 0;
                }
            }

            return updated;
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

            // -1: no updates, 0: false (fail), 1: true (success, download .so), 2: true (success, download .apk)
            int result = (int)o;
            String message = "";
            if ( result == -1 ) {
                message = "[업데이트] 업데이트가 없습니다.";
            }
            else if ( result == 0 ) {
                message = "[업데이트] 업데이트를 실패했습니다.";
            }
            else if ( result == 1 ) {
                message = "[업데이트] 완료!\n앱을 다시 실행합니다!"
                    + "실행이 안되면 앱을 완전히 종료 후 다시 실행해 주세요!";
            }
            else if ( result == 2 ) {
                message = "[업데이트] APK 다운로드 완료!\n"
                        + "앱 삭제 후 다운받은 APK를 다시 설치해 주세요! (다운로드 디렉터리에서 확인)";
            }
            else {
                message = "Error...";
            }

            Toast.makeText(m_context, message, Toast.LENGTH_LONG).show();

            if ( result == 1 ) {
                // Restart App

                // Source: https://stackoverflow.com/questions/6609414/how-do-i-programmatically-restart-an-android-app
                android.content.pm.PackageManager packageManager = m_context.getPackageManager();
                android.content.Intent intent = packageManager.getLaunchIntentForPackage(m_context.getPackageName());
                android.content.ComponentName componentName = intent.getComponent();
                android.content.Intent mainIntent = android.content.Intent.makeRestartActivityTask(componentName);
                // Required for API 34 and later
                // Ref: https://developer.android.com/about/versions/14/behavior-changes-14#safer-intents
                mainIntent.setPackage(m_context.getPackageName());
                m_context.startActivity(mainIntent);
                Runtime.getRuntime().exit(0);
            }
            else if ( result == 2 ) {
                //Runtime.getRuntime().exit(0);
            }
        }
    }

    public String get_current_updates_info() {
        // get current updates info (just a counting number)

        String ret = null;

        try {
            File f = new File(m_ml_so_updates_pathname);
            if (f.exists()) {
                //if ((new File(m_ml_so_updates_pathname).exists())) {
                FileInputStream inputStream;
                //inputStream = new FileInputStream(new File(m_ml_so_updates_pathname));
                inputStream = new FileInputStream(f);

                java.io.BufferedReader breader = new java.io.BufferedReader(new java.io.InputStreamReader(inputStream));
                if (breader == null) {
                    Log.d(TAG, "BufferedReader == NULL");
                    inputStream.close();
                    inputStream = null;
                    return null;
                }

                String res = "";
                String line = "";
                while ((line = breader.readLine()) != null) {
                    res += line;
                }
                breader.close();
                inputStream.close();
                breader = null;
                inputStream = null;

                // updates.txt: 1,2024.07.26
                //String update_count = res.split(",")[0];
                //String current_updates_date = res.split(",")[1];
                //int current_updates = Integer.parseInt(update_count);
                ret = res;
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        return ret;
    }

    private String handle_redirect(String REQ_URL) {
        boolean redirected;
        String redirected_url = null;
        int redirect_count = 0;

        java.net.HttpURLConnection conn = null;
        String url = REQ_URL;

        try {
            // Source: https://stackoverflow.com/questions/15754633/android-httpurlconnection-handle-http-redirects
            do {
                conn = (java.net.HttpURLConnection) new java.net.URL(url).openConnection();
                int code = conn.getResponseCode();
                redirected = code == java.net.HttpURLConnection.HTTP_MOVED_PERM
                        || code == java.net.HttpURLConnection.HTTP_MOVED_TEMP
                        || code == java.net.HttpURLConnection.HTTP_SEE_OTHER;
                if (redirected) {
                    url = conn.getHeaderField("Location");
                    conn.disconnect();

                    ++redirect_count;
                }

                if (redirect_count > 5) {
                    Log.d(TAG, "Error: many redirect...");
                    if ( conn != null ) {
                        conn.disconnect();
                        conn = null;
                    }
                    break;
                }
            } while (redirected);

            redirected_url = conn.getURL().toString();
            Log.d(TAG, "Redirect: " + redirected_url );

            conn.disconnect();
            conn = null;
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        return redirected_url;
    }

    private Object[] check_for_updates() {
        Log.d( TAG, "Check for updates..." );

        // updates.txt: 1,2024.07.26,[y|n]
        Object result[] = new Object[]{ false, false, "" };

        if ( !network_online() ) {
            Arrays.fill( result, false );
            return result;
        }

        int current_updates = 0; // just a counting number
        String current_updates_date = ""; // 2024.07.26
        boolean has_updates = false;
        Boolean has_updates_flag_download_apk = false; // 1,2024.07.26,[y|n]

        String res = get_current_updates_info();
        if ( res == null ) {
            Log.d( TAG, "Error: cannot current updates info from " + m_ml_so_updates_pathname );
            Log.d( TAG, "initialize update: set to '0,0'" );
            res = "0,0";
        }
        // updates.txt: 1,2024.07.26,[y|n]
        String update_count = res.split(",")[0];
        current_updates_date = res.split(",")[1];
        current_updates = Integer.parseInt(update_count);


        // get new updates info
        try {
            String m_cookie = null;

            String REQ_URL = REQ_URL_CHECK_UPDATE;
            java.net.HttpURLConnection conn = null;
            Log.d( TAG, "REQ = " + REQ_URL_CHECK_UPDATE );

            //java.io.InputStream in_stream = null;
            java.io.OutputStream out_stream = null;
            java.io.BufferedReader breader = null;
            java.io.BufferedWriter bwriter = null;

            int response_code = 1;
            String response = null;

            // handle the redirect url
            String redirected_url = handle_redirect( REQ_URL );
            if ( redirected_url == null ) {
                Arrays.fill( result, false );
                return result;
            }

            //java.net.URL url = new java.net.URL(REQ_URL);
            java.net.URL url = new java.net.URL(redirected_url);
            if (url == null) {
                Log.d(TAG, "URL == NULL");
                Arrays.fill( result, false );
                return result;
            }

            conn = (java.net.HttpURLConnection) url.openConnection();
            if (conn == null) {
                Log.d(TAG, "URLConnection == NULL");
                Arrays.fill( result, false );
                return result;
            }


            //conn.addRequestProperty( "User-Agent", "Mozilla/5.0 AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36" );
            //conn.setRequestProperty( "User-Agent", "Mozilla/5.0 AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36" );
            //conn.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
            conn.setReadTimeout(15000);
            conn.setConnectTimeout(15000);
            conn.setRequestMethod("POST");
            conn.setDoInput(true);
            conn.setDoOutput(true);
            conn.setInstanceFollowRedirects(true);

            //! session id
            //{
            //    if ( m_cookie != null ) {
            //        conn.setRequestProperty( "cookie", m_cookie );
            //    }
            //}


            {
                java.io.InputStream is = url.openStream();
                java.io.BufferedReader br = new java.io.BufferedReader(new java.io.InputStreamReader(is));

                String line = "";
                response = "";

                while ((line = br.readLine()) != null) {
                    response += line;
                }
                is.close();
                br.close();
                is = null;
                br = null;

                // updates.txt: 1,2024.07.26,[y|n]
                String new_updates_count = response.split( "," )[0];
                String new_updates_date = response.split( "," )[1];
                // 1,2024.07.26,[y|n]
                if ( response.split( "," ).length > 2 ) {
                    has_updates_flag_download_apk =
                            (response.split(",")[2] == "y")? true : false;
                }
                has_updates = (Integer.parseInt(new_updates_count) > current_updates);

                if ( Integer.parseInt(new_updates_count) == 0
                        && current_updates == 0
                        && !(new File( getFilesDir(), m_ml_so_updates)).exists() ) {
                    has_updates = true;
                }

                result[0] = has_updates;
                result[1] = has_updates_flag_download_apk; // default: false
                result[2] = new_updates_date; // default: "0"

                if (has_updates) {
                    // update file
                    //File f = new File( getFilesDir(), m_ml_so_updates_pathname);
                    File f = new File( getFilesDir(), m_ml_so_updates);
                    if ( !f.exists() ) {
                        f.createNewFile();
                    }
                    if ( f.exists() ) {
                        OutputStream os = new FileOutputStream(f);
                        if (os != null) {
                            os.write(response.getBytes());
                        }
                    }
                    else {
                        Log.d( TAG, "Error: cannot created: " + m_ml_so_updates_pathname );
                    }
                }
                Log.d( TAG, "has updates: " + has_updates );
                Log.d( TAG, "has updates: download APK: " + has_updates_flag_download_apk );
                Log.d( TAG, "updates: current: " + current_updates + ", new: " + new_updates_count );
                Log.d( TAG, "updates: current: " + current_updates_date + ", new: " + new_updates_date );

                conn.disconnect();
                conn = null;
            }


// NOT work for https://github.com/...
// Response: 403 Error
/*
            out_stream = conn.getOutputStream();
            if (out_stream == null) {
                Log.d(TAG, "Output Stream == NULL");
                return false;
            }

            bwriter = new java.io.BufferedWriter(new java.io.OutputStreamWriter(out_stream, "UTF-8"));
            if (bwriter == null) {
                Log.d(TAG, "BufferedWriter == NULL");
                return false;
            }

            StringBuilder data = new StringBuilder();
            if (data == null) {
                Log.d(TAG, "StringBuilder == NULL");
                return false;
            }

            {
                    //data.append( URLEncoder.encode(POST_VAR_ID, "UTF-8") );
                    //data.append( "=" );
                    //data.append( URLEncoder.encode(user_id, "UTF-8") );
                    //data.append( "&" );
                    //data.append( URLEncoder.encode(POST_VAR_PASSWD, "UTF-8") );
                    //data.append( "=" );
                    //data.append( URLEncoder.encode(user_passwd, "UTF-8") );
                data.append("");
            }

            bwriter.write(data.toString());
            bwriter.flush();
            bwriter.close();

            if (out_stream != null)
                out_stream.close();


            response_code = conn.getResponseCode();
            Log.d(TAG, "response code = " + response_code);
            Log.d(TAG, "URL = " + conn.getURL() );
            if (response_code == javax.net.ssl.HttpsURLConnection.HTTP_OK) {
                Log.d(TAG, "response code = HttpsURLConnection.HTTP_OK");

                String line = null;

                breader = new java.io.BufferedReader(new java.io.InputStreamReader(conn.getInputStream()));
                if (breader == null) {
                    Log.d(TAG, "BufferedReader == NULL");
                    return false;
                }

                response = "";
                //int limit_line = 0; // 30
                while ((line = breader.readLine()) != null) {
                    //if (line.contains("<br>")) {
                    //    line = line.replace("<br>", "\r\n");
                    //}
                    response += line;

                    //if (++limit_line == 30) break;
                }
                Log.d(TAG, "response: " + response);

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

                // updates.txt: 1,2024.07.26
                String new_updates_count = response.split( "," )[0];
                String new_updates_date = response.split( "," )[1];
                has_updates = (Integer.parseInt(new_updates_count) > current_updates);

                if (has_updates) {
                    // update file
                    //File f = new File( getFilesDir(), m_ml_so_updates_pathname);
                    File f = new File( getFilesDir(), m_ml_so_updates);
                    if ( !f.exists() ) {
                        f.createNewFile();
                    }
                    if ( f.exists() ) {
                        OutputStream os = new FileOutputStream(f);
                        if (os != null) {
                            os.write(response.getBytes());
                        }
                    }
                    else {
                        Log.d( TAG, "Error: cannot created: " + m_ml_so_updates_pathname );
                    }
                }
                Log.d( TAG, "has updates: " + has_updates );
                Log.d( TAG, "updates: current: " + current_updates + ", new: " + new_updates_count );
                Log.d( TAG, "updates: current: " + current_updates_date + ", new: " + new_updates_date );
            }
*/
        }
        catch (Exception e) {
            e.printStackTrace();
            Arrays.fill( result, false );
        }

        return result;
    }

    private boolean download_update_file(String REQ_URL, String save_filename) {
        Log.d( TAG, "download updates..." );

        if ( !network_online() ) {
            return false;
        }

        if ( REQ_URL.isEmpty() || save_filename.isEmpty() ) {
            return false;
        }

        Log.d( TAG, "URL = " + REQ_URL );
        Log.d( TAG, "Save filename = " + save_filename );

        String m_cookie = null;
        try {
            //String REQ_URL = REQ_URL_DOWNLOAD_UPDATES;
            java.net.HttpURLConnection conn = null;

            //java.io.InputStream in_stream = null;
            java.io.OutputStream out_stream = null;
            //java.io.BufferedReader breader = null;
            java.io.BufferedWriter bwriter = null;

            int response_code = 0;
            String response = null;


            // handle the redirect url
            String redirected_url = handle_redirect( REQ_URL );
            if ( redirected_url == null ) {
                return false;
            }

            //java.net.URL url = new java.net.URL(REQ_URL);
            java.net.URL url = new java.net.URL(redirected_url);
            if (url == null) {
                Log.d(TAG, "URL == NULL");
                return false;
            }

            conn = (java.net.HttpURLConnection) url.openConnection();
            if (conn == null) {
                Log.d(TAG, "URLConnection == NULL");
                return false;
            }

            //conn.setRequestProperty( "User-Agent", "mobile_app" );
            //conn.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
            conn.setReadTimeout(15000);
            conn.setConnectTimeout(15000);
            conn.setRequestMethod("POST");
            conn.setDoInput(true);
            conn.setDoOutput(true);
            conn.setInstanceFollowRedirects(true);

            //! session id
            //{
            //    if ( m_cookie != null ) {
            //        conn.setRequestProperty( "cookie", m_cookie );
            //    }
            //}


            {
                java.io.InputStream is = url.openStream();
                java.io.File file = null;
                java.io.OutputStream output = null;
                byte[] buffer = new byte[4 * 1024];
                int bytes = 0;
                //file = new java.io.File(getFilesDir(), "liblottery_prediction.so");

                // Download: liblottery_prediction.so
                file = new java.io.File(getFilesDir(), save_filename);

                if (file == null) {
                    Log.d(TAG, "file == NULL");
                    return false;
                }

                Log.d(TAG, "file = " + file.getAbsolutePath() );

                output = new java.io.FileOutputStream(file);
                if (output == null) {
                    Log.d(TAG, "output == NULL");
                    return false;
                }

                while ((bytes = is.read(buffer)) > 0) {
                    output.write(buffer, 0, bytes);
                }
                output.flush();
                output = null;
                file = null;

                conn.disconnect();
                conn = null;
            }


// NOT work for https://github.com/...
// Response: 403 Error
/*
            out_stream = conn.getOutputStream();
            if (out_stream == null) {
                Log.d(TAG, "Output Stream == NULL");
                return false;
            }

            bwriter = new java.io.BufferedWriter(new java.io.OutputStreamWriter(out_stream, "UTF-8"));
            if (bwriter == null) {
                Log.d(TAG, "BufferedWriter == NULL");
                return false;
            }

            StringBuilder data = new StringBuilder();
            if (data == null) {
                Log.d(TAG, "StringBuilder == NULL");
                return false;
            }

            {
                    //data.append( URLEncoder.encode(POST_VAR_ID, "UTF-8") );
                    //data.append( "=" );
                    //data.append( URLEncoder.encode(user_id, "UTF-8") );
                    //data.append( "&" );
                    //data.append( URLEncoder.encode(POST_VAR_PASSWD, "UTF-8") );
                    //data.append( "=" );
                    //data.append( URLEncoder.encode(user_passwd, "UTF-8") );
                data.append("");
            }

            bwriter.write(data.toString());
            bwriter.flush();
            bwriter.close();

            if (out_stream != null)
                out_stream.close();

            response_code = conn.getResponseCode();
            Log.d(TAG, "response code = " + response_code);
            if (response_code == javax.net.ssl.HttpsURLConnection.HTTP_OK) {
                Log.d(TAG, "response code = HttpsURLConnection.HTTP_OK");

                String line = null;

                java.io.File file = null;
                java.io.OutputStream output = null;
                byte[] buffer = new byte[4 * 1024];
                int bytes = 0;
                file = new java.io.File(getFilesDir(), "liblottery_prediction.so");
                if (file == null) {
                    Log.d(TAG, "file == NULL");
                    return false;
                }
                output = new java.io.FileOutputStream(file);
                if (output == null) {
                    Log.d(TAG, "output == NULL");
                    return false;
                }

                while ((bytes = conn.getInputStream().read(buffer)) > 0) {
                    output.write(buffer, 0, bytes);
                }
                output.flush();
                output = null;
                file = null;

                //breader = new java.io.BufferedReader(new java.io.InputStreamReader(conn.getInputStream()));
                //if (breader == null) {
                //    Log.d(TAG, "BufferedReader == NULL");
                //    return false;
                //}
                //
                //response = "";
                //int limit_line = 0; // 30
                //while ((line = breader.readLine()) != null) {
                //    if (line.contains("<br>")) {
                //        line = line.replace("<br>", "\r\n");
                //    }
                //    response += line;
                //
                //    if (++limit_line == 30) break;
                //}

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
                //breader.close();
                conn.disconnect();
                //breader = null;
                conn = null;
            }
*/

            Log.d(TAG, "download updates: done");
        }
        catch ( Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    private boolean download_file(String REQ_URL, String save_filename, Boolean into_public_download, String save_dir) {
        Log.d( TAG, "download updates..." );

        if ( !network_online() ) {
            return false;
        }

        if ( REQ_URL.isEmpty() || save_filename.isEmpty() ) {
            return false;
        }

        Log.d( TAG, "URL = " + REQ_URL );
        Log.d( TAG, "Save filename = " + save_filename );
        Log.d( TAG, "Save directory = " + save_dir );

        String m_cookie = null;
        try {
            //String REQ_URL = REQ_URL_DOWNLOAD_UPDATES;
            java.net.HttpURLConnection conn = null;

            //java.io.InputStream in_stream = null;
            java.io.OutputStream out_stream = null;
            //java.io.BufferedReader breader = null;
            java.io.BufferedWriter bwriter = null;

            int response_code = 0;
            String response = null;


            // handle the redirect url
            String redirected_url = handle_redirect( REQ_URL );
            if ( redirected_url == null ) {
                return false;
            }

            //java.net.URL url = new java.net.URL(REQ_URL);
            java.net.URL url = new java.net.URL(redirected_url);
            if (url == null) {
                Log.d(TAG, "URL == NULL");
                return false;
            }

            conn = (java.net.HttpURLConnection) url.openConnection();
            if (conn == null) {
                Log.d(TAG, "URLConnection == NULL");
                return false;
            }

            //conn.setRequestProperty( "User-Agent", "mobile_app" );
            //conn.setRequestProperty( "Content-Type", "application/x-www-form-urlencoded" );
            conn.setReadTimeout(15000);
            conn.setConnectTimeout(15000);
            conn.setRequestMethod("POST");
            conn.setDoInput(true);
            conn.setDoOutput(true);
            conn.setInstanceFollowRedirects(true);

            //! session id
            //{
            //    if ( m_cookie != null ) {
            //        conn.setRequestProperty( "cookie", m_cookie );
            //    }
            //}


            {
                java.io.InputStream is = url.openStream();
                java.io.File file = null;
                java.io.OutputStream output = null;
                byte[] buffer = new byte[4 * 1024];
                int bytes = 0;

                if ( into_public_download ) {
                    // Download: APK
                    //file = new java.io.File( new_path, save_filename );
                    //file = new java.io.File( new_path, "/app-release_" + "2024.11.04" + "_lotto645.apk" );

                    Uri collection;
                    ContentResolver resolver = m_context.getContentResolver();
                    ContentValues contentValues = new ContentValues();

                    contentValues.put(MediaStore.MediaColumns.DISPLAY_NAME, save_filename);
                    //contentValues.put(MediaStore.MediaColumns.MIME_TYPE, "text/plain"); // test
                    contentValues.put(MediaStore.MediaColumns.RELATIVE_PATH,
                            Environment.DIRECTORY_DOWNLOADS + File.separator + save_dir);

                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                        collection = MediaStore.Downloads.getContentUri(MediaStore.VOLUME_EXTERNAL_PRIMARY);
                    } else {
                        collection = MediaStore.Files.getContentUri("external");
                    }

                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                        contentValues.put(MediaStore.MediaColumns.IS_PENDING, 1);
                    }

                    Uri fileUri = resolver.insert(collection, contentValues);

                    if (fileUri == null) {
                        Log.d(TAG, "output == NULL");
                        return false;
                    }

                    //try (OutputStream outputStream = resolver.openOutputStream(fileUri)) {
                    //    outputStream.write(content.getBytes());
                    //    outputStream.flush();
                    //    Toast.makeText(m_context, "File saved to Downloads", Toast.LENGTH_SHORT).show();
                    //}
                    //catch (IOException e) {
                    //    e.printStackTrace();
                    //    Toast.makeText(m_context, "Failed to save file", Toast.LENGTH_SHORT).show();
                    //}

                    //output = new java.io.FileOutputStream(file);
                    output = resolver.openOutputStream(fileUri);
                    if (output == null) {
                        Log.d(TAG, "output == NULL");
                        return false;
                    }

                    Log.d(TAG, "file (URI) = " + fileUri.toString() );
                    Log.d(TAG, "pathname = " + Environment.DIRECTORY_DOWNLOADS + "/" + save_dir + "/" + save_filename );

                    while ((bytes = is.read(buffer)) > 0) {
                        output.write(buffer, 0, bytes);
                    }
                    output.flush();

                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                        contentValues.clear();
                        contentValues.put(MediaStore.MediaColumns.IS_PENDING, 0);
                        resolver.update(fileUri, contentValues, null, null);
                    }
                }
                else {
                    // Internal Private Own Directory
                    // Download: liblottery_prediction.so
                    file = new java.io.File(getFilesDir(), save_filename);

                    Log.d(TAG, "file = " + file.getAbsolutePath() );

                    output = new java.io.FileOutputStream(file);
                    if (output == null) {
                        Log.d(TAG, "output == NULL");
                        return false;
                    }

                    while ((bytes = is.read(buffer)) > 0) {
                        output.write(buffer, 0, bytes);
                    }
                    output.flush();
                }

                output = null;
                file = null;

                conn.disconnect();
                conn = null;
            }

            Log.d(TAG, "download updates: done");
        }
        catch ( Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    //public boolean download_contents(final String save_filename, final String contents) {
    public boolean download_contents(final String save_filename, final byte[] contents) {
        try {
            Uri collection;
            ContentResolver resolver = m_context.getContentResolver();
            ContentValues contentValues = new android.content.ContentValues();

            contentValues.put(MediaStore.MediaColumns.DISPLAY_NAME, save_filename);
            contentValues.put(MediaStore.MediaColumns.MIME_TYPE, "text/plain");
            contentValues.put(MediaStore.MediaColumns.RELATIVE_PATH, Environment.DIRECTORY_DOWNLOADS);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                collection = MediaStore.Downloads.getContentUri(MediaStore.VOLUME_EXTERNAL_PRIMARY);
            } else {
                collection = MediaStore.Files.getContentUri("external");
            }

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                contentValues.put(MediaStore.MediaColumns.IS_PENDING, 1);
            }

//            File home_dir = new File(new_path);
//            if (!home_dir.exists()) {
//                if (home_dir.mkdir()) {
//                    Log.d(TAG, "home directory created: " + home_dir.getAbsolutePath());
//                } else {
//                    Log.d(TAG, "home directory created [FAIL]: " + home_dir.getAbsolutePath());
//                    return 0;
//                }
//            }

            Uri fileUri = resolver.insert(collection, contentValues);
            if (fileUri != null) {
                try (OutputStream outputStream = resolver.openOutputStream(fileUri)) {
                    //outputStream.write(content.getBytes());
                    outputStream.write( contents );
                    outputStream.flush();
                    //Toast.makeText(m_context, "File saved to Downloads", Toast.LENGTH_SHORT).show();
                } catch (IOException e) {
                    e.printStackTrace();
                    //Toast.makeText(m_context, "Failed to save file", Toast.LENGTH_SHORT).show();
                }

                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                    contentValues.clear();
                    contentValues.put(MediaStore.MediaColumns.IS_PENDING, 0);
                    resolver.update(fileUri, contentValues, null, null);
                }
            } else {
                //Toast.makeText(m_context, "Failed to create file", Toast.LENGTH_SHORT).show();
                return false;
            }
        }
        catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }
}
