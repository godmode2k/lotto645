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
$ pip3 install numpy
$ pip3 install pandas
$ pip3 install sklearn

$ pip install micromlgen
or
$ pip install https://github.com/eloquentarduino/micromlgen.git


$ python3 test_lotto645_tmp2.py
results:
 - model_lotto645.h
 - model_lotto645_predicts_method.h
 - model_lotto645_results_winning_numbers.h
```



Android App
----------
```sh
$ cd lotto645_prediction/app/src/main/cpp/

// Download (Excel: xls) all results
// https://www.dhlottery.co.kr/gameResult.do?method=byWin
//
// e.g., lotto645 당첨번호 1128회차까지
// https://dhlottery.co.kr/gameResult.do?method=allWinExel&gubun=byWin&nowPage=
// &drwNoStart=1&drwNoEnd=1128

Rename download file:
 - lotto645_당첨번호1128회차까지.xls


(Edit)
test_lotto645_tmp2.py: 188

_xls_filename = "./lotto645_당첨번호1128회차까지.xls"

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

