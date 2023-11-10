@set TLSDK=E:\Telink\SDK
@set PATH=%TLSDK%\bin;%TLSDK%\opt\tc32\bin;%TLSDK%\usr\bin;%PATH%
make -j %1 %2 %3
