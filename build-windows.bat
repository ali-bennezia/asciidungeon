echo off
echo "Compiling ..."

gcc -o ./bin/asciidungeon.exe ./src/*.c ^
	 -I"./../asciigl/include" -L"./libs" -lasciigl-static

if not exist bin (
	mkdir bin
)
if not exist assets (
	mkdir assets
)

xcopy /e /i /y /q assets "bin/assets"

echo "Compilation done."
