if [ -f /usr/include/curl/curl.h ];then :;else
    sudo apt-get install libcurl4-gnutls-dev
fi
if [ -e /usr/lib/libipcd.so ];then :;else
	make -C library/ipcd_ipc
	sudo cp library/ipcd_ipc/libipcd.so /usr/lib
	make -C library/ipcd_ipc veryclean
fi

[ -e build ] || mkdir build 
cd build 
cmake .. && make 
