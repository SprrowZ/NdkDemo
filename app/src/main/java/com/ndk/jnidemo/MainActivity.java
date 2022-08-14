package com.ndk.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.ndk.jnidemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
   EditText mEdit;
   Button mRead;
   Button mWrite;
    // Used to load the 'jnidemo' library on application startup.
    static {
        System.loadLibrary("jnidemo");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        mEdit = binding.etData;
        mRead = binding.btnRead;
        mWrite = binding.btnWrite;
        //获得文件路径
        final String filePath = getFilesDir().getPath()+"/test";

        mWrite.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String data = mEdit.getText().toString();
                write(filePath,data);
            }
        });

        mRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            String data =  read(filePath);
                Toast.makeText(MainActivity.this,data,Toast.LENGTH_SHORT).show();
            }
        });
    }


    public native void write(String filePath,String data);
    public native String read(String filePath);
}