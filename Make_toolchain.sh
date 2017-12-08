#!/bin/sh

# buildのために必要なパッケージをaptコマンドでインストールしておきます。
sudo apt -y install automake bison flex gawk gettext gperf help2man libncurses5-dev libtool-bin texinfo

# homeディレクトリの下にsrcディレクトリ作成し、そのsrcディレクトリの中にesp32フォルダを新規に作成します。mkdirの-pというオプションコマンドを追加し、二階層下のesp32フォルダまで一気に作成しましょう。作成されたesp32フォルダに移動し、 GitHubよりtoolchainのソースファイルをダウンロードします。
mkdir -p ~/src/esp32
cd ~/src/esp32
git clone -b xtensa-1.22.x https://github.com/espressif/crosstool-NG.git

# ダウンロードしてきたcrosstool-NG ディレクトリに入り、次の通りにパラメータを指定してmakeとbuildを行います。
cd crosstool-NG
./bootstrap
./configure --enable-local
make install
./ct-ng xtensa-esp32-elf
./ct-ng build

# 出来たファイルのアクセス権限を変更し、homeディレクトリ下のArduinoディレクトリ中のhardwareライブラリの中にコピーします。
chmod --recursive u+w builds/xtensa-esp32-elf
cd builds
cp -r xtensa-esp32-elf/ ~/Arduino/hardware/espressif/esp32/tools/

# これでArduino IDEの起動準備ができました。
