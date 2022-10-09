@echo off

set RESULT_DIR=.\results
if exist %RESULT_DIR% (
	echo "Deleting %RESULT_DIR%\*"
	del /s/q %RESULT_DIR%\* >nul
) else (
	echo "Creating %RESULT_DIR%"
	mkdir %RESULT_DIR%
)

call test_fax.bat sip t38 t38
call test_fax.bat sip g711 t38
call test_fax.bat sip t38  g711
call test_fax.bat sip g711 g711
call test_fax.bat sip rtp  t38
call test_fax.bat sip t38  rtp
call test_fax.bat sip g711 rtp
call test_fax.bat sip rtp  g711

call test_fax.bat h323 t38  t38  fast
call test_fax.bat h323 g711 t38  fast
call test_fax.bat h323 t38  g711 fast
call test_fax.bat h323 g711 g711 fast

call test_fax.bat h323 t38  t38  slow
call test_fax.bat h323 g711 t38  slow
call test_fax.bat h323 t38  g711 slow
call test_fax.bat h323 g711 g711 slow
