# Lotto 645 prediction test: Android App


Summary
----------
>



Environment
----------
```sh
Python: v3.7.4
sklearn, micromlgen

Android:
 - Android Studio
 - Android 11
 - NDK
```



Installation and Run
----------
```sh
$ pip install numpy pandas lxml
$ pip install scikit-learn

$ pip install micromlgen
or
$ pip install https://github.com/eloquentarduino/micromlgen.git


$ python3 test_lotto645_tmp2.py
results:
 - model_lotto645.h
 - model_lotto645_predicts_method.h
 - model_lotto645_results_winning_numbers.h


// Android App
APK requires Network permission to get a last winning numbers.
You can also type the numbers if you don't want using Network.
Or you can ignore that.

안드로이드 앱에서 지난 번 당첨번호를 가져오기 위해 네트워크를 사용합니다.
네트워크 사용을 원하지 않으면 당첨번호를 직접 입력하거나 해당 기능(버튼)을 사용하지 않으면 됩니다.

=== 업데이트 ===

1. 앱 업데이트
 - 프로젝트 코드와 업데이트 기능이 변경되어 내장 업데이트만으로는 적용되지 않습니다.
 - 기존에 설치된 앱을 삭제하고 APK를 재설치 해야합니다.
 -
 - 이제 업데이트시에 APK 재설치가 필요할 경우, APK 파일을 내장메모리 <Download/lotto645> 디렉터리에 다운로드합니다.
 - 설치되어 있는 앱은 삭제하고 새버전으로 다시 설치해주면 됩니다.

2. 번호생성 알고리즘
 - 번호생성 알고리즘(4)이 추가되었습니다.

3. test_lotto645_tmp2.py
 - _xls_last_game_num = "1186" 에서 원하는 회차번호만 변경하면 해당 xls 파일을 다운로드합니다.
```



Android App
----------
```sh
$ cd lotto645_prediction/app/src/main/cpp/

//1. Download winning list
// Download (Excel: xls) all results
// https://www.dhlottery.co.kr/gameResult.do?method=byWin
//
// e.g., lotto645 당첨번호 1128회차까지
// https://dhlottery.co.kr/gameResult.do?method=allWinExel&gubun=byWin&nowPage=
// &drwNoStart=1&drwNoEnd=1128
//
//Rename download file:
// - lotto645_당첨번호1128회차까지.xls

//2. (Edit) test_lotto645_tmp2.py: 188
//_xls_filename = "./lotto645_당첨번호1128회차까지.xls"

2. (Edit) test_lotto645_tmp2.py:
_xls_last_game_num = "1186"    # last game number

3. Generate codes
$ python3 test_lotto645_tmp2.py
results:
 - model_lotto645.h
 - model_lotto645_predicts_method.h
 - model_lotto645_results_winning_numbers.h
 - numbers

(NOTE)
 - ml_module.cpp requires {
    model_lotto645.h,
    model_lotto645_predicts_method.h,
    model_lotto645_results_winning_numbers.h
 }

4. Copy below files to "lotto645_prediction/app/src/main/cpp/"
{
    model_lotto645.h,
    model_lotto645_predicts_method.h,
    model_lotto645_results_winning_numbers.h
}

5. then, rebuild APK


---------------------------------------------
Rebuild/Generate signed APK Android App
---------------------------------------------
results:
 - library (.so): lotto645_prediction/app/src/main/jniLibs/ (SEE: platforms)
 - lotto645_prediction/app/release/app-release.apk

---------------------------------------------
Updates library (.so) without reinstall APK
---------------------------------------------
1. rebuild library (.so)
2. Android device:
 - Copy .so file (lotto645_prediction/app/src/main/jniLibs/: SEE target platform) to "internal-storage:/Download/liblottery_prediction.so"
 - Run an App (Note: kill the running App)

---------------------------------------------
APK 재설치없이 업데이트
---------------------------------------------
1. .so 파일을 최신 xls 파일로 적용해서 rebuild
2. 안드로이드 기기에서
 - rebuild 한 .so 파일을 (단말기에 맞는 .so 파일: arm64-v8a/liblottery_prediction.so) "내장메모리:/Download/liblottery_prediction.so" 에 복사
 - App 실행 (실행 중이면 종료해야 됨)

```


Screenshots
----------

> Android App
<img src="https://github.com/godmode2k/lotto645/raw/main/screenshot.jpg" width="40%" height="40%">

