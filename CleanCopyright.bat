@echo off
title CleanCopyright

SETLOCAL ENABLEDELAYEDEXPANSION

set targetDir=Source

REM !\n! will add a blank line
(set \n=^
%=DONT REMOVE THIS=%
)

for /f "tokens=1,2 delims==" %%a in (Config/DefaultGame.ini) do (
if %%a==CopyrightNotice set foundNotice=// %%b
)

REM Grab the preferable Copyright Notice from the DefaultGame.ini.  Any project update should proliferate to all files if you update it and run this bat
echo Attempting to add %foundNotice% to all .h and .cpp files in %targetDir%
echo.

PAUSE 

echo Grabbing all files in %targetDir%...
echo.

set /a total=0
for /r %targetDir% %%a in (*) do (
	set /p foundLine=<!%%a!
	
	REM Does this file already have the copyright notice already match? if so, carry on
	echo !foundLine!|find "!foundNotice!" >nul
	if errorlevel 1 ( 
		set /a total=total+1
		echo %%a 
		echo !foundLine! 
		
		REM Is this first line an include? if so, we need to append a new line and the notice
		echo !foundLine!|find "#" >nul
		if NOT errorlevel 1 ( 
			echo Found include, maybe a pragma.  Appending.
			
			REM duplicate the file, add the new copyright and a new line, and replace the old file with the new
			(echo !foundNotice!!\n!) > %%a.txt.new

			type %%a >> %%a.txt.new
			move /y %%a.txt.new %%a
		)
		
		echo !foundLine!|find "//" >nul
		if NOT errorlevel 1 (
			echo Found a comment that isnt the copyright notice. Replacing.
			
			REM Copy and delete first line
			more +1 "%%a" > %%adeleted.txt.new
			
			REM Is there a space here? if not, we should probably add one
			set /p newTempLine=<"%%adeleted.txt.new"
			
			if [!newTempLine!] == [] (
			echo Space avaliable at the start of the new file - adding our copyright notice.
			(echo !foundNotice!) > %%a.txt.new
			
			) else (
			echo No space avaliable at the start of the new file - pushing existing content down and adding copyright notice
			(echo !foundNotice!!\n!) > %%a.txt.new
			
			)

			type %%adeleted.txt.new >> %%a.txt.new
			REM move /y "%%a.txt.new" "%%a" > nul
			del "%%adeleted.txt.new"
		)
		
		echo --------------------------------------------------------------------------------
	)
)

echo.
echo Found a total of %total% files in %TargetDir% that're eligiable for a new copyright notice

PAUSE
