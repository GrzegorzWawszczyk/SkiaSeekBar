package com.example.app;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {

    // Ładowanie biblioteki C++
    static {
        System.loadLibrary("SkiaSeekBar");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Wywołanie funkcji JNI w C++
        nativeMain();
    }

    // JNI: odpowiada funkcji w C++
    private native int nativeMain();
}
