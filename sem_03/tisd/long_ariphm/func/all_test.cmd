@echo off
for /l %%i in (1,1,6) do if %%i LSS 10 (call pos_test.cmd 0%%i) else (call pos_test.cmd %%i)
for /l %%i in (1,1,4) do if %%i LSS 10 (call neg_test.cmd 0%%i) else (call neg_test.cmd %%i)
 