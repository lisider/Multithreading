#########################################################################
# File Name: add_new_thread.sh
# Author: Sues
# mail: sumory.kaka@foxmail.com
# Created Time: Thu 15 Mar 2018 07:19:50 AM PDT
# Version : 1.0
#########################################################################
#!/bin/bash

SAMPLE=sample

cp doc/${SAMPLE} $1 -r
cd $1

BIG_1=`echo ${1} | tr '[a-z]' '[A-Z]'`
BIG_SAMPLE=`echo ${SAMPLE} | tr '[a-z]' '[A-Z]'`

sed -i "s/${BIG_SAMPLE}/${BIG_1}/g" * 
sed -i "s/${SAMPLE}/$1/g" * 

mv ${SAMPLE}.c $1.c
mv ${SAMPLE}_cli.c  $1_cli.c
mv ${SAMPLE}_cli.h  $1_cli.h
mv ${SAMPLE}.h $1.h

cd ..

sed -i "/static APP_REG app_to_reg/a{a_$1_register,{0},${BIG_1}_THREAD_NAME}," appmainprog.c
sed -i "/#define TIMERD_THREAD_NAME/a#define ${BIG_1}_THREAD_NAME \"$1\"" inc/u_app_thread.h
sed -i "/extern VOID a_ws_register/aextern VOID a_$1_register(AMB_REGISTER_INFO_T* pt_reg);" appmainprog.c
sed -i "/ADD_SUBDIRECTORY(ws)/aADD_SUBDIRECTORY($1)" CMakeLists.txt
sed -i "s/ws am cli timerd/& $1/" CMakeLists.txt
