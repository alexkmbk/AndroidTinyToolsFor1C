package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.os.Build;
import android.os.VibrationEffect;
import android.os.Vibrator;
import androidx.annotation.Keep;

import static android.content.Context.VIBRATOR_SERVICE;

@Keep
public class VibrateClass implements Runnable
{

    Activity mContext;
    long milliseconds;

    public VibrateClass(Activity mContext, long milliseconds) {
        this.mContext = mContext;
        this.milliseconds = milliseconds;
    }

    @SuppressWarnings("deprecation")
    public void run() {

        Vibrator vibrator = mContext.getSystemService(Vibrator.class);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            vibrator.vibrate(VibrationEffect.createOneShot(milliseconds, VibrationEffect.DEFAULT_AMPLITUDE));
        } else {
            //deprecated in API 26
            vibrator.vibrate(milliseconds);
        }

        //final ToneGenerator tg = new ToneGenerator(AudioManager.STREAM_NOTIFICATION, 200);
        //tg.startTone(ToneGenerator.TONE_PROP_BEEP);


    }

    public void vibrate()
    {
        mContext.runOnUiThread(this);
    }
}