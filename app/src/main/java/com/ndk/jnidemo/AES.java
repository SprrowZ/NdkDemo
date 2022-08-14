package com.ndk.jnidemo;

import java.security.NoSuchAlgorithmException;

import javax.crypto.Cipher;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

public class AES {
    private static  final String MODE = "AES/ECB/PKCS5Padding";
    /**
     * 数据加密 AES
     * @param data
     * @param key
     * @return  加密后的数据
     */
    public static String encrypt(String data,String key) {
        try {
            Cipher cipher = Cipher.getInstance(MODE);
            cipher.init(Cipher.ENCRYPT_MODE,new SecretKeySpec(key.getBytes(),"AES"));
            //返回加密后的数据
           return Hex.encode(cipher.doFinal(data.getBytes("UTF-8"))) ;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }

    }
    /**
     * 数据解密AES
     * @param data  密文数据
     * @param key  AES密钥
     * @return  解密后的数据
     */
    public static String decrypt(String data,String key){
        try {
            Cipher cipher = Cipher.getInstance(MODE);
            cipher.init(Cipher.DECRYPT_MODE,new SecretKeySpec(key.getBytes(),"AES"));
            byte[] decryptBytes= Hex.decode(data);
            return new String(cipher.doFinal(decryptBytes));
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
