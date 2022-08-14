#include <jni.h>
#include <string>
#include "testaes.cpp"
//引入android日志
#include <android/log.h>

#define LOGTAG "JNIDdemo"
#define  LOGI(...)   __android_log_print(ANDROID_LOG_INFO,LOGTAG,__VA_ARGS__);


extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" void
TestWrite(JNIEnv *env, jobject, jstring filePath, jstring fileData) {
    const char *jPath = env->GetStringUTFChars(filePath, NULL);

    LOGI("准备写入文件...，数据：%s",env->GetStringUTFChars(filePath, NULL));
    FILE *pFile = fopen(jPath, "w");
    if (pFile == NULL) {
        return;
    }

    LOGI("文件打开成功...");
    //数据加密
    jstring encFileContent = encrypt(env, fileData);
    const char *jFileData = env->GetStringUTFChars(encFileContent, NULL);
    LOGI("加密后的数据：%s",jFileData);

    fwrite(jFileData, strlen(jFileData), 1, pFile);

    fclose(pFile);
    LOGI("文件写入成功，关闭文件...");
}

extern "C" jstring
TestRead(JNIEnv *env, jobject, jstring filePath, jstring fileData) {
    const char *jPath = env->GetStringUTFChars(filePath, NULL);

    LOGI("准备读取文件...");


    FILE *pFile = fopen(jPath, "r");
    if (pFile == NULL) {
        return env->NewStringUTF("打开文件失败");
    }

    LOGI("打开文件成功...");

    char *pBuf;//文件内容指针
    fseek(pFile, 0, SEEK_END);//把指针移动到文件末尾，用于测量文件长度
    int size = (int) ftell(pFile);//内容长度
    pBuf = new char[size + 1];//定义数组长度
    rewind(pFile);//把指针移动到文件开头
    fread(pBuf, size, 1, pFile);
    pBuf[size] = 0;//把读到的文件最后一位，写为0，否则系统会一直寻找到0才结束

    //关闭文件
    fclose(pFile);
    LOGI("读取文件的内容,%s",pBuf);
    jstring  jData = decrypt(env,env->NewStringUTF(pBuf));
    LOGI("解密后的数据,%s",env->GetStringUTFChars(jData,NULL));
    //数据解密

    //返回数据
    return jData;
}
/**
 * 动态注册
 * @param vm  虚拟机对象
 * @return
 */

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *) {
    jint result = -1;
    JNIEnv *env = NULL;
    //通过虚拟机对象获得环境对象
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    const JNINativeMethod method[] = {
            {"write", "(Ljava/lang/String;Ljava/lang/String;)V,(void*)TestWrite"},
            {"read",  "(Ljava/lang/String;Ljava/lang/String;)V,(void*)TestRead"}
    };
    //找到Java类
    jclass jclassName = env->FindClass("com/ndk/jnidemo/MainActivity");
    //执行动态注册
    jint ret = env->RegisterNatives(jclassName, method, 2);
    if (ret != JNI_OK) {
        return result;
    }
    return JNI_VERSION_1_6;
}