package com.ndk.jnidemo;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);

        String key = "1234567887654321";
        String data = "哈喽，你是啷个？";
        System.out.println("原始数据:"+data);

        //AES加密
        String enStr = AES.encrypt(data,key);

        System.out.println("加密后的数据："+enStr);

        //AES解密

        String deStr = AES.decrypt(enStr,key);

        System.out.println("解密后的数据："+deStr);

    }


}