package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.media.AudioManager;
import android.media.ToneGenerator;

@android.support.annotation.Keep
public class BeepClass implements Runnable
{

    Activity mContext;
    int TONE;

    public BeepClass(Activity mContext, int TONE) {
        this.mContext = mContext;
        this.TONE = TONE;
    }

     public void run() {
        final ToneGenerator tg = new ToneGenerator(AudioManager.STREAM_NOTIFICATION, 200);
        tg.startTone(TONE);
        tg.release();
    }

    public void beep()
    {
        mContext.runOnUiThread(this);
    }
}