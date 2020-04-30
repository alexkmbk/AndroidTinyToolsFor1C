package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.widget.Toast;

@android.support.annotation.Keep
public class ToastClass implements Runnable
{

    Activity mContext;
    String message;

    public ToastClass(Activity mContext, String message) {
        this.mContext = mContext;
        this.message = message;
    }

    public void run() {
       Toast.makeText(mContext.getApplicationContext(), message, Toast.LENGTH_LONG).show();
    }

    public void toast()
    {
        mContext.runOnUiThread(this);
    }
}