/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <stdio.h>
#include <jni.h>
#include <omp.h>
#define MAX_STRING_LEN 100

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
jstring
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
	char str[MAX_STRING_LEN];
	//strcpy(str,"Hello from JNI !\n Brought to you by the number _!");
	double first,second,last;



omp_set_num_threads(4);
first=omp_get_wtime();
int i;
float a=0;
//#pragma omp parallel for private(i) reduction(+:a)
for (i=0;i<900000;i++)
	a+=i;
second=omp_get_wtime();
snprintf(str,sizeof(str),"Hello from JNI !\n%lf Brought to you by the number %d!\nIt took %lf seconds!\n",a,omp_get_max_threads(),second-first);
    return (*env)->NewStringUTF(env, str);
}
