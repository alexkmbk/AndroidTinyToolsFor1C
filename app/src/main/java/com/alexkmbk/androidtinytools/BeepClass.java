package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.media.AudioManager;
import android.media.ToneGenerator;
import androidx.annotation.Keep;

@Keep
public class BeepClass implements Runnable
{

    Activity mContext;
    int TONE;

    public BeepClass(Activity mContext, int TONE) {
        this.mContext = mContext;
        this.TONE = TONE;
    }

     public void run() {
        final ToneGenerator  tg = new ToneGenerator(AudioManager.STREAM_ALARM, 100);
        tg.startTone(TONE, 200);
        tg.release();
    }

    public void beep()
    {
        mContext.runOnUiThread(this);
    }
}