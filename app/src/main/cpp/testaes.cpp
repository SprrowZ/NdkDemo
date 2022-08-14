//
// Created by 18041 on 2022/8/13.
//
#include <jni.h>
#include <string>

//加密Key
static char* key = "232345234";

jstring encrypt(JNIEnv *env,jstring fileContent){
    jclass cls =  env->FindClass("com/ndk/jnidemo/AES");
    if(cls ==NULL){
        return NULL;
    }
    //通过jclass获取方法id
    jmethodID  methodEncryptId = env->GetStaticMethodID(cls,"encrypt",
    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (methodEncryptId == NULL){
        return NULL;
    }
    //char*转jstring
    jstring  keyAes = env->NewStringUTF(key);

    //调用Java AES 方法
    return (jstring)env->CallStaticObjectMethod(cls,methodEncryptId,fileContent,keyAes);
}

jstring decrypt(JNIEnv *env,jstring fileContent){
    jclass cls =  env->FindClass("com/ndk/jnidemo/AES");
    if(cls ==NULL){
        return NULL;
    }
    //通过jclass获取方法id
    jmethodID  methodDecryptId = env->GetStaticMethodID(cls,"decrypt",
                                                        "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (methodDecryptId == NULL){
        return NULL;
    }
    //char*转jstring
    jstring  keyAes = env->NewStringUTF(key);

    //调用Java AES 解密方法
    return (jstring)env->CallStaticObjectMethod(cls,methodDecryptId,fileContent,keyAes);
}