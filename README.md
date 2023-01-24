### module_app

##zephyr os module app example

mkdir wrk
cd wrk
west init -m git@github.com:palich2000/module_app.git
west update --narrow
west build -b esp32  main-project -- -G"Unix Makefiles"
west flash
minicom -D /dev/ttyACM0 -b 115200


*** Booting Zephyr OS build 3b7e7575a926 ***
Hello libsample 1.0 2.14
[00:00:01.390,000] <inf> module_app: My first MCU program
[00:00:01.390,000] <inf> module_app: Starting! esp32
uart:~$.

success !

