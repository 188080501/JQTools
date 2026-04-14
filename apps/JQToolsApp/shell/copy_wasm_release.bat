cd  %~dp0
cd "..\..\..\build\WebAssembly_Qt_6_8_*_single_threaded-Release\apps\JQToolsApp"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQTools.wasm jason@10.0.1.225:~/web/JQTools
    scp JQTools.js jason@10.0.1.225:~/web/JQTools
    scp qtloader.js jason@10.0.1.225:~/web/JQTools
    scp qtlogo.svg jason@10.0.1.225:~/web/JQTools
)

cd  %~dp0
cd "..\web"

ping -n 1 10.0.1.225 >nul
if %errorlevel%==0 (
    scp JQTools.html jason@10.0.1.225:~/web/JQTools
    scp manifest.json jason@10.0.1.225:~/web/JQTools
    scp favicon.ico jason@10.0.1.225:~/web/JQTools
)
