#########################################################################
# File Name: add_new_thread.sh
# Author: Sues
# mail: sumory.kaka@foxmail.com
# Created Time: Thu 15 Mar 2018 07:19:50 AM PDT
# Version : 1.0
#########################################################################
#!/bin/bash
cp ws $1 -r
cd $1

BIG_1=`echo ${1} | tr '[a-z]' '[A-Z]'`
echo ${BIG_1}

sed -i "s/WS/${BIG_1}/g" * 
sed -i "s/ws/$1/g" * 

mv ws.c $1.c
mv ws_cli.c  $1_cli.c
mv ws_cli.h  $1_cli.h
mv ws.h $1.h

cd ..

sed -i "/static APP_REG app_to_reg/a{a_$1_register,{0},${BIG_1}_THREAD_NAME}," appmainprog.c
sed -i "/#define TIMERD_THREAD_NAME/a#define ${BIG_1}_THREAD_NAME \"$1\"" inc/u_app_thread.h
sed -i "/extern VOID a_ws_register/aextern VOID a_$1_register(AMB_REGISTER_INFO_T* pt_reg);" appmainprog.c
sed -i "/ADD_SUBDIRECTORY(ws)/aADD_SUBDIRECTORY($1)" CMakeLists.txt
sed -i "s/ws am cli timerd/& $1/" CMakeLists.txt
