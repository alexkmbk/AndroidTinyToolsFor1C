package com.alexkmbk.androidtinytools;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import android.widget.Toast;

@android.support.annotation.Keep
public class BroadcastReceiverClass implements Runnable{
    Activity mContext; // activity of 1C:Enterprise
    private BroadcastReceiver mReceiver;
    private long mV8Object; // 1C application context
    private String mExtraParamName;
    private String mActionName;

    // in C/C++ code the function will have name Java_com_alexkmbk_androidtinytools_BroadcastReceiverClass_BroadcastMessage
    static native void BroadcastMessage(long pObject, String sEventName, String sExtraParam);

    public BroadcastReceiverClass(Activity mContext, String ActionName, String ExtraParamName, long v8Object) {
        this.mContext = mContext;
        this.mV8Object = v8Object;
        this.mExtraParamName = ExtraParamName;
        this.mActionName = ActionName;
    }

    public void StartBroadcastReceiver(){
            mContext.runOnUiThread(this);
    }

    public void StopBroadcastReceiver()
    {
        if (mReceiver != null)
        {
            mContext.unregisterReceiver(mReceiver);
            mReceiver = null;
        }
    }

        public void run() {

            try {
                System.loadLibrary("AndroidTinyTools_" + Constants.version);
            } catch (UnsatisfiedLinkError e) {
                Toast.makeText(mContext.getApplicationContext(), e.getMessage(), Toast.LENGTH_LONG).show();
                return;
            }

            if (mReceiver == null)
            {
                mReceiver = new BroadcastReceiver() {
                    @Override
                    public void onReceive(Context context, Intent intent) {
                        if (intent.getAction().equals(mActionName)){
                            if (mExtraParamName.isEmpty())
                                BroadcastMessage(mV8Object, mActionName, null);
                            else {
                                 BroadcastMessage(mV8Object, mActionName, intent.getStringExtra(mExtraParamName));
                            }
                        }
                    }
                };
                mContext.registerReceiver(mReceiver, new IntentFilter(mActionName));
            }
        }
 }
